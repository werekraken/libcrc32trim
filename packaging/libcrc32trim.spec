%{?!packager: %define packager Matt Cover <werekraken@gmail.com>}

BuildRequires: zlib-devel

Name:     libcrc32trim
Version:  %{ver}
Release:  1%{?dist}
License:  zlib
Group:    Development/Libraries
URL:      https://github.com/werekraken/libcrc32trim
Source0:  %{name}-%{version}.tar.gz
Summary:  Trim crcs of streams from the front, end, or both of a combined crc
Requires: zlib


%description
Trim crcs of streams (e.g. padding, headers, footers) from the front, end, or
both of a combined crc when the lengths of all streams, but the first, are
known.

%package devel
Summary:  Development files for libcrc32trim
Requires: %{name} = %{version}-%{release}

%description devel
The libcrc32trim-devel package contains the header files and libraries needed
to develop applications that use libcrc32trim.

%prep
%setup -q

%build
%{make_build}

%install
%{make_install} INCLUDEDIR=%{_includedir} LIBDIR=%{_libdir}

%clean
%{__rm} -rf %{buildroot}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%doc LICENSE README.md
%{_libdir}/libcrc32trim.so.*

%files devel
%doc LICENSE README.md
%{_libdir}/libcrc32trim.so
%{_includedir}/crc32trim.h

%changelog
* %(date "+%a %b %d %Y") %{packager} - %{version}-%{release}
- Automatic build
