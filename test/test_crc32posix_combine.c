#include "unity.h"
#include "crc32trim.h"

/* ========================================================================= */
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

/* ========================================================================= */
void test_crc32posix_combine_valid_zeros(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xffffffffUL; // crc32posix for ''
  crcB  = 0xffffffffUL; // crc32posix for ''
  lenB  = 0L;

  crcAB = crc32posix_combine(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xffffffffUL); // crc32posix for ''
}

/* ========================================================================= */
void test_crc32posix_combine_valid_zero_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xffffffffUL; // crc32posix for ''
  crcB  = 0x4c536d68UL; // crc32posix for 'that'
  lenB  = 4L;

  crcAB = crc32posix_combine(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0x4c536d68UL); // crc32posix for 'that'
}

/* ========================================================================= */
void test_crc32posix_combine_valid_zero_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xd85c7e3fUL; // crc32posix for 'this'
  crcB  = 0xffffffffUL; // crc32posix for ''
  lenB  = 0L;

  crcAB = crc32posix_combine(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xd85c7e3fUL); // crc32posix for 'this'
}

/* ========================================================================= */
void test_crc32posix_combine_invalid_zero_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xd85c7e3fUL; // crc32posix for 'this'
  crcB  = 0x4c536d68UL; // crc32posix for 'that'
  lenB  = 0L;

  crcAB = crc32posix_combine(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xd85c7e3fUL); // crc32posix for 'this'
}

/* ========================================================================= */
void test_crc32posix_combine_invalid_neg_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xd85c7e3fUL; // crc32posix for 'this'
  crcB  = 0x4c536d68UL; // crc32posix for 'that'
  lenB  = -1L;

  crcAB = crc32posix_combine(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xd85c7e3fUL); // crc32posix for 'this'
}
