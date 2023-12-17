#include "s21_helpers.h"

#include <stdio.h>
#include <string.h>

#include "s21_decimal.h"

/* bits[3] [31] [30...24] [23...16] [15...0]
 *        |sign|null     |exp      |null    |
 * TODO: Signs
 */

void truncateZeroesAtTheEnd(big_decimal *value) {
  // TODO:
  /* Exponent = 0
   * longDivision
  */
}

int longDivision(big_decimal value1, big_decimal value2, big_decimal *result) {
  /* Searching for a number for the first digit in the quotient 
   * Without handling exponents*/
  unsigned posFirstDigit = UINTMAX;
  big_decimal result_ = *result;
  int rv = 0;
  for (int i = 6 * 32 - 1; i >= 0 && posFirstDigit == UINTMAX; --i) {
    if (getBit(value1, i)) posFirstDigit = i;
  }
  // TODO if posFirstDigit == UINTMAX here
  bit_t br = TRUE;
  big_decimal absValue1 = value1;
  setSign(&absValue1, 0);
  setExp(&absValue1, 0);
  big_decimal absValue2 = value2;
  setSign(&absValue2, 0);
  setExp(&absValue2, 0);
  unsigned posEndFirstDigit = posEndFirstDigit;
  /* TODO: Need to handle situation when at the begin divisible < divisor (3 / 33) */
  while (br) {
    big_decimal tmpShifted = absValue1;
    shiftRight(&tmpShifted, posEndFirstDigit);
    if (bigDecimalIsGreater(tmpShifted, absValue2)) {
      br = FALSE;
      setBit(&result_, 0, 1);
      
    }
    else {
      if (posEndFirstDigit > 0)
        --posEndFirstDigit;
      else /* TODO */;
    }
  }
  setSign(&absValue2, 1);
  big_decimal tmpValue = absValue1;
  shiftRight(&tmpValue, posEndFirstDigit);
  while (posEndFirstDigit > 0) {
    shiftLeft(&result_, 1);
    big_decimal tmpValue_;
    /* Subtraction */
    helperSummSub(tmpValue, absValue2, &tmpValue_);
    --posEndFirstDigit;
    // TODO to do refactor this part
    if (posEndFirstDigit > 0) {
      shiftLeft(&tmpValue_, 1);
      setBit(&tmpValue_, 0, getBit(value1, posEndFirstDigit));
      while (bigDecimalIsLess(tmpValue_, absValue2) == 1 && posEndFirstDigit > 0) {
        --posEndFirstDigit;
        shiftLeft(&tmpValue_, 1);
        setBit(&tmpValue_, 0, getBit(value1, posEndFirstDigit));
        shiftLeft(&result_, 0);
      }
      tmpValue = tmpValue_;
    } else {
      // TODO calculate the remains
    }
    
  }
}

int divisionBigDecimal(big_decimal value1, big_decimal value2, big_decimal *result) {
  /* 
   * rv = 0 Ok Without remainder
   * rv = 1 Ok With remainder
   * rv = 3 Division by zero
  */
  int rv = 0;
  bit_t sign1 = getSign(value1);
  bit_t sign2 = getSign(value2);
  unsigned exp1 = getExp(value1);
  unsigned exp2 = getExp(value2);
  /* Check division by zero */
  setSign(&value2, 0);
  setExp(&value2, 0);
  if (bigDecimalIsLess(value2, (big_decimal){.bits = {0, 0, 0, 0, 0, 0, 0}}) == 2) 
    rv = 3;
  else {
    setSign(&value2, sign2);
    setExp(&value2, exp2);
    // TODO
  }
  return rv;
}

void toBigDecimal(s21_decimal value1, big_decimal *bigValue1) {
  /* It is assumed that the bigValue is empty and all bits are zero */
  bigValue1->bits[6] = value1.bits[3];
  bigValue1->bits[0] = value1.bits[0];
  bigValue1->bits[1] = value1.bits[1];
  bigValue1->bits[2] = value1.bits[2];
}

