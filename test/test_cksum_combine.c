#include "unity.h"
#include "crc32trim.h"
#include <limits.h>

/* ========================================================================= */
void test_cksum_combine(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenA;
  long lenB;

  crcA  = 0xc91eafc6UL; // cksum for 'this'
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenA  = 4L;
  lenB  = 4L;

  crcAB = cksum_combine(crcA, lenA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0x3fa2960aUL); // cksum for 'thisthat'
}

/* ========================================================================= */
void test_cksum_combine_valid_zeros(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenA;
  long lenB;

  crcA  = 0xffffffffUL; // cksum for ''
  crcB  = 0xffffffffUL; // cksum for ''
  lenA  = 0L;
  lenB  = 0L;

  crcAB = cksum_combine(crcA, lenA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xffffffffUL); // cksum for ''
}

/* ========================================================================= */
void test_cksum_combine_valid_zero_leading(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenA;
  long lenB;

  crcA  = 0xffffffffUL; // cksum for ''
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenA  = 0L;
  lenB  = 4L;

  crcAB = cksum_combine(crcA, lenA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xf014b584UL); // cksum for 'that'
}

/* ========================================================================= */
void test_cksum_combine_valid_zero_trailing(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenA;
  long lenB;

  crcA  = 0xc91eafc6UL; // cksum for 'this'
  crcB  = 0xffffffffUL; // cksum for ''
  lenA  = 4L;
  lenB  = 0L;

  crcAB = cksum_combine(crcA, lenA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xc91eafc6UL); // cksum for 'this'
}

/* ========================================================================= */
void test_cksum_combine_invalid_zero_lenA(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenA;
  long lenB;

  crcA  = 0xc91eafc6UL; // cksum for 'this'
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenA  = 0L;
  lenB  = 4L;

  crcAB = cksum_combine(crcA, lenA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xc91eafc6UL); // cksum for 'this'
}

/* ========================================================================= */
void test_cksum_combine_invalid_zero_lenB(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenA;
  long lenB;

  crcA  = 0xc91eafc6UL; // cksum for 'this'
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenA  = 4L;
  lenB  = 0L;

  crcAB = cksum_combine(crcA, lenA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xc91eafc6UL); // cksum for 'this'
}

/* ========================================================================= */
void test_cksum_combine_invalid_neg_lenA(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenA;
  long lenB;

  crcA  = 0xc91eafc6UL; // cksum for 'this'
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenA  = 4L;
  lenB  = -1L;

  crcAB = cksum_combine(crcA, lenA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xc91eafc6UL); // cksum for 'this'
}

/* ========================================================================= */
void test_cksum_combine_invalid_neg_lenB(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenA;
  long lenB;

  crcA  = 0xc91eafc6UL; // cksum for 'this'
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenA  = 4L;
  lenB  = -1L;

  crcAB = cksum_combine(crcA, lenA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xc91eafc6UL); // cksum for 'this'
}

/* ========================================================================= */
void test_cksum_combine_invalid_too_big_lenAB(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenA;
  long lenB;

  crcA  = 0xc91eafc6UL; // cksum for 'this'
  crcB  = 0xf014b584UL; // cksum for 'that'
  lenA  = LONG_MAX;
  lenB  = LONG_MAX;

  crcAB = cksum_combine(crcA, lenA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0xc91eafc6UL); // cksum for 'this'
}
