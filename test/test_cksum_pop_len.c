#include "unity.h"
#include "crc32trim.h"

void test_cksum_pop_len(void) {
  unsigned long crc;
  long len;

  crc = 0xc91eafc6UL; // cksum for 'this'
  len = 4L;

  crc = cksum_pop_len(crc, len);

  TEST_ASSERT_EQUAL_UINT(crc, 0xd85c7e3fUL); // crc32posix for 'this'
}
