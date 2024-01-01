#ifndef S21_HELPERS_H
#define S21_HELPERS_H

#include "s21_decimal.h"
#define DECIMALTEN                   \
  (big_decimal) {                    \
    .bits = { 10, 0, 0, 0, 0, 0, 0 } \
  }

#define INTMAX 0x7fffffff
#define TRUE 1
#define FALSE 0
#define UINTMAX 0xffffffff
#define EXPMASK (0b00000000111111110000000000000000)

typedef unsigned bit_t;

typedef struct {
  unsigned bits[7];
} big_decimal;

bit_t getBit(big_decimal value, unsigned num);
void setBit(big_decimal *value, unsigned num, bit_t bitValue);
int helperSummSub(big_decimal value1, big_decimal value2, big_decimal *result);
unsigned getExp(big_decimal value);
void setExp(big_decimal *value, unsigned exp);
bit_t getSign(big_decimal value);
void setSign(big_decimal *value, bit_t sign);
void print_binary(unsigned int number);
int shiftLeft(big_decimal *num, int shift);
void print_decimal(big_decimal num);
int bigDecimalIsLess(big_decimal value1, big_decimal value2);
int bigDecimalIsGreater(big_decimal value1, big_decimal value2);
void mulToBigDecimal(big_decimal value1, big_decimal value2,
                     big_decimal *result);
void alignmentExp(big_decimal *value1, big_decimal *value2);
void toBigDecimal(s21_decimal value1, big_decimal *bigValue1);
bit_t fromBigDecimal(big_decimal bigValue, s21_decimal *value);
void truncateZeroesAtTheEnd(big_decimal *value);
int shiftRight(big_decimal *num, int shift);
int longDivision(big_decimal value1, big_decimal value2, big_decimal *result);

#endif