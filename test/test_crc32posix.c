#include "unity.h"
#include "crc32trim.h"

void test_crc32posix_combine(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xd85c7e3fUL; // crc32posix for 'this'
  crcB  = 0x4c536d68UL; // crc32posix for 'that'
  lenB  = 4L;

  crcAB = crc32posix_combine(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0x620d7ac6UL); // crc32posix for 'thisthat'
}

void test_crc32posix_trim_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x620d7ac6UL; // crc32posix for 'thisthat'
  crcA  = 0xd85c7e3fUL; // crc32posix for 'this'
  lenB  = 4L;

  crcB = crc32posix_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x4c536d68UL); // crc32posix for 'that'
}

void test_crc32posix_trim_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x620d7ac6UL; // crc32posix for 'thisthat'
  crcB  = 0x4c536d68UL; // crc32posix for 'that'
  lenB  = 4L;

  crcA = crc32posix_trim_trailing(crcAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0xd85c7e3fUL); // crc32posix for 'this'
}
