#include "unity.h"
#include "crc32trim.h"

/* ========================================================================= */
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

/* ========================================================================= */
void test_crc32_trim_leading_valid_zeros(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x00000000UL; // crc32 for ''
  crcA  = 0x00000000UL; // crc32 for ''
  lenB  = 0L;

  crcB = crc32_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x00000000UL); // crc32 for ''
}

/* ========================================================================= */
void test_crc32_trim_leading_valid_zero_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0xedffc49cUL; // crc32 for 'thisthat'
  crcA  = 0x00000000UL; // crc32 for ''
  lenB  = 8L;

  crcB = crc32_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0xedffc49cUL); // crc32 for 'thisthat'
}

/* ========================================================================= */
void test_crc32_trim_leading_valid_zero_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0xedffc49cUL; // crc32 for 'thisthat'
  crcA  = 0xedffc49cUL; // crc32 for 'thisthat'
  lenB  = 0L;

  crcB = crc32_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x00000000UL); // crc32 for ''
}

/* ========================================================================= */
void test_crc32_trim_leading_invalid_zero_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0xedffc49cUL; // crc32 for 'thisthat'
  crcA  = 0xfeee8227UL; // crc32 for 'this'
  lenB  = 0L;

  crcB = crc32_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0xedffc49cUL); // crc32 for 'thisthat'
}

/* ========================================================================= */
void test_crc32_trim_leading_invalid_neg_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0xedffc49cUL; // crc32 for 'thisthat'
  crcA  = 0xfeee8227UL; // crc32 for 'this'
  lenB  = -1L;

  crcB = crc32_trim_leading(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0xedffc49cUL); // crc32 for 'thisthat'
}
