#include "s21_decimal.h"

#include <stdint.h>

#include "s21_helpers.h"

/*
  0 - OK
  1 - число слишком велико или равно бесконечности
  2 - число слишком мало или равно отрицательной бесконечности
  3 - деление на 0
*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ec = 0;
  unsigned carry = 0;
  for (int bit = 0; bit < 3; ++bit) {
    for (int i = 0; i < 32; ++i) {
      unsigned b1 = getBit(value_1, bit * 32 + i);
      unsigned b2 = getBit(value_2, bit * 32 + i);
      setBit(result, bit * 32 + i, carry);
      carry = (b1 + b2) > 1;
    }
  }
  // Overflow
  if (carry) ec = 1;
  return ec;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal numsForSumm[(sizeof(s21_decimal) - sizeof(unsigned)) * 8] = {};
  int ec = 0;
  for (int bit = 0; bit < (sizeof(s21_decimal) - sizeof(unsigned)) * 8; ++bit) {
    if (getBit(value_2, bit)) {
      numsForSumm[bit] = value_1;
    }
  }

  return ec;
}
