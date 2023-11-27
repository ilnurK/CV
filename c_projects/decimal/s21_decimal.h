#ifndef DECH
#define DECH

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define LOW 0
#define MID 1
#define HIGH 2
#define DEC 3
#define PLUS 0
#define MINUS 1
#define MAX_POW 28

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// OUR FUNCTIONS
// primary
// setters
void s21_setBit(s21_decimal *dst, unsigned int index);
void s21_setBitNum(unsigned int *dst, unsigned int index);
void s21_setSign(s21_decimal *num, int sign);
void s21_setDecPow(s21_decimal *num, unsigned int exponent);
void s21_setBinaryValue(s21_decimal *num, unsigned int sign,
                        unsigned int exponent, unsigned int low,
                        unsigned int mid, unsigned int high);

// getters
bool s21_getSign(s21_decimal num);
int s21_getDecPow(s21_decimal num);
int s21_getBinaryPow(float src);
int s21_getBit(s21_decimal src, unsigned int index);
int s21_getGreatestMantiss(s21_decimal num);
int s21_getHighIdx(s21_decimal num);
int s21_getLastDig(s21_decimal num);

// checkers
int s21_checkNonNull(s21_decimal value);
int s21_checkNonOne(s21_decimal num);
int s21_checkDecimal(s21_decimal src);
int s21_checkTenPower(s21_decimal num);

// copy dec without exp and sign
void s21_copyDec(s21_decimal from, s21_decimal *to);
// return remaind and reuce exp
unsigned int s21_decrement(s21_decimal *value);

// shifters
unsigned int s21_shiftLeft(s21_decimal num, int mant);
int s21_shiftAllLeft(s21_decimal *num);
unsigned int s21_shiftRight(s21_decimal num, int mant);
unsigned int s21_shiftAllRight(s21_decimal *num);

int s21_bringToCommDenom(s21_decimal *v1, s21_decimal *v2);
int s21_makeSamePow(s21_decimal *small_pow, s21_decimal *large_pow, int min_pow,
                    int max_pow);
int s21_mulTen(s21_decimal *num);
int s21_divTen(s21_decimal *num, s21_decimal *rem);
int s21_lastRound(s21_decimal v1, s21_decimal v2, s21_decimal *res, int func);
void s21_bankRound(s21_decimal *res, int remaind);

// secondary
// decimal to string
void s21_decToStr(s21_decimal value, char *str);
// bytes string to decimal
s21_decimal s21_strToDec(char *str);

// double from string
double s21_strBitsToNum(char *str);
int s21_abs(int num);

/*
Arithmetic Operators
The functions return the error code:
0 - OK
1 - the number is too large or equal to infinity
2 - the number is too small or equal to negative infinity
3 - division by 0
*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
unsigned int s21_addBit(s21_decimal v1, s21_decimal v2, unsigned int *in_mind,
                        int mant);
void s21_reduceAdd(s21_decimal *result, int *overflow, int *power);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
unsigned int s21_subBit(s21_decimal v1, s21_decimal v2, int *in_mind, int mant);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_mulRound(s21_decimal *res, s21_decimal temp_res);
int s21_reduceMantis(s21_decimal *v1, s21_decimal *v2, s21_decimal *rem_1,
                     s21_decimal *rem_2, int *rem_pow);
int s21_reduceOneMantiss(s21_decimal *num);
void s21_mulRemainds(s21_decimal v1, s21_decimal v2, s21_decimal rem_1,
                     s21_decimal rem_2, s21_decimal *res);
void s21_mulCycle(s21_decimal v1, s21_decimal v2, s21_decimal *res);
void s21_mulAdd(s21_decimal v1, s21_decimal *res, int i, int j);
void s21_reducePow(s21_decimal *res);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_divRem(s21_decimal v1, s21_decimal v2, s21_decimal *res,
               s21_decimal *rem);
int s21_adjusmentPow(s21_decimal *ten, s21_decimal cur_diff);
int s21_divFraction(s21_decimal *res, s21_decimal numer, s21_decimal denom);
void s21_divRemMul(s21_decimal *numer, s21_decimal *temp, s21_decimal rem,
                   s21_decimal denom_10);
void s21_divRound(s21_decimal *res, s21_decimal numer, s21_decimal denom);
void s21_increasePow(s21_decimal *res, int *power);

/*
  Comparison Operators
  Return value:
  0 - FALSE
  1 - TRUE
  */
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_less_num(s21_decimal num1, s21_decimal num2, int result);

int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_num(s21_decimal num1, s21_decimal num2, int result);

int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

/*
Convertors and parsers
Return value - code error:
0 - OK
1 - convertation error
*/
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
void s21_floatDecCycle(int binary_power, unsigned int fbits, s21_decimal *dst);

int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/*
Another functions
Return value - code error:
0 - OK
1 - calculation error
*/
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif