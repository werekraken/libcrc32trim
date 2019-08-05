#include "unity.h"
#include "crc32trim.h"

/* ========================================================================= */
void test_cksum_trim_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenB;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenAB = 8L;
  lenB  = 4L;

  crcA = cksum_trim_trailing(crcAB, lenAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0xc91eafc6UL); // cksum for 'this'
}

/* ========================================================================= */
void test_cksum_trim_trailing_valid_zeros(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenB;

  crcAB = 0xffffffffUL; // cksum for ''
  crcB  = 0xffffffffUL; // cksum for ''
  lenAB = 0L;
  lenB  = 0L;

  crcA = cksum_trim_trailing(crcAB, lenAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0xffffffffUL); // cksum for ''
}

/* ========================================================================= */
void test_cksum_trim_trailing_valid_zero_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenB;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcB  = 0x3fa2960aUL; // cksum for 'thisthat'
  lenAB = 8L;
  lenB  = 8L;

  crcA = cksum_trim_trailing(crcAB, lenAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0xffffffffUL); // cksum for ''
}

/* ========================================================================= */
void test_cksum_trim_trailing_valid_zero_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenB;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcB  = 0xffffffffUL; // cksum for ''
  lenAB = 8L;
  lenB  = 0L;

  crcA = cksum_trim_trailing(crcAB, lenAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0x3fa2960aUL); // cksum for 'thisthat'
}

/* ========================================================================= */
void test_cksum_trim_trailing_invalid_zero_lenA(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenB;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenAB = 4L;
  lenB  = 4L;

  crcA = cksum_trim_trailing(crcAB, lenAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0x3fa2960aUL); // cksum for 'thisthat'
}

/* ========================================================================= */
void test_cksum_trim_trailing_invalid_zero_lenB(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenB;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenAB = 8L;
  lenB  = 0L;

  crcA = cksum_trim_trailing(crcAB, lenAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0x3fa2960aUL); // cksum for 'thisthat'
}

/* ========================================================================= */
void test_cksum_trim_trailing_invalid_zero_lenAB(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenB;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenAB = 0L;
  lenB  = 4L;

  crcA = cksum_trim_trailing(crcAB, lenAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0x3fa2960aUL); // cksum for 'thisthat'
}

/* ========================================================================= */
void test_cksum_trim_trailing_invalid_neg_lenA(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenB;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenAB = 3L;
  lenB  = 4L;

  crcA = cksum_trim_trailing(crcAB, lenAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0x3fa2960aUL); // cksum for 'thisthat'
}

/* ========================================================================= */
void test_cksum_trim_trailing_invalid_neg_lenB(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenB;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenAB = 8L;
  lenB  = -1L;

  crcA = cksum_trim_trailing(crcAB, lenAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0x3fa2960aUL); // cksum for 'thisthat'
}

/* ========================================================================= */
void test_cksum_trim_trailing_invalid_neg_lenAB(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenB;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenAB = -1L;
  lenB  = 4L;

  crcA = cksum_trim_trailing(crcAB, lenAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0x3fa2960aUL); // cksum for 'thisthat'
}
