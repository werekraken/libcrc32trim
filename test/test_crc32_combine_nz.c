#include "unity.h"
#include "crc32trim.h"

/* ========================================================================= */
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

/* ========================================================================= */
void test_crc32_combine_nz_valid_zeros(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0x00000000UL; // crc32 for ''
  crcB  = 0x00000000UL; // crc32 for ''
  lenB  = 0L;

  crcAB = crc32_combine_nz(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0x00000000UL); // crc32 for ''
}

/* ========================================================================= */
void test_crc32_combine_nz_valid_zero_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0x00000000UL; // crc32 for ''
  crcB  = 0xa8539d8cUL; // crc32 for 'that'
  lenB  = 4L;

  crcAB = crc32_combine_nz(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xa8539d8cUL); // crc32 for 'that'
}

/* ========================================================================= */
void test_crc32_combine_nz_valid_zero_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xfeee8227UL; // crc32 for 'this'
  crcB  = 0x00000000UL; // crc32 for ''
  lenB  = 0L;

  crcAB = crc32_combine_nz(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xfeee8227UL); // crc32 for 'this'
}

/* ========================================================================= */
void test_crc32_combine_nz_invalid_zero_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xfeee8227UL; // crc32 for 'this'
  crcB  = 0xa8539d8cUL; // crc32 for 'that'
  lenB  = 0L;

  crcAB = crc32_combine_nz(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xfeee8227UL); // crc32 for 'this'
}

/* ========================================================================= */
void test_crc32_combine_nz_invalid_neg_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xfeee8227UL; // crc32 for 'this'
  crcB  = 0xa8539d8cUL; // crc32 for 'that'
  lenB  = -1L;

  crcAB = crc32_combine_nz(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xfeee8227UL); // crc32 for 'this'
}
