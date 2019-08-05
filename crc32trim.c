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

static unsigned long const crc32_04c11db7_table[] = {
    0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b,
    0x1a864db2, 0x1e475005, 0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
    0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd, 0x4c11db70, 0x48d0c6c7,
    0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
    0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3,
    0x709f7b7a, 0x745e66cd, 0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,
    0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5, 0xbe2b5b58, 0xbaea46ef,
    0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
    0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb,
    0xceb42022, 0xca753d95, 0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
    0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d, 0x34867077, 0x30476dc0,
    0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
    0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4,
    0x0808d07d, 0x0cc9cdca, 0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,
    0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02, 0x5e9f46bf, 0x5a5e5b08,
    0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
    0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc,
    0xb6238b25, 0xb2e29692, 0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,
    0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a, 0xe0b41de7, 0xe4750050,
    0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
    0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34,
    0xdc3abded, 0xd8fba05a, 0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,
    0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb, 0x4f040d56, 0x4bc510e1,
    0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
    0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5,
    0x3f9b762c, 0x3b5a6b9b, 0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,
    0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623, 0xf12f560e, 0xf5ee4bb9,
    0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
    0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd,
    0xcda1f604, 0xc960ebb3, 0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
    0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b, 0x9b3660c6, 0x9ff77d71,
    0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
    0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2,
    0x470cdd2b, 0x43cdc09c, 0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,
    0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24, 0x119b4be9, 0x155a565e,
    0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
    0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a,
    0x2d15ebe3, 0x29d4f654, 0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,
    0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c, 0xe3a1cbc1, 0xe760d676,
    0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
    0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662,
    0x933eb0bb, 0x97ffad0c, 0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,
    0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
};

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
    if (lenB == 0 && crcAB == crcA)
        return 0;

    if (lenB <= 0)
        return crcAB;

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
    if (lenB == 0 && crcAB == crcA)
        return 0;

    if (lenB <= 0)
        return crcAB;

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
    if (lenB == 0 && crcAB == crcA)
        return 0xffffffff;

    if (lenB <= 0)
        return crcAB;

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

/* ========================================================================= */
unsigned long cksum_pop_len(
    unsigned long crc,
    long len
) {
    unsigned long crcB;
    long lenB;

    if (len <= 0)
        return crc;

    crcB = 0;
    lenB = 0;
    for (; len; len >>= 8) {
        crcB = (crcB << 8) ^
                   crc32_04c11db7_table[((crcB >> 24) ^ len) & 0xff];
        lenB++;
    }
    crcB &= 0xffffffff;
    crcB ^= 0xffffffff;
    return crc32posix_trim_trailing(crc, crcB, lenB);
}

/* ========================================================================= */
unsigned long cksum_push_len(
    unsigned long crc,
    long len
) {
    if (len <= 0)
        return crc;

    crc ^= 0xffffffff;
    for (; len; len >>= 8)
        crc = (crc << 8) ^
                   crc32_04c11db7_table[((crc >> 24) ^ len) & 0xff];
    crc &= 0xffffffff;
    return crc ^ 0xffffffff;
}

/* ========================================================================= */
unsigned long cksum_combine(
    unsigned long crcA,
    long lenA,
    unsigned long crcB,
    long lenB
) {
    unsigned long crcAB;
    long lenAB;

    if (lenA == 0 && crcA == 0xffffffff)
        return crcB;

    if (lenA <= 0 || lenB <= 0)
        return crcA;

    lenAB = lenA + lenB;

    if (lenAB < lenA || lenAB < lenB)
        return crcA;

    crcA = cksum_pop_len(crcA, lenA);
    crcB = cksum_pop_len(crcB, lenB);

    crcAB = crc32posix_combine(crcA, crcB, lenB);

    return cksum_push_len(crcAB, lenAB);
}

/* ========================================================================= */
unsigned long cksum_trim_leading(
    unsigned long crcAB,
    long lenAB,
    unsigned long crcA,
    long lenA
) {
    unsigned long crcB;
    long lenB;

    if (lenAB <= 0 || lenA <= 0)
        return crcAB;

    lenB = lenAB - lenA;

   if (lenB == 0 && crcAB == crcA)
        return 0xffffffff;

    if (lenB <= 0)
        return crcAB;

    crcAB = cksum_pop_len(crcAB, lenAB);
    crcA  = cksum_pop_len(crcA,  lenA);

    crcB = crc32posix_trim_leading(crcAB, crcA, lenB);

    return cksum_push_len(crcB, lenB);
}

/* ========================================================================= */
unsigned long cksum_trim_trailing(
    unsigned long crcAB,
    long lenAB,
    unsigned long crcB,
    long lenB
) {
    unsigned long crcA;
    long lenA;

    if (lenAB <= 0 || lenB <= 0)
        return crcAB;

    lenA = lenAB - lenB;

    if (lenA == 0 && crcAB == crcB)
        return 0xffffffff;

    if (lenA <= 0)
        return crcAB;

    crcAB = cksum_pop_len(crcAB, lenAB);
    crcB  = cksum_pop_len(crcB,  lenB);

    crcA = crc32posix_trim_trailing(crcAB, crcB, lenB);

    return cksum_push_len(crcA, lenA);
}
