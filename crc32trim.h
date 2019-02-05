/* crc32trim.h
 *
 * Copyright (C) 2016-2019 Matt Cover
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Matt Cover
 * werekraken@gmail.com
 */

#ifndef _CRC32TRIM_H_
#define _CRC32TRIM_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NO_ZLIB
extern unsigned long crc32_trim_leading(
    unsigned long crcAB,
    unsigned long crcA,
    long lenB
);
#endif

extern unsigned long crc32_trim_trailing(
    unsigned long crcAB,
    unsigned long crcB,
    long lenB
);

#ifdef __cplusplus
}
#endif

#endif // _CRC32TRIM_H_
