/* crc32trim.c
 *
 * Copyright (C) 2016-2018 Matt Cover
 *
 * For conditions of distribution and use, see copyright notice in crc32trim.h
 * or LICENSE.
 *
 * This code is borrows heavily from crc32.c found in zlib version 1.2.8, but
 * has been altered.
 *
 * Thanks to Mark Adler <madler@alumni.caltech.edu> for writing zlib's crc32.c,
 * his posts about crc32_combine(), and answering questions of the community.
 */

#include <stdio.h>

#define GF2_DIM 32      /* dimension of GF(2) vectors (length of CRC) */

/* ========================================================================= */
static unsigned long gf2_matrix_times(
    unsigned long *mat,
    unsigned long vec
) {
    unsigned long sum;

    sum = 0;
    while (vec) {
        if (vec & 0x80000000UL)
            sum ^= *mat;
        vec = (vec << 1) & 0xffffffffUL;
        mat++;
    }
    return sum;
}

/* ========================================================================= */
static void gf2_matrix_square(
    unsigned long *square,
    unsigned long *mat
) {
    int n;

    for (n = 0; n < GF2_DIM; n++)
        square[n] = gf2_matrix_times(mat, mat[n]);
}

/* ========================================================================= */
unsigned long crc32_trim_trailing(
    unsigned long crc1,
    unsigned long crc2,
    int len2
) {
    int n;
    unsigned long row;
    unsigned long even[GF2_DIM];    /* even-power-of-two zeros operator */
    unsigned long odd[GF2_DIM];     /* odd-power-of-two zeros operator */

    /* degenerate case (also disallow negative lengths) */
    if (len2 <= 0)
        return crc1;

    /* get crcA0 */
    crc1 ^= crc2;

    /* put operator for one zero bit in odd */
    odd[0] = 0xdb710641UL;          /* CRC-32 "Un"polynomial */
    row = 0x80000000UL;
    for (n = 1; n < GF2_DIM; n++) {
        odd[n] = row;
        row >>= 1;
    }

    /* put operator for two zero bits in even */
    gf2_matrix_square(even, odd);

    /* put operator for four zero bits in odd */
    gf2_matrix_square(odd, even);

    /* apply len2 zeros to crc1 (first square will put the operator for one
       zero byte, eight zero bits, in even) */
    do {
        /* apply zeros operator for this bit of len2 */
        gf2_matrix_square(even, odd);
        if (len2 & 1)
            crc1 = gf2_matrix_times(even, crc1);
        len2 >>= 1;

        /* if no more bits set, then done */
        if (len2 == 0)
            break;

        /* another iteration of the loop with odd and even swapped */
        gf2_matrix_square(odd, even);
        if (len2 & 1)
            crc1 = gf2_matrix_times(odd, crc1);
        len2 >>= 1;

        /* if no more bits set, then done */
    } while (len2 != 0);

    return crc1;
}
