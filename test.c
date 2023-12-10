#include <stdio.h>
#include <string.h>

#include "s21_decimal.h"
#include "s21_helpers.h"

int main() {
  s21_decimal num1 = {.bits = {UINTMAX, 234234, 0, 0}};
  s21_decimal num2 = {.bits = {UINTMAX, 1233, 0, 0}};
  s21_decimal res = {};
  // s21_mul(num1, num2, &res);
  print_decimal(num1);
  print_decimal(num2);
  // s21_add(num1, num2, &res);
  s21_sub(num1, num2, &res);
  print_decimal(res);

  // printf("%d\n", getSign(num));
  // setSign(&num,
  // 1);11100011100010100100000000000000000000000000000000
  //    111000111000101001                               0
  // printf("%d\n", getSign(num));
  // setSign(&num, 0);
  // printf("%d\n", getSign(num));
  // printf("%d\n", getExp(num));
  // setExp(&num, 10);
  // printf("%d\n", getExp(num));
  // setExp(&num, 28);
  // printf("%d\n", getExp(num));
  // setExp(&num, 1);
  // printf("%d\n", getExp(num));
  // setExp(&num, 0);
  // printf("%d\n", getExp(num));
  // setBit(&num, 32, 1);
  // printf("%d\n", getBit(num, 32));
  // setBit(&num, 32, 0);
  // printf("%d\n", getBit(num, 32));
  // setBit(&num, 33, 1);
  // printf("%d\n", getBit(num, 33));
  // setBit(&num, 33, 0);
  // printf("%d\n", getBit(num, 33));
  // setBit(&num, 67, 1);
  // printf("%d\n", getBit(num, 67));
  // setBit(&num, 67, 0);
  // printf("%d\n", getBit(num, 67));
  // setBit(&num, 95, 1);
  // printf("%d\n", getBit(num, 95));
  // setBit(&num, 95, 0);
  // printf("%d\n", getBit(num, 95));
  return 0;
}