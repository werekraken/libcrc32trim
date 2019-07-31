#include "unity.h"
#include "crc32trim.h"

void test_cksum_combine_no_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcA  = 0xd85c7e3fUL; // cksum (no len) for 'this'
  crcB  = 0x4c536d68UL; // cksum (no len) for 'that'
  lenB  = 4L;

  crcAB = cksum_combine_no_len(crcA, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcAB, 0x620d7ac6UL); // cksum (no len) for 'thisthat'
}

void test_cksum_trim_leading_no_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x620d7ac6UL; // cksum (no len) for 'thisthat'
  crcA  = 0xd85c7e3fUL; // cksum (no len) for 'this'
  lenB  = 4L;

  crcB = cksum_trim_leading_no_len(crcAB, crcA, lenB);

  TEST_ASSERT_EQUAL_UINT(crcB, 0x4c536d68UL); // cksum (no len) for 'that'
}

void test_cksum_trim_trailing_no_len(void) {
  unsigned long crcA;
  unsigned long crcAB;
  unsigned long crcB;
  long lenB;

  crcAB = 0x620d7ac6UL; // cksum (no len) for 'thisthat'
  crcB  = 0x4c536d68UL; // cksum (no len) for 'that'
  lenB  = 4L;

  crcA = cksum_trim_trailing_no_len(crcAB, crcB, lenB);

  TEST_ASSERT_EQUAL_UINT(crcA, 0xd85c7e3fUL); // cksum (no len) for 'this'
}
