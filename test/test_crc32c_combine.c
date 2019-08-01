#include "unity.h"
#include "crc32trim.h"

/* ========================================================================= */
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

/* ========================================================================= */
void test_crc32c_combine_valid_zeros(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0x00000000UL; // crc32c for ''
  crcB  = 0x00000000UL; // crc32c for ''
  lenB  = 0L;

  crcAB = crc32c_combine(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0x00000000UL); // crc32c for ''
}

/* ========================================================================= */
void test_crc32c_combine_valid_zero_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0x00000000UL; // crc32c for ''
  crcB  = 0x9deebb0eUL; // crc32c for 'that'
  lenB  = 4L;

  crcAB = crc32c_combine(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0x9deebb0eUL); // crc32c for 'that'
}

/* ========================================================================= */
void test_crc32c_combine_valid_zero_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xd4301c5dUL; // crc32c for 'this'
  crcB  = 0x00000000UL; // crc32c for ''
  lenB  = 0L;

  crcAB = crc32c_combine(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xd4301c5dUL); // crc32c for 'this'
}

/* ========================================================================= */
void test_crc32c_combine_invalid_zero_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xd4301c5dUL; // crc32c for 'this'
  crcB  = 0x9deebb0eUL; // crc32c for 'that'
  lenB  = 0L;

  crcAB = crc32c_combine(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xd4301c5dUL); // crc32c for 'this'
}

/* ========================================================================= */
void test_crc32c_combine_invalid_neg_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xd4301c5dUL; // crc32c for 'this'
  crcB  = 0x9deebb0eUL; // crc32c for 'that'
  lenB  = -1L;

  crcAB = crc32c_combine(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xd4301c5dUL); // crc32c for 'this'
}
