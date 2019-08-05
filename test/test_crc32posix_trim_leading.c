#include "unity.h"
#include "crc32trim.h"

/* ========================================================================= */
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

/* ========================================================================= */
void test_crc32posix_trim_leading_valid_zeros(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0xffffffffUL; // crc32posix for ''
  crcA  = 0xffffffffUL; // crc32posix for ''
  lenB  = 0L;

  crcB = crc32posix_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0xffffffffUL); // crc32posix for ''
}

/* ========================================================================= */
void test_crc32posix_trim_leading_valid_zero_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x620d7ac6UL; // crc32posix for 'thisthat'
  crcA  = 0xffffffffUL; // crc32posix for ''
  lenB  = 8L;

  crcB = crc32posix_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x620d7ac6UL); // crc32posix for 'thisthat'
}

/* ========================================================================= */
void test_crc32posix_trim_leading_valid_zero_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x620d7ac6UL; // crc32posix for 'thisthat'
  crcA  = 0x620d7ac6UL; // crc32posix for 'thisthat'
  lenB  = 0L;

  crcB = crc32posix_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0xffffffffUL); // crc32posix for ''
}

/* ========================================================================= */
void test_crc32posix_trim_leading_invalid_zero_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x620d7ac6UL; // crc32posix for 'thisthat'
  crcA  = 0xd85c7e3fUL; // crc32posix for 'this'
  lenB  = 0L;

  crcB = crc32posix_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x620d7ac6UL); // crc32posix for 'thisthat'
}

/* ========================================================================= */
void test_crc32posix_trim_leading_invalid_neg_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x620d7ac6UL; // crc32posix for 'thisthat'
  crcA  = 0xd85c7e3fUL; // crc32posix for 'this'
  lenB  = -1L;

  crcB = crc32posix_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x620d7ac6UL); // crc32posix for 'thisthat'
}
