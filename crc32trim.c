/* crc32trim.c
 *
 * Copyright (c) 2016-present Matt Cover
 * All rights reserved.
 *
 * This source code is licensed under the zlib license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * This code is borrows heavily from crc32.c found in zlib version 1.2.8, but
 * has been altered.
 *
 * Thanks to Mark Adler <madler@alumni.caltech.edu> for writing zlib's crc32.c,
 * his posts about crc32_combine(), and answering questions of the community.
 */

#define CRC_FORM_NORMAL    0
#define CRC_FORM_REFLECTED 1

#define CRC_OPERATION_COMBINE 0
#define CRC_OPERATION_TRIM_TRAILING 1

#define GF2_DIM 32      /* dimension of GF(2) vectors (length of CRC) */

/* ========================================================================= */
static unsigned long gf2_matrix_times(
    unsigned long *mat,
    unsigned long vec,
    int form
) {
    unsigned long sum;

    sum = 0;
    while (vec) {
        if (form == CRC_FORM_NORMAL) {
            if (vec & 0x80000000UL)
                sum ^= *mat;
            vec = (vec << 1) & 0xffffffffUL;
        } else {
            if (vec & 1)
                sum ^= *mat;
            vec >>= 1;
        }
        mat++;
    }
    return sum;
}

/* ========================================================================= */
static void gf2_matrix_square(
    unsigned long *square,
    unsigned long *mat,
    int form
) {
    int n;

    for (n = 0; n < GF2_DIM; n++)
        square[n] = gf2_matrix_times(mat, mat[n], form);
}

/* ========================================================================= */
static unsigned long crc32_reconstruct(
    unsigned long crc1,
    unsigned long crc2,
    long len2,
    unsigned long poly,
    int form,
    int operation
) {
    int n;
    unsigned long row;
    unsigned long even[GF2_DIM];    /* even-power-of-two zeros operator */
    unsigned long odd[GF2_DIM];     /* odd-power-of-two zeros operator */

    /* degenerate case (also disallow negative lengths) */
    if (len2 <= 0)
        return crc1;

    if (operation == CRC_OPERATION_TRIM_TRAILING) {
        /* put crcA0 in crc1 */
        crc1 ^= crc2;
    }

    /* put operator for one zero bit in odd */
    odd[0] = poly;
    if (form == CRC_FORM_NORMAL) {
        row = 0x80000000UL;
    } else {
        row = 1;
    }
    for (n = 1; n < GF2_DIM; n++) {
        odd[n] = row;
        if (form == CRC_FORM_NORMAL) {
            row >>= 1;
        } else {
            row <<= 1;
        }
    }

    /* put operator for two zero bits in even */
    gf2_matrix_square(even, odd, form);

    /* put operator for four zero bits in odd */
    gf2_matrix_square(odd, even, form);

    /* apply len2 zeros to crc1 (first square will put the operator for one
       zero byte, eight zero bits, in even) */
    do {
        /* apply zeros operator for this bit of len2 */
        gf2_matrix_square(even, odd, form);
        if (len2 & 1)
            crc1 = gf2_matrix_times(even, crc1, form);
        len2 >>= 1;

        /* if no more bits set, then done */
        if (len2 == 0)
            break;

        /* another iteration of the loop with odd and even swapped */
        gf2_matrix_square(odd, even, form);
        if (len2 & 1)
            crc1 = gf2_matrix_times(odd, crc1, form);
        len2 >>= 1;

        /* if no more bits set, then done */
    } while (len2 != 0);

    if (operation == CRC_OPERATION_COMBINE) {
        /* put crcAB in crc1 */
        crc1 ^= crc2;
    }

    return crc1;
}

/* ========================================================================= */
unsigned long crc32_combine_nz(
    unsigned long crcA,
    unsigned long crcB,
    long lenB
) {
    unsigned long poly = 0xedb88320UL; /* CRC-32 "reversed" polynomial */
    return crc32_reconstruct(crcA, crcB, lenB,
               poly, CRC_FORM_REFLECTED, CRC_OPERATION_COMBINE);
}

/* ========================================================================= */
unsigned long crc32_trim_leading(
    unsigned long crcAB,
    unsigned long crcA,
    long lenB
) {
    return crc32_combine_nz(crcA, crcAB, lenB);
}

/* ========================================================================= */
unsigned long crc32_trim_trailing(
    unsigned long crcAB,
    unsigned long crcB,
    long lenB
) {
    unsigned long poly = 0xdb710641UL; /* CRC-32 "reciprocal" polynomial */
    return crc32_reconstruct(crcAB, crcB, lenB,
               poly, CRC_FORM_NORMAL, CRC_OPERATION_TRIM_TRAILING);
}

/* ========================================================================= */
unsigned long crc32c_combine(
    unsigned long crcA,
    unsigned long crcB,
    long lenB
) {
    unsigned long poly = 0x82f63b78UL; /* CRC-32C "reversed" polynomial */
    return crc32_reconstruct(crcA, crcB, lenB,
               poly, CRC_FORM_REFLECTED, CRC_OPERATION_COMBINE);
}

/* ========================================================================= */
unsigned long crc32c_trim_leading(
    unsigned long crcAB,
    unsigned long crcA,
    long lenB
) {
    return crc32c_combine(crcA, crcAB, lenB);
}

/* ========================================================================= */
unsigned long crc32c_trim_trailing(
    unsigned long crcAB,
    unsigned long crcB,
    long lenB
) {
    unsigned long poly = 0x05EC76F1UL; /* CRC-32C "reciprocal" polynomial */
    return crc32_reconstruct(crcAB, crcB, lenB,
               poly, CRC_FORM_NORMAL, CRC_OPERATION_TRIM_TRAILING);
}

/* ========================================================================= */
unsigned long crc32posix_combine(
    unsigned long crcA,
    unsigned long crcB,
    long lenB
) {
    unsigned long poly = 0x04c11db7UL; /* CRC-32 "normal" polynomial */

    /* avoid bit flip on degenerate case (also disallow negative lengths) */
    if (lenB <= 0)
        return crcA;

    return crc32_reconstruct(crcA ^ 0xffffffff, crcB, lenB,
               poly, CRC_FORM_NORMAL, CRC_OPERATION_COMBINE);
}

/* ========================================================================= */
unsigned long crc32posix_trim_leading(
    unsigned long crcAB,
    unsigned long crcA,
    long lenB
) {
    return crc32posix_combine(crcA, crcAB, lenB);
}

/* ========================================================================= */
unsigned long crc32posix_trim_trailing(
    unsigned long crcAB,
    unsigned long crcB,
    long lenB
) {
    unsigned long poly = 0x82608edbUL; /* CRC-32 "reversed reciprocal"
                                          polynomial */

    /* avoid bit flip on degenerate case (also disallow negative lengths) */
    if (lenB <= 0)
        return crcAB;

    return crc32_reconstruct(crcAB, crcB, lenB,
               poly, CRC_FORM_REFLECTED, CRC_OPERATION_TRIM_TRAILING) ^ 0xffffffff;
}
