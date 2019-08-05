#include "unity.h"
#include "crc32trim.h"

/* ========================================================================= */
void test_cksum_trim_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenA;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcA  = 0xc91eafc6UL; // cksum for 'this'
  lenAB = 8L;
  lenA  = 4L;

  crcB = cksum_trim_leading(crcAB, lenAB, crcA, lenA);

  TEST_ASSERT_EQUAL_UINT(crcB, 0xf014b584UL); // cksum for 'that'
}

/* ========================================================================= */
void test_cksum_trim_leading_valid_zeros(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenA;

  crcAB = 0xffffffffUL; // cksum for ''
  crcA  = 0xffffffffUL; // cksum for ''
  lenAB = 0L;
  lenA  = 0L;

  crcB = cksum_trim_leading(crcAB, lenAB, crcA, lenA);

  TEST_ASSERT_EQUAL_UINT(crcB, 0xffffffffUL); // cksum for ''
}

/* ========================================================================= */
void test_cksum_trim_leading_valid_zero_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenA;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcA  = 0xffffffffUL; // cksum for ''
  lenAB = 8L;
  lenA  = 0L;

  crcB = cksum_trim_leading(crcAB, lenAB, crcA, lenA);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x3fa2960aUL); // cksum for 'thisthat'
}

/* ========================================================================= */
void test_cksum_trim_leading_valid_zero_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenA;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcA  = 0x3fa2960aUL; // cksum for 'thisthat'
  lenAB = 8L;
  lenA  = 8L;

  crcB = cksum_trim_leading(crcAB, lenAB, crcA, lenA);

  TEST_ASSERT_EQUAL_UINT(crcB, 0xffffffffUL); // cksum for ''
}

/* ========================================================================= */
void test_cksum_trim_leading_invalid_zero_lenA(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenA;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcA  = 0xc91eafc6UL; // cksum for 'this'
  lenAB = 8L;
  lenA  = 0L;

  crcB = cksum_trim_leading(crcAB, lenAB, crcA, lenA);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x3fa2960aUL); // cksum for 'thisthat'
}

/* ========================================================================= */
void test_cksum_trim_leading_invalid_zero_lenB(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenA;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcA  = 0xc91eafc6UL; // cksum for 'this'
  lenAB = 4L;
  lenA  = 4L;

  crcB = cksum_trim_leading(crcAB, lenAB, crcA, lenA);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x3fa2960aUL); // cksum for 'thisthat'
}

/* ========================================================================= */
void test_cksum_trim_leading_invalid_zero_lenAB(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenA;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcA  = 0xc91eafc6UL; // cksum for 'this'
  lenAB = 0L;
  lenA  = 4L;

  crcB = cksum_trim_leading(crcAB, lenAB, crcA, lenA);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x3fa2960aUL); // cksum for 'thisthat'
}

/* ========================================================================= */
void test_cksum_trim_leading_invalid_neg_lenA(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenA;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcA  = 0xc91eafc6UL; // cksum for 'this'
  lenAB = 8L;
  lenA  = -1L;

  crcB = cksum_trim_leading(crcAB, lenAB, crcA, lenA);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x3fa2960aUL); // cksum for 'thisthat'
}

/* ========================================================================= */
void test_cksum_trim_leading_invalid_neg_lenB(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenA;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcA  = 0xc91eafc6UL; // cksum for 'this'
  lenAB = 3L;
  lenA  = 4L;

  crcB = cksum_trim_leading(crcAB, lenAB, crcA, lenA);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x3fa2960aUL); // cksum for 'thisthat'
}

/* ========================================================================= */
void test_cksum_trim_leading_invalid_neg_lenAB(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenAB;
  long lenA;

  crcAB = 0x3fa2960aUL; // cksum for 'thisthat'
  crcA  = 0xc91eafc6UL; // cksum for 'this'
  lenAB = -1L;
  lenA  = 4L;

  crcB = cksum_trim_leading(crcAB, lenAB, crcA, lenA);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x3fa2960aUL); // cksum for 'thisthat'
}
