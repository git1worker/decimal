#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"
#include "s21_helpers.h"

START_TEST(test_s21_shifts) {
  big_decimal dec = {.bits = {0b101101, 0, 0, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b1011010000000000, 0, 0, 0, 0, 0, 0}};
  shiftLeft(&dec, 10);
  ck_assert(!memcmp(&dec, &dec2, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_longDiv) {
  big_decimal dec = {.bits = {0b101101, 0, 0, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b101, 0, 0, 0, 0, 0}};
  big_decimal dec3 = (big_decimal){.bits = {0b1001, 0, 0, 0, 0, 0}};
  big_decimal res = {};
  longDivision(dec, dec2, &res);
  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_longDiv2) {
  big_decimal dec = {
      .bits = {0, 0b100110000000000100010000000000, 0, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b1000, 0, 0, 0, 0, 0}};
  big_decimal dec3 =
      (big_decimal){.bits = {0, 0b100110000000000100010000000, 0, 0, 0, 0}};
  big_decimal res = {};
  longDivision(dec, dec2, &res);
  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_longDiv3) {
  big_decimal dec = {.bits = {0, 0b100110000000000100010000000, 0, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b1111111011, 0, 0, 0, 0, 0}};
  big_decimal dec3 =
      (big_decimal){.bits = {0, 0b10011000110000000, 0, 0, 0, 0}};
  big_decimal res = {};
  longDivision(dec, dec2, &res);
  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
}
END_TEST;

int main(void) {
  Suite *s = suite_create("s21_suite");
  TCase *tc = tcase_create("");

  tcase_add_test(tc, test_s21_shifts);
  tcase_add_test(tc, test_s21_longDiv);
  tcase_add_test(tc, test_s21_longDiv2);
  tcase_add_test(tc, test_s21_longDiv3);

  suite_add_tcase(s, tc);
  SRunner *sr;
  int number_failed = 0;

  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}