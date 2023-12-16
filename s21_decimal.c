#include "s21_decimal.h"

#include <stdint.h>
#include <string.h>

#include "s21_helpers.h"

/*
  0 - OK
  1 - число слишком велико или равно бесконечности
  2 - число слишком мало или равно отрицательной бесконечности
  3 - деление на 0
*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal result_ = *result;
  // bit_t sign1 = getSign(value_1);
  // bit_t sign2 = getSign(value_2);
  // if (sign1 == sign2) {
  // } else {
  //   // TODO:
  // }

  return 0;
}
// 10001011011111010010100011001011
// 10001011011111010010100011001011
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ec = 0;

  return 0;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal numsForSumm[(sizeof(s21_decimal) - sizeof(unsigned)) * 8] = {};
  int ec = 0;
  // s21_decimal outcome = {};
  // for (int bit = 0; bit < (sizeof(s21_decimal) - sizeof(unsigned)) * 8;
  // ++bit) {
  //   if (getBit(value_2, bit)) {
  //     numsForSumm[bit] = value_1;
  //     shiftLeft(&(numsForSumm[bit]), bit);
  //     s21_add(outcome, numsForSumm[bit], &outcome);
  //   }
  // }
  return ec;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return 0;
}

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  bit_t rv = 0;
  // unsigned exp1 = getExp(value1);
  // unsigned exp2 = getExp(value2);
  // bit_t sign1 = getSign(value1);
  // bit_t sign2 = getSign(value2);
  // // TODO
  // if (sign1 == sign2) {
  //   while (exp1 > exp2) {
  //   }
  //   /* Exponents are equal */

  // } else {
  //   if (sign1 > sign2)
  //     rv = TRUE;
  //   else
  //     rv = FALSE;
  // }
  return 0;
}
