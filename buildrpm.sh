#!/bin/bash

set -e

name="libcrc32trim"
version="`awk '{print $NF}' VERSION`"
tar="rpmbuild/${name}-${version}.tar.gz"

rm -rf rpmbuild
mkdir rpmbuild

tar cvzf "$tar" \
  --transform 's%^%'"${name}-${version}"'/%' \
  crc32trim.{c,h} \
  LICENSE \
  Makefile \
  packaging/ \
  README.md \
  VERSION

rpmbuild \
  --define "_topdir `pwd`/rpmbuild" \
  --define "ver $version" \
  -ta "$tar"