/*
  0 - OK
  1 - число слишком велико или равно бесконечности
  2 - число слишком мало или равно отрицательной бесконечности
*/
bit_t fromBigDecimal(big_decimal bigValue, s21_decimal *value) {
  /* Is is not assumed for exponential values.
   * Check only quantity of digits */
  bit_t rv = 0;
  bit_t sign = getSign(bigValue);
  /* Overflow check */
  if (bigDecimalIsGreater(bigValue, (big_decimal){.bits = {{UINTMAX, UINTMAX, UINTMAX, 0, 0, 0, 0}}}) == 1) 
    rv = 1;
  else if (bigDecimalIsLess(bigValue, (big_decimal){.bits = {{UINTMAX, UINTMAX, UINTMAX, 0, 0, 0, (UINTMAX + 1) / 2}}}) == 1)
    rv = 2;
  else {
    setSign(&bigValue, sign);
    value->bits[3] = bigValue.bits[6];
    value->bits[0] = bigValue.bits[0];
    value->bits[1] = bigValue.bits[1];
    value->bits[2] = bigValue.bits[2];
  }
}

int bigDecimalIsLess(big_decimal value1, big_decimal value2) {
  /* Tested */
  bit_t rv = FALSE;
  /* rv = 1 value1 < value2
   * rv = 0 value1 > value2
   * rv = 2 value1 == value2
   */
  bit_t sign1 = getSign(value1);
  bit_t sign2 = getSign(value2);
  if (sign1 == sign2) {
    alignmentExp(&value1, &value2);
    /* Exponents already are equal */
    bit_t br = TRUE;
    print_decimal(value1);
    print_decimal(value2);
    for (int i = (sizeof(big_decimal) - sizeof(unsigned)) * 8 - 1; i >= 0 && br;
         --i) {
      bit_t b1 = getBit(value1, i);
      bit_t b2 = getBit(value2, i);
      if (b1 == b2)
        continue;
      else if (b1 < b2)
        rv = TRUE;
      br = FALSE;
    }
    if (br) /* If the values are equal */
      rv = 2;
    else if (sign1)
      rv = !rv;
  } else {
    if (sign1 > sign2)
      rv = TRUE;
    else
      rv = FALSE;
  }
  return rv;
}

int bigDecimalIsGreater(big_decimal value1, big_decimal value2) {
  /* Tested */
  int rv = bigDecimalIsLess(value1, value2);
  if (rv == 1)
    rv = 0;
  else if (!rv)
    rv = 1;
  return rv;
}

void mulToBigDecimal(big_decimal value1, big_decimal value2,
                     big_decimal *result) {
  /* Tested */
  /* It is assumed that the values will not exceed s21_decimal */
  big_decimal numForSumm = {};
  big_decimal outcome = {};
  bit_t sign1 = getSign(value1);
  bit_t sign2 = getSign(value2);
  setSign(&value1, 0);
  setSign(&value1, 0);
  for (int bit = 0; bit < (sizeof(big_decimal) - sizeof(unsigned)) * 8; ++bit) {
    if (getBit(value2, bit)) {
      numForSumm = value1;
      shiftLeft(&(numForSumm), bit);
      helperSummSub(outcome, numForSumm, &outcome);
    }
  }
  setExp(&outcome, getExp(value1) + getExp(value2));
  setSign(&outcome, sign1 ^ sign2);
  *result = outcome;
}

int helperSummSub(big_decimal value1, big_decimal value2, big_decimal *result) {
  /* Tested */
  /* It is assumed that the exponents are equal */
  int ec = 0;
  big_decimal result_ = *result;
  bit_t sign1 = getSign(value1);
  bit_t sign2 = getSign(value2);
  if (sign1 == sign2) {
    unsigned carry = 0;
    for (int bit = 0; bit < 6; ++bit) {
      for (int i = 0; i < 32; ++i) {
        bit_t b1 = getBit(value1, bit * 32 + i);
        bit_t b2 = getBit(value2, bit * 32 + i);
        bit_t b3 = b1 + b2 + carry;
        carry = b3 / 2;
        b3 = b3 % 2;
        setBit(&result_, bit * 32 + i, b3);
      }
    }
    setSign(&result_, sign1);
    // Overflow
    if (carry) ec = 1;
  } else {
    bit_t sign;
    big_decimal *majorValue, *minorValue;

    big_decimal tmpValue1 = value1;
    big_decimal tmpValue2 = value2;
    setSign(&tmpValue1, 0);
    setSign(&tmpValue2, 0);

    if (/* Abs value */ bigDecimalIsGreater(tmpValue1, tmpValue2) == 1) {
      sign = getSign(value1);
      majorValue = &value1;
      minorValue = &value2;
    } else {
      sign = getSign(value2);
      if (/* Values are equal */ bigDecimalIsGreater(tmpValue1, tmpValue2) == 2)
        sign = FALSE;
      majorValue = &value2;
      minorValue = &value1;
    }
    setSign(&result_, sign);
    bit_t loan = 0;
    for (int bit = 0; bit < 6; ++bit) {
      for (int i = 0; i < 32; ++i) {
        bit_t b1 = getBit(*majorValue, bit * 32 + i);
        bit_t b2 = getBit(*minorValue, bit * 32 + i);
        bit_t b3;
        if (b1 > b2)
          b3 = !loan, loan = FALSE;
        else if (b1 == b2)
          b3 = loan;
        else
          b3 = !loan, loan = TRUE;
        setBit(&result_, bit * 32 + i, b3);
      }
    }
  }
  if (!ec) *result = result_;
}

bit_t getBit(big_decimal value, unsigned num) {
  /* Tested */
  return (value.bits[num / 32] >> num % 32) & 1;
}

void setBit(big_decimal *value, unsigned num, bit_t bitValue) {
  /* Tested */
  bit_t corrBit = 1 << (num % 32);
  if (bitValue) {
    *((*value).bits + (num / 32)) = *((*value).bits + (num / 32)) | corrBit;
  } else {
    unsigned invertedMask = UINTMAX - corrBit;
    *((*value).bits + (num / 32)) =
        *((*value).bits + (num / 32)) & invertedMask;
  }
}

unsigned getExp(big_decimal value) {
  /* Tested */
  return (value.bits[6] & EXPMASK) >> 16;
}

void setExp(big_decimal *value, unsigned exp) {
  /* Tested */
  exp = exp << 16;
  value->bits[6] = value->bits[6] & (UINTMAX - EXPMASK);
  value->bits[6] = value->bits[6] | exp;
}

bit_t getSign(big_decimal value) {
  /* Tested */
  return value.bits[6] >> 31;
}

void setSign(big_decimal *value, bit_t sign) {
  /* Tested */
  setBit(value, 32 * 7 - 1, sign);
}

void alignmentExp(big_decimal *value1, big_decimal *value2) {
  unsigned exp1 = getExp(*value1);
  unsigned exp2 = getExp(*value2);
  while (exp1 < exp2) {
    mulToBigDecimal(*value1, DECIMALTEN, value1);
    setExp(value1, getExp(*value1) + 1);
    exp1 = getExp(*value1);
  }
  while (exp2 < exp1) {
    mulToBigDecimal(*value2, DECIMALTEN, value2);
    // print_decimal(*value2);
    setExp(value2, getExp(*value2) + 1);
    exp2 = getExp(*value2);
  }
}

int shiftLeft(big_decimal *num, int shift) {
  /* Tested */
  int ec = 0;
  big_decimal converted = *num;
  /* ec = 0 OK
   * ec = 1 Overflow
   */
  while (shift != 0 && !ec) {
    if (getBit(converted, 32 * 6 - 1))
      ec = 1;
    else {
      for (int i = 5; i != -1; --i) {
        if (getBit(converted, (i + 1) * 32 - 1))
          setBit(&converted, (i + 1) * 32, 1);
        converted.bits[i] = converted.bits[i] << 1;
      }
      --shift;
    }
  }
  if (!ec) *num = converted;
  return ec;
}

int shiftRight(big_decimal *num, int shift) {
  /* Tested */
  int ec = 0;
  big_decimal converted = *num;
  /* ec = 0 OK
   * ec = 1 Overflow
   */
  while (shift != 0 && !ec) {
    for (int i = 0; i < 6; ++i) {
      converted.bits[i] = converted.bits[i] >> 1;
      if (getBit(converted, (i + 1) * 32))
        setBit(&converted, (i + 1) * 32 - 1, 1);
    }
    --shift;
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

#define insertOneAtBegin(buff, _charForInsert) \
  {                                            \
    char currChar = buff[0];                   \
    buff[0] = _charForInsert;                  \
    char nextChar;                             \
    int i_ = 1;                                \
    do {                                       \
      nextChar = buff[i_];                     \
      buff[i_] = currChar;                     \
      currChar = nextChar;                     \
      ++i_;                                    \
    } while (buff[i_] != '\0');                \
    buff[i_] = nextChar;                       \
    buff[i_ + 1] = '\0';                       \
  }

void print_decimal(big_decimal num) {
  char buffer[40] = {};
  for (int i = 6; i > -1; --i) {
    citoa(num.bits[i], buffer, 2);
    while (strlen(buffer) < 32) {
      insertOneAtBegin(buffer, '0');
    }
    printf("|%s", buffer);
  }
  putchar('|');
  putchar('\n');
}
