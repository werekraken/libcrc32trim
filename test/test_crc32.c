#include "unity.h"
#include "crc32trim.h"

void test_crc32_combine_nz(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xfeee8227UL; // crc32 for 'this'
  crcB  = 0xa8539d8cUL; // crc32 for 'that'
  lenB  = 4L;

  crcAB = crc32_combine_nz(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xedffc49cUL); // crc32 for 'thisthat'
}

void test_crc32_trim_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0xedffc49cUL; // crc32 for 'thisthat'
  crcA  = 0xfeee8227UL; // crc32 for 'this'
  lenB  = 4L;

  crcB = crc32_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0xa8539d8cUL); // crc32 for 'that'
}

void test_crc32_trim_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0xedffc49cUL; // crc32 for 'thisthat'
  crcB  = 0xa8539d8cUL; // crc32 for 'that'
  lenB  = 4L;

  crcA = crc32_trim_trailing(crcAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0xfeee8227UL); // crc32 for 'this'
}
