/* crc32trim.h
 *
 * Copyright (c) 2016-present Matt Cover
 * All rights reserved.
 *
 * This source code is licensed under the zlib license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef _CRC32TRIM_H_
#define _CRC32TRIM_H_

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned long cksum_combine(
    unsigned long crcA,
    long lenA,
    unsigned long crcB,
    long lenB
);

extern unsigned long cksum_pop_len(
    unsigned long crc,
    long len
);

extern unsigned long cksum_push_len(
    unsigned long crc,
    long len
);

extern unsigned long cksum_trim_leading(
    unsigned long crcAB,
    long lenAB,
    unsigned long crcA,
    long lenA
);

extern unsigned long cksum_trim_trailing(
    unsigned long crcAB,
    long lenAB,
    unsigned long crcB,
    long lenB
);

extern unsigned long crc32_combine_nz(
    unsigned long crcA,
    unsigned long crcB,
    long lenB
);

extern unsigned long crc32_trim_leading(
    unsigned long crcAB,
    unsigned long crcA,
    long lenB
);

extern unsigned long crc32_trim_trailing(
    unsigned long crcAB,
    unsigned long crcB,
    long lenB
);

extern unsigned long crc32c_combine(
    unsigned long crcA,
    unsigned long crcB,
    long lenB
);

extern unsigned long crc32c_trim_leading(
    unsigned long crcAB,
    unsigned long crcA,
    long lenB
);

extern unsigned long crc32c_trim_trailing(
    unsigned long crcAB,
    unsigned long crcB,
    long lenB
);

extern unsigned long crc32posix_combine(
    unsigned long crcA,
    unsigned long crcB,
    long lenB
);

extern unsigned long crc32posix_trim_leading(
    unsigned long crcAB,
    unsigned long crcA,
    long lenB
);

extern unsigned long crc32posix_trim_trailing(
    unsigned long crcAB,
    unsigned long crcB,
    long lenB
);

#ifdef __cplusplus
}
#endif

#endif // _CRC32TRIM_H_
