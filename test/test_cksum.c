#include "unity.h"
#include "crc32trim.h"

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

void test_cksum_pop_len(void) {
  unsigned long crc;
  long len;

  crc = 0xc91eafc6UL; // cksum for 'this'
  len = 4L;

  crc = cksum_pop_len(crc, len);

  TEST_ASSERT_EQUAL_UINT(crc, 0xd85c7e3fUL); // crc32posix for 'this'
}

void test_cksum_push_len(void) {
  unsigned long crc;
  long len;

  crc = 0xd85c7e3fUL; // crc32posix for 'this'
  len = 4L;

  crc = cksum_push_len(crc, len);

  TEST_ASSERT_EQUAL_UINT(crc, 0xc91eafc6UL); // cksum for 'this'
}
