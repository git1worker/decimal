#include <stdio.h>
#include <string.h>

#include "s21_decimal.h"
#include "s21_helpers.h"

int main() {
  s21_decimal num1 = {};
  s21_decimal num2 = {};
  s21_decimal res = {};
  // s21_mul(num1, num2, &res);
  setBit(&num1, 0, 1);
  int ec = 0;
  for (int i = 0; i < 96 && !ec; ++i) {
    ec = shiftLeft(&num1, 2);
    print_decimal(num1);
  }

  // printf("%d\n", getSign(num));
  // setSign(&num, 1);
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