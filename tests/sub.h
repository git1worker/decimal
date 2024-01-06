#include "test.h"

/* Initialzation in the array of bits is reversed. Pay attention!*/

START_TEST(test_s21_sub1) {
  s21_decimal dec = {.bits = {0b11000001110110101111110110011110,
                              0b00111110001001010000001001100001,
                              0b11000001110110101111110110011110, 0}};
  s21_decimal dec2 = {.bits = {0b11000001110110101111110110011110,
                               0b00111110001001010000001001100001,
                               0b00111110001001010000001001100001, 0}};
  s21_decimal dec3 =
      (s21_decimal){.bits = {0b10000011101101011111101100111100,
                             0b01111100010010100000010011000011,
                             0b11111111111111111111111111111111, 0}};
  s21_decimal res = {};
  s21_add(dec, dec2, &res);
  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_sub2) {
  s21_decimal dec = {.bits = {0b11000001110110101111110110011110,
                              0b00111110001001010000001001100001,
                              0b11000001110110101111110110011110, 0}};
  s21_decimal dec2 = {.bits = {0b11000001110110101111110110011110,
                               0b00111110001001010000001001100001,
                               0b00111110001001010000001001100001, 0}};
  s21_decimal dec3 =
      (s21_decimal){.bits = {0b10000011101101011111101100111100,
                             0b01111100010010100000010011000011,
                             0b11111111111111111111111111111111, 0}};
  s21_decimal res = {};
  s21_add(dec, dec2, &res);
  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
}
END_TEST;

Suite *testAdd() {
  Suite *s = suite_create("s21_sub suite");
  TCase *tc = tcase_create("");
  tcase_add_test(tc, test_s21_sub1);
  tcase_add_test(tc, test_s21_sub2);
  suite_add_tcase(s, tc);
  return s;
}