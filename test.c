#include <stdio.h>
#include <string.h>

#include "s21_decimal.h"
#include "s21_helpers.h"

int main() {
  /* Initialzation in array bits is reversed. Pay attention!*/
  big_decimal num1 = {.bits = {123456789, 123456789, 0, 0, 0, 0, 0}};
  big_decimal num2 = {.bits = {123456789, 123456789, 0, 0, 0, 0, 0}};
  big_decimal res = {};

  


  return 0;
}

// print_decimal(num1);
  // print_decimal(num2);
  //  helperSummSub(num1, num2, &res); 1001001100101100000001011010010
  //  print_decimal(res);              1001001100101100000001011010010
  // setExp(&num1, 0);
  // setExp(&num2, 1);
  // printf("%d = 0\n", bigDecimalIsGreater(num1, num2));
  // big_decimal num3 = {.bits = {123456789, 123456789, 0, 0, 0, 0, 0}};
  // setExp(&num3, 1);
  // setSign(&num3, 1);
  // setSign(&num2, 1);
  // printf("%d = 2\n", bigDecimalIsLess(num3, num2));

  // big_decimal num4 = {.bits = {0, 0, 0, 0, 234234, 0, 0}};
  // printf("%d = 1\n", bigDecimalIsLess(num2, num4));
  // big_decimal num5 = {.bits = {0, 0, 0, 234234, 234234, 0, 0}};
  // setSign(&num5, 1);
  // printf("%d = 1\n", bigDecimalIsLess(num5, num2));
  // big_decimal num6 = {.bits = {0, 0, 0, 0, 1233, 0, 0}};
  // setExp(&num6, 1);
  // printf("%d = 1\n", bigDecimalIsLess(num6, num2));
  // big_decimal num7 = {.bits = {0, 0, 0, 0, 1233, 0, 0}};
  // setExp(&num7, 2);
  // printf("%d = 1\n", bigDecimalIsLess(num7, num6));

/*
print ("{0:b}".format(
-int('100100010011000000000000000000000000011110110000000000000000000000000000000011111111111111111111111111111111',
2) +
  int('11110000000000000000000000010111110000000000000000000000000000000000000011011001101100100010000111101',
2)) )

#                        0000000000000000000000000
#11011001101100100010000111100|11100100110010011011101111000011 |
#11011001101100100010000111100|11100100110010011011101111000011

# Multiply
#
10001000000111010000000000001101011111110110100100000000000000001011011100011110011101101011011010011100001101110000100110001001011000110010101110001101100110110010001000011110011100100110010011011101111000011
#
110101111000001101000|00000000000000010110111000011110|11101101011011010101110011011000|00010011000100101100100001000011|00011011001101100100010001000000|11100100110010011011101110111111

# Summ
#
100100110001000000000000000000000011011100110000000000000000000000000000000100011011001101100100010000111100
#
100100110001000000000000000000000011011100110000000000000000000000000000000100011011001101100100010000111100

# -Summ
#
-100011110100111111111111111111111101100000110000000000000000000000000000000011100100110010011011101111000010
#
100011110100111111111111111111111101100000110000000000000000000000000000000011100100110010011011101111000010
*/

// shiftLeft(&num1, 1);
// print_decimal(num1);
// shiftLeft(&num1, 32);
// print_decimal(num1);
// shiftLeft(&num1, 64);
// print_decimal(num1);
// shiftLeft(&num1, 10);
// print_decimal(num1);
// shiftLeft(&num1, 10);
// print_decimal(num1);
// shiftLeft(&num1, 9);
// print_decimal(num1);
// shiftLeft(&num1, 1);
// print_decimal(num1);
// shiftLeft(&num1, 1);
// print_decimal(num1);

// setSign(&num1, 1);
// setSign(&num2, 1);
// setExp(&num1, 7);
// print_decimal(num1);
// print_decimal(num2);
// printf("%d\n", getSign(num1));

// printf("%d\n", getSign(num1));
// setSign(&num1, 0);
// printf("%d\n", getSign(num1));
// printf("%d\n", getExp(num1));
// setExp(&num1, 10);
// printf("%d = 10\n", getExp(num1));
// setExp(&num1, 28);
// printf("%d = 28\n", getExp(num1));
// setExp(&num1, 1);
// printf("%d = 1\n", getExp(num1));
// setExp(&num1, 0);
// printf("%d = 0\n", getExp(num1));
// setBit(&num1, 128, 1);
// printf("%d = 1\n", getBit(num1, 128));
// setBit(&num1, 129, 0);
// printf("%d = 0\n", getBit(num1, 129));
// setBit(&num1, 160, 1);
// printf("%d = 1\n", getBit(num1, 160));
// setBit(&num1, 191, 0);
// printf("%d = 0\n", getBit(num1, 191));
// setBit(&num1, 0, 1);
// printf("%d = 1\n", getBit(num1, 0));
// setBit(&num1, 67, 0);
// printf("%d = 0\n", getBit(num1, 67));
// setBit(&num1, 95, 1);
// printf("%d = 1\n", getBit(num1, 95));
// setBit(&num1, 111, 0);
// printf("%d = 0\n", getBit(num1, 111));