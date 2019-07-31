# libcrc32trim

_libcrc32trim_ exposes a number of functions which perform combine and trim operations for several CRC-32 implementations.

`crc32_combine_nz()`, `crc32c_combine()`, and `cksum_combine_no_len()` all perform a combine operation like _[zlib's](https://github.com/madler/zlib)_ `crc32_combine()`.
```c
crcAB = crc32_combine_nz(crcA, crcB, lenB);
crcAB = crc32c_combine(crcA, crcB, lenB);
crcAB = cksum_combine_no_len(crcA, crcB, lenB);
```

`crc32_trim_leading()`, `crc32c_trim_leading()`, and `cksum_trim_leading_no_len()` all perform a leading trim.
```c
crcB = crc32_trim_leading(crcAB, crcA, lenB);
crcB = crc32c_trim_leading(crcAB, crcA, lenB);
crcB = cksum_trim_leading_no_len(crcAB, crcA, lenB);
```

`crc32_trim_trailing()`, `crc32c_trim_trailing()`, and `cksum_trim_trailing_no_len()` all perform a trailing trim.
```c
crcA = crc32_trim_trailing(crcAB, crcB, lenB);
crcA = crc32c_trim_trailing(crcAB, crcB, lenB);
crcA = cksum_trim_trailing_no_len(crcAB, crcB, lenB);
```

The initial motivation for `crc32_trim_trailing()` was to compute the crc32 of
a stream trimmed of padding of a known length and value without needing the
original stream. `crc32_trim_leading()` can do the same for leading padding,
but the length of the stream without leading padding must be known.

These functions can also be used to compute the crc32 of a body trimmed of a
known header and footer, when lengths of the body and footer are known, without
needing the original stream.

## Installation

_libcrc32trim_ has build time dependencies on gcc and make. These package names may vary slightly between distros.

Install build time dependencies on CentOS.
```
sudo yum install gcc make
```

Build.
```
make
```

Install.
```
sudo make install
```

The vagrant environment can also be used to build an rpm.

To spin up the CentOS 7 environment and build an rpm use the following. This will clean up the vm.
```
./runner.sh buildrpm
```

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

## Versioning

This project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## License

_libcrc32trim_ is available as open source under the terms of the [zlib license](LICENSE).

## Compatibility

_libcrc32trim_ is actively tested on CentOS 7, but is likely to work on other distros and Unix-like systems.
