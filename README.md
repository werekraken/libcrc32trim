# libcrc32trim

## Overview

_libcrc32trim_ currently exposes one function, `crc32_trim_trailing()`. The
primary motivation for this is to trim padding of a known length and value off
a crc32 without needing the original data used to produce the crc32.

```c
crcA = crc32_trim_trailing(crcAB, crcB, lengthB)
```

In some ways it does the opposite of _[zlib's](https://github.com/madler/zlib)_
`crc32_combine()`.

```c
crcAB = crc32_combine(crcA, crcB, lengthB)
```

It is also worth mentioning that `crc32_trim_leading()` is not needed because
this would follow the same steps as zlib's `crc32_combine()`. This may have
applications when dealing with data where the header and total stream length
are known (keep in mind `crc32_trim_trailing()` can remove a known footer).

```c
crcB = crc32_combine(crcA, crcAB, lengthB)
```

## Usage

```c
unsigned long crcA;
unsigned long crcAB;
unsigned long crcB;
int lenB;

crcAB = 0xedffc49cUL; // crc32 for 'thisthat'
crcB  = 0xa8539d8cUL; // crc32 for 'that'
lenB  = 4;

crcA = crc32_trim_trailing(crcAB, crcB, lenB);
// crcA contains 0xfeee8227UL, the crc32 for 'this'
```

## License

This code is under the zlib license, permitting free commercial use.
