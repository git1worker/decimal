#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"
#include "s21_helpers.h"

/* Initialzation in the array of bits is reversed. Pay attention!*/

START_TEST(test_s21_shifts) {
  big_decimal dec = {.bits = {0b101101, 0, 0, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b1011010000000000, 0, 0, 0, 0, 0, 0}};
  shiftLeft(&dec, 10);
  ck_assert(!memcmp(&dec, &dec2, sizeof(dec)));
  big_decimal dec3 = {
      .bits = {0b10000000000000000000000000000000, 0b10110, 0, 0, 0, 0, 0}};
  shiftLeft(&dec, 21);
  ck_assert(!memcmp(&dec, &dec3, sizeof(dec)));
  shiftRight(&dec, 21);
  ck_assert(!memcmp(&dec, &dec2, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_longDiv) {
  big_decimal dec = {.bits = {0b101101, 0, 0, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b101, 0, 0, 0, 0, 0, 0}};
  big_decimal dec3 = (big_decimal){.bits = {0b1001, 0, 0, 0, 0, 0, 0}};
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

START_TEST(test_s21_GetSetBit) {
  big_decimal dec = {
      .bits = {0, 0b100110000000000100010000000, UINT32_MAX, 0, 0, 0, 0}};
  ck_assert(getBit(dec, 32 + 26));
  ck_assert(!getBit(dec, 32 + 25));
  ck_assert(!getBit(dec, 32 + 24));
  ck_assert(getBit(dec, 32 + 23));
  ck_assert(getBit(dec, 32 + 22));
  ck_assert(getBit(dec, 32 * 3 - 1));
  ck_assert(!getBit(dec, 32 * 3));
  setBit(&dec, 32 * 3, 1);
  ck_assert(getBit(dec, 32 * 3));
  setBit(&dec, 0, 1);
  ck_assert(getBit(dec, 0));
}
END_TEST;

START_TEST(test_s21_exponents) {
  /* Exp value U [0, 28]; */
  big_decimal dec = {
      .bits = {0, 0b100110000000000100010000000, UINT32_MAX, 0, 0, 0, 0}};
  setExp(&dec, 0b1010);

  ck_assert(dec.bits[6] == 0b1010 << 16);
  ck_assert(getExp(dec) == 0b1010);
  setExp(&dec, 28);
  ck_assert(dec.bits[6] == 28 << 16);
  ck_assert(getExp(dec) == 28);
}
END_TEST;

START_TEST(test_s21_mulToBigDec) {
  // print ("{0:b}".format(
  // -int('100100010011000000000000000|11110110000000011100000001000000|11111111111001111111111111111111',
  // 2) +
  //   int('111100000001100000001011|11100000011111111110000000000000|00011011001101100100010000111101',
  // 2)) )
  big_decimal dec = {.bits = {0b11111111111001111111111111111111,
                              0b11110110000000011100000001000000,
                              0b100100010011000000000000000, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b00011011001101100100010000111101,
                               0b11100000011111111110000000000000,
                               0b111100000001100000001011, 0, 0, 0, 0}};
  big_decimal dec3 = (big_decimal){.bits = {0b01111111000100011011101111000011,
                                            0b10011101101011111010011001100110,
                                            0b00111011010101001001000100101111,
                                            0b10100001010000010010010101011000,
                                            0b00011010110010011100110011101110,
                                            0b1000100000101010101, 0}};
  big_decimal res = {};
  mulToBigDecimal(dec, dec2, &res);
  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_mulToBigDec2) {
  big_decimal dec = {.bits = {0b11111111111111111111111111111111,
                              0b11111111111111111111111111111111,
                              0b11111111111111111111111111111111, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b11111111111111111111111111111111,
                               0b11111111111111111111111111111111,
                               0b11111111111111111111111111111111, 0, 0, 0, 0}};
  big_decimal dec3 =
      (big_decimal){.bits = {0b00000000000000000000000000000001,
                             0b00000000000000000000000000000000,
                             0b00000000000000000000000000000000,
                             0b11111111111111111111111111111110,
                             0b11111111111111111111111111111111,
                             0b11111111111111111111111111111111, 0}};
  big_decimal res = {};
  mulToBigDecimal(dec, dec2, &res);
  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_alignmentExp) {
  big_decimal dec = {.bits = {1, 0, 0, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {1, 0, 0, 0, 0, 0, 0}};
  big_decimal dec3 = (big_decimal){
      .bits = {0b01010100000010111110010000000000, 0b10, 0, 0, 0, 0}};
  setExp(&dec3, 10);
  setExp(&dec, 10);

  alignmentExp(&dec, &dec2);
  ck_assert(!memcmp(&dec2, &dec3, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_alignmentExp2) {
  big_decimal dec = {.bits = {0b11111111111111111111111111111111,
                              0b11111111111111111111111111111111,
                              0b11111111111111111111111111111111, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b11111111111111111111111111111111,
                               0b11111111111111111111111111111111,
                               0b11111111111111111111111111111111, 0, 0, 0, 0}};
  big_decimal dec3 =
      (big_decimal){.bits = {0b11110000000000000000000000000000,
                             0b11000001110110101111110110011110,
                             0b11011111101100000011000110100001,
                             0b00001111111111111111111111111111,
                             0b00111110001001010000001001100001,
                             0b100000010011111100111001011110, 0}};
  setExp(&dec3, 28);
  setExp(&dec, 28);

  alignmentExp(&dec, &dec2);
  ck_assert(!memcmp(&dec2, &dec3, sizeof(dec)));
}
END_TEST;

int main(void) {
  Suite *s = suite_create("s21_suite");
  TCase *tc = tcase_create("");

  tcase_add_test(tc, test_s21_shifts);
  tcase_add_test(tc, test_s21_longDiv);
  tcase_add_test(tc, test_s21_longDiv2);
  tcase_add_test(tc, test_s21_longDiv3);
  tcase_add_test(tc, test_s21_GetSetBit);
  tcase_add_test(tc, test_s21_exponents);
  tcase_add_test(tc, test_s21_mulToBigDec);
  tcase_add_test(tc, test_s21_mulToBigDec2);
  tcase_add_test(tc, test_s21_alignmentExp);
  tcase_add_test(tc, test_s21_alignmentExp2);

  suite_add_tcase(s, tc);
  SRunner *sr;
  int number_failed = 0;

  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}