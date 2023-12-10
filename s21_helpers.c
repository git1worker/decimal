#include "s21_helpers.h"

#include <stdio.h>

#include "s21_decimal.h"

#define INTMAX 0x7fffffff
#define TRUE 1
#define FALSE 0
#define UINTMAX 0xffffffff
#define EXPMASK (0b00000000111111110000000000000000)

/* bits[3] [31] [30...24] [23...16] [15...0]
 *        |sign|null     |exp      |null    |
 */

unsigned getBit(s21_decimal value, unsigned num) {
  return (value.bits[num / 32] >> num % 32) & 1;
}

void setBit(s21_decimal *value, unsigned num, unsigned bitValue) {
  unsigned corrBit = 1 << (num % 32);
  if (bitValue) {
    *((*value).bits + (num / 32)) = *((*value).bits + (num / 32)) | corrBit;
  } else {
    unsigned invertedMask = UINTMAX - corrBit;
    *((*value).bits + (num / 32)) =
        *((*value).bits + (num / 32)) & invertedMask;
  }
}

unsigned getExp(s21_decimal value) { return (value.bits[3] & EXPMASK) >> 16; }

void setExp(s21_decimal *value, unsigned exp) {
  exp = exp << 16;
  value->bits[3] = value->bits[3] & (UINTMAX - EXPMASK);
  value->bits[3] = value->bits[3] | exp;
}

unsigned getSign(s21_decimal value) { return value.bits[3] >> 31; }

void setSign(s21_decimal *value, unsigned sign) {
  setBit(value, 32 * 4 - 1, sign);
}

int shiftLeft(s21_decimal *num, int shift) {
  int ec = 0;
  s21_decimal converted = *num;
  /* ec = 0 OK
   * ec = 1 Overflow
   */
  while (shift != 0 && !ec) {
    if (getBit(converted, 95))
      ec = 1;
    else {
      converted.bits[2] = converted.bits[2] << 1;
      if (getBit(converted, 63)) setBit(&converted, 64, 1);
      converted.bits[1] = converted.bits[1] << 1;
      if (getBit(converted, 31)) setBit(&converted, 32, 1);
      converted.bits[0] = converted.bits[0] << 1;
      --shift;
    }
  }
  if (!ec) *num = converted;
  return ec;
}

void reverse(char str[], int length) {
  int start = 0;
  int end = length - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    end--;
    start++;
  }
}

// Implementation of citoa()
char *citoa(unsigned long num, char *str, int base) {
  int i = 0;

  /* Handle 0 explicitly, otherwise empty string is
   * printed for 0 */
  if (!num) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  // Process individual digits
  while (num != 0) {
    int rem = num % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / base;
  }

  str[i] = '\0';  // Append string terminator

  // Reverse the string
  reverse(str, i);

  return str;
}

void print_decimal(s21_decimal num) {
  char buffer[40] = {};
  for (int i = 2; i > -1; --i) {
    citoa(num.bits[i], buffer, 2);
    printf("|%32s", buffer);
  }
  putchar('|');
  putchar('\n');
}
