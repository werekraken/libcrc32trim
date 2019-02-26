# libcrc32trim

_libcrc32trim_ currently exposes two functions, `crc32_trim_leading()` and
`crc32_trim_trailing()`. These provide opposite functionality to that of
_[zlib's](https://github.com/madler/zlib)_ `crc32_combine()`.

```c
/*
 * NOTE: crc32_combine() is part of zlib and is included here for
 * demonstrative purposes only.
 */
crcAB = crc32_combine(crcA, crcB, lenB);
```

```c
crcB = crc32_trim_leading(crcAB, crcA, lenB);
```

```c
crcA = crc32_trim_trailing(crcAB, crcB, lenB);
```

The initial motivation for `crc32_trim_trailing()` was to compute the crc32 of
a stream trimmed of padding of a known length and value without needing the
original stream. `crc32_trim_leading()` can do the same for leading padding,
but the length of the stream without leading padding must be known.

These functions can also be used to compute the crc32 of a body trimmed of a
known header and footer, when lengths of the body and footer are known, without
needing the original stream.

## Usage

### crc32_trim_leading()

```c
unsigned long crcA;
unsigned long crcAB;
unsigned long crcB;
long lenB;

crcAB = 0xedffc49cUL; // crc32 for 'thisthat'
crcA  = 0xfeee8227UL; // crc32 for 'this'
lenB  = 4L;

crcB = crc32_trim_leading(crcAB, crcA, lenB);
// crcB contains 0xa8539d8cUL, the crc32 for 'that'
```

### crc32_trim_trailing()

```c
unsigned long crcA;
unsigned long crcAB;
unsigned long crcB;
long lenB;

crcAB = 0xedffc49cUL; // crc32 for 'thisthat'
crcB  = 0xa8539d8cUL; // crc32 for 'that'
lenB  = 4L;

crcA = crc32_trim_trailing(crcAB, crcB, lenB);
// crcA contains 0xfeee8227UL, the crc32 for 'this'
```

## Testing

Vagrant is used for consistent test environments.

To spin up the CentOS 7 enviroment, build, and run the tests use the following. This will clean up the vm.
```
./runner.sh
```

If developing new tests, it can be convenient to keep the environment around for several runs. This will leave the vm in place.
```
RUNNER_VAGRANT_DESTROY=false ./runner.sh
```

## License

_libcrc32trim_ is available as open source under the terms of the [zlib license](LICENSE).
