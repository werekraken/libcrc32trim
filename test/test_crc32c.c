#include "unity.h"
#include "crc32trim.h"

void test_crc32c_combine(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xd4301c5dUL; // crc32c for 'this'
  crcB  = 0x9deebb0eUL; // crc32c for 'that'
  lenB  = 4L;

  crcAB = crc32c_combine(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0x0d252e1bUL); // crc32c for 'thisthat'
}

void test_crc32c_trim_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x0d252e1bUL; // crc32c for 'thisthat'
  crcA  = 0xd4301c5dUL; // crc32c for 'this'
  lenB  = 4L;

  crcB = crc32c_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x9deebb0eUL); // crc32c for 'that'
}

void test_crc32c_trim_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x0d252e1bUL; // crc32c for 'thisthat'
  crcB  = 0x9deebb0eUL; // crc32c for 'that'
  lenB  = 4L;

  crcA = crc32c_trim_trailing(crcAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0xd4301c5dUL); // crc32c for 'this'
}
