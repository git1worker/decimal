#include "test.h"

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

START_TEST(test_s21_helpesSummSub) {
  big_decimal dec = {.bits = {0b11000001110110101111110110011110,
                              0b00111110001001010000001001100001,
                              0b11000001110110101111110110011110, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b11000001110110101111110110011110,
                               0b00111110001001010000001001100001,
                               0b00111110001001010000001001100001, 0, 0, 0, 0}};
  big_decimal dec3 =
      (big_decimal){.bits = {0b10000011101101011111101100111100,
                             0b01111100010010100000010011000011,
                             0b11111111111111111111111111111111, 0, 0, 0, 0}};
  big_decimal res = {};
  helperSummSub(dec, dec2, &res);

  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_helpesSummSub2) {
  big_decimal dec = {.bits = {0b11000001110110101111110110011110,
                              0b00111110001001010000001001100001,
                              0b11000001110110101111110110011110, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b11000001110110101111110110011110,
                               0b00111110001001010000001001100001,
                               0b00111110001001010000001001100001, 0, 0, 0, 0}};

  big_decimal dec3 = (big_decimal){
      .bits = {0, 0, 0b10000011101101011111101100111101, 0, 0, 0, 0}};
  setSign(&dec, 1);
  setSign(&dec3, 1);
  big_decimal res = {};
  helperSummSub(dec, dec2, &res);

  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_helpesSummSub3) {
  big_decimal dec = {.bits = {0b11000001110110101111110110011110,
                              0b00111110001001010000001001100001,
                              0b11000001110110101111110110011110, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b11000001110110101111110110011110,
                               0b00111110001001010000001001100001,
                               0b00111110001001010000001001100001, 0, 0, 0, 0}};
  big_decimal dec3 =
      (big_decimal){.bits = {0b10000011101101011111101100111100,
                             0b01111100010010100000010011000011,
                             0b11111111111111111111111111111111, 0, 0, 0, 0}};
  setSign(&dec, 1);
  setSign(&dec2, 1);
  setSign(&dec3, 1);
  big_decimal res = {};
  helperSummSub(dec, dec2, &res);

  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_truncZeroes) {
  big_decimal dec = {.bits = {0b11010110110110000,  // 110000
                              0, 0, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b10101011111000,  // 11000
                               0, 0, 0, 0, 0, 0}};
  big_decimal dec3 = (big_decimal){.bits = {0b10001001100,  // 1100
                                            0, 0, 0, 0, 0, 0}};
  big_decimal res = (big_decimal){.bits = {0b1011,  // 11
                                           0, 0, 0, 0, 0, 0}};

  setExp(&dec, 5);
  setExp(&dec2, 4);
  setExp(&dec3, 3);
  setExp(&res, 1);
  truncateZeroesAtTheEndAfterExp(&dec);
  truncateZeroesAtTheEndAfterExp(&dec2);
  truncateZeroesAtTheEndAfterExp(&dec3);
  ck_assert(!memcmp(&res, &dec3, sizeof(dec)));
  ck_assert(!memcmp(&res, &dec2, sizeof(dec)));
  ck_assert(!memcmp(&res, &dec, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_truncZeroes2) {
  big_decimal dec = {.bits = {0b11010110110110000,  // dec = 110000
                              0, 0, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b10101011111000,  // dec = 11000
                               0, 0, 0, 0, 0, 0}};

  setExp(&dec, 1);
  setExp(&dec2, 0);
  truncateZeroesAtTheEndAfterExp(&dec);
  ck_assert(!memcmp(&dec, &dec2, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_truncZeroes3) {
  big_decimal dec = {.bits = {0b11010110110110000,  // 1dec = 10000
                              0, 0, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0b11010110110110000,  // dec = 110000
                               0, 0, 0, 0, 0, 0}};
  truncateZeroesAtTheEndAfterExp(&dec);
  ck_assert(!memcmp(&dec, &dec2, sizeof(dec)));
}
END_TEST;

START_TEST(test_s21_truncZeroes4) {
  big_decimal dec = {.bits = {0,  // 1dec = 10000
                              0, 0, 0, 0, 0, 0}};
  big_decimal dec2 = {.bits = {0,  // dec = 110000
                               0, 0, 0, 0, 0, 0}};
  setExp(&dec, 10);
  truncateZeroesAtTheEndAfterExp(&dec);
  ck_assert(!memcmp(&dec, &dec2, sizeof(dec)));
}
END_TEST;

Suite *testHelpers() {
  Suite *s = suite_create("Helpers suite");
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
  tcase_add_test(tc, test_s21_helpesSummSub);
  tcase_add_test(tc, test_s21_helpesSummSub2);
  tcase_add_test(tc, test_s21_helpesSummSub3);
  tcase_add_test(tc, test_s21_truncZeroes);
  tcase_add_test(tc, test_s21_truncZeroes2);
  tcase_add_test(tc, test_s21_truncZeroes3);
  tcase_add_test(tc, test_s21_truncZeroes4);

  suite_add_tcase(s, tc);

  return s;
}