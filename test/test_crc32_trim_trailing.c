#include "unity.h"
#include "crc32trim.h"

/* ========================================================================= */
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

/* ========================================================================= */
void test_crc32_trim_trailing_valid_zeros(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x00000000UL; // crc32 for ''
  crcB  = 0x00000000UL; // crc32 for ''
  lenB  = 0L;

  crcA = crc32_trim_trailing(crcAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0x00000000UL); // crc32 for ''
}

/* ========================================================================= */
void test_crc32_trim_trailing_valid_zero_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0xedffc49cUL; // crc32 for 'thisthat'
  crcB  = 0xedffc49cUL; // crc32 for 'thisthat'
  lenB  = 8L;

  crcA = crc32_trim_trailing(crcAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0x00000000UL); // crc32 for ''
}

/* ========================================================================= */
void test_crc32_trim_trailing_valid_zero_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0xedffc49cUL; // crc32 for 'thisthat'
  crcB  = 0x00000000UL; // crc32 for ''
  lenB  = 0L;

  crcA = crc32_trim_trailing(crcAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0xedffc49cUL); // crc32 for 'thisthat'
}

/* ========================================================================= */
void test_crc32_trim_trailing_invalid_zero_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0xedffc49cUL; // crc32 for 'thisthat'
  crcB  = 0xa8539d8cUL; // crc32 for 'that'
  lenB  = 0L;

  crcA = crc32_trim_trailing(crcAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0xedffc49cUL); // crc32 for 'thisthat'
}

/* ========================================================================= */
void test_crc32_trim_trailing_invalid_neg_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0xedffc49cUL; // crc32 for 'thisthat'
  crcB  = 0xa8539d8cUL; // crc32 for 'that'
  lenB  = -1L;

  crcA = crc32_trim_trailing(crcAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0xedffc49cUL); // crc32 for 'thisthat'
}
