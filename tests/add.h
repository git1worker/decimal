#include "test.h"

/* Initialzation in the array of bits is reversed. Pay attention!*/

START_TEST(test_s21_add1) {
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

START_TEST(test_s21_add2) {
  s21_decimal dec = {.bits = {0b11001000101010101011000110101010,
                              0b110101010100101100111101100, 0, 0}};
  s21_decimal dec2 = {.bits = {0b11111101010110101011111111101010,
                               0b01010001010101010100101010101111, 0b101001,
                               0}};
  s21_decimal dec3 =
      (s21_decimal){.bits = {0b00110100101100000000111001000000,
                             0b01001010101010101111000011000011, 0b101001, 0}};
  s21_decimal res = {};
  setSign_(&dec, 1);
  s21_add(dec, dec2, &res);
  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_add3) {
  s21_decimal dec = {.bits = {0b11001000101010101011000110101010,
                              0b110101010100101100111101100, 0, 0}};
  s21_decimal dec2 = {.bits = {0b11111101010110101011111111101010,
                               0b01010001010101010100101010101111, 0b101001,
                               0}};
  s21_decimal dec3 =
      (s21_decimal){.bits = {0b11000110000001010111000110010100,
                             0b01010111111111111010010010011100, 0b101001, 0}};
  s21_decimal res = {};
  setSign_(&dec, 1);
  setSign_(&dec2, 1);
  setSign_(&dec3, 1);
  s21_add(dec, dec2, &res);
  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_add4) {
  // TODO: exponents
  s21_decimal dec = {.bits = {0b11001000101010101011000110101010,
                              0b110101010100101100111101100, 0, 0}};
  s21_decimal dec2 = {.bits = {0b11111101010110101011111111101010,
                               0b01010001010101010100101010101111, 0b101001,
                               0}};
  s21_decimal dec3 =
      (s21_decimal){.bits = {0b11000110000001010111000110010100,
                             0b01010111111111111010010010011100, 0b101001, 0}};
  s21_decimal res = {};
  setSign_(&dec, 1);
  setSign_(&dec2, 1);
  setSign_(&dec3, 1);
  s21_add(dec, dec2, &res);
  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
}
END_TEST;

Suite *testAdd() {
  Suite *s = suite_create("s21_add suite");
  TCase *tc = tcase_create("");
  tcase_add_test(tc, test_s21_add1);
  tcase_add_test(tc, test_s21_add2);
  tcase_add_test(tc, test_s21_add3);

  suite_add_tcase(s, tc);
  return s;
}