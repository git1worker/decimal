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
  int ec = 0;
  unsigned carry = 0;
  for (int bit = 0; bit < 3; ++bit) {
    for (int i = 0; i < 32; ++i) {
      bit_t b1 = getBit(value_1, bit * 32 + i);
      bit_t b2 = getBit(value_2, bit * 32 + i);
      bit_t b3 = b1 + b2 + carry;
      carry = b3 / 2;
      b3 = b3 % 2;
      setBit(result, bit * 32 + i, b3);
    }
  }
  // Overflow
  if (carry) ec = 1;
  return ec;
}
// 10001011011111010010100011001011
// 10001011011111010010100011001011
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ec = 0;
  bit_t loan = 0;
  /* Completed only for value1 > value2 
   * without handling of sign */

  for (int bit = 0; bit < 3; ++bit) {
    for (int i = 0; i < 32; ++i) {
      bit_t b1 = getBit(value_1, bit * 32 + i);
      bit_t b2 = getBit(value_2, bit * 32 + i);
      bit_t b3;
      if (b1 > b2)
        b3 = !loan, loan = FALSE;
      else if (b1 == b2)
        b3 = loan;
      else
        b3 = !loan, loan = TRUE;
      setBit(result, bit * 32 + i, b3);
    }
  }
  if (loan) /* TODO:*/
    ;
  return 0;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal numsForSumm[(sizeof(s21_decimal) - sizeof(unsigned)) * 8] = {};
  int ec = 0;
  s21_decimal outcome = {};
  for (int bit = 0; bit < (sizeof(s21_decimal) - sizeof(unsigned)) * 8; ++bit) {
    if (getBit(value_2, bit)) {
      numsForSumm[bit] = value_1;
      shiftLeft(&(numsForSumm[bit]), bit);
      s21_add(outcome, numsForSumm[bit], &outcome);
    }
  }
  return ec;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  
  return 0;
}
