#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include "s21_decimal.h"
#define DECIMALTEN          \
  (s21_decimal) {           \
    .bits = { 0, 0, 0, 10 } \
  }
#define INTMAX 0x7fffffff
#define TRUE 1
#define FALSE 0
#define UINTMAX 0xffffffff
#define EXPMASK (0b00000000111111110000000000000000)

typedef unsigned bit_t;

bit_t getBit(s21_decimal value, unsigned num);
void setBit(s21_decimal *value, unsigned num, bit_t bitValue);
unsigned getExp(s21_decimal value);
void setExp(s21_decimal *value, unsigned exp);
bit_t getSign(s21_decimal value);
void setSign(s21_decimal *value, bit_t sign);
void print_binary(unsigned int number);
int shiftLeft(s21_decimal *num, int shift);
void print_decimal(s21_decimal num);

#endif