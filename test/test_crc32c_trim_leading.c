#include "unity.h"
#include "crc32trim.h"

/* ========================================================================= */
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

/* ========================================================================= */
void test_crc32c_trim_leading_valid_zeros(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x00000000UL; // crc32c for ''
  crcA  = 0x00000000UL; // crc32c for ''
  lenB  = 0L;

  crcB = crc32c_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x00000000UL); // crc32c for ''
}

/* ========================================================================= */
void test_crc32c_trim_leading_valid_zero_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x0d252e1bUL; // crc32c for 'thisthat'
  crcA  = 0x00000000UL; // crc32c for ''
  lenB  = 8L;

  crcB = crc32c_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x0d252e1bUL); // crc32c for 'thisthat'
}

/* ========================================================================= */
void test_crc32c_trim_leading_valid_zero_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x0d252e1bUL; // crc32c for 'thisthat'
  crcA  = 0x0d252e1bUL; // crc32c for 'thisthat'
  lenB  = 0L;

  crcB = crc32c_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x00000000UL); // crc32c for ''
}

/* ========================================================================= */
void test_crc32c_trim_leading_invalid_zero_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x0d252e1bUL; // crc32c for 'thisthat'
  crcA  = 0xd4301c5dUL; // crc32c for 'this'
  lenB  = 0L;

  crcB = crc32c_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x0d252e1bUL); // crc32c for 'thisthat'
}

/* ========================================================================= */
void test_crc32c_trim_leading_invalid_neg_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x0d252e1bUL; // crc32c for 'thisthat'
  crcA  = 0xd4301c5dUL; // crc32c for 'this'
  lenB  = -1L;

  crcB = crc32c_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x0d252e1bUL); // crc32c for 'thisthat'
}
