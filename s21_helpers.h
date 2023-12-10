#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include "s21_decimal.h"
#define DECIMALTEN          \
  (s21_decimal) {           \
    .bits = { 0, 0, 0, 10 } \
  }

unsigned getBit(s21_decimal value, unsigned num);
void setBit(s21_decimal *value, unsigned num, unsigned bitValue);
unsigned getExp(s21_decimal value);
void setExp(s21_decimal *value, unsigned exp);
unsigned getSign(s21_decimal value);
void setSign(s21_decimal *value, unsigned sign);
void print_binary(unsigned int number);
int shiftLeft(s21_decimal *num, int shift);
void print_decimal(s21_decimal num);

#endif