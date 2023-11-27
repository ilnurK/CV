#include "s21_decimal.h"

void s21_setBit(s21_decimal* dst, unsigned int index) {
  if (index <= 31) {
    dst->bits[0] |= (1 << index);
  } else if (index >= 32 && index <= 63) {
    dst->bits[1] |= (1 << (index - 32));
  } else if (index >= 64 && index <= 95) {
    dst->bits[2] |= (1 << (index - 64));
  } else if (index >= 96 && index <= 127) {
    dst->bits[3] |= (1 << (index - 96));
  }
}

void s21_setBitNum(unsigned int* dst, unsigned int index) {
  if (index <= 31) {
    *dst |= (1 << index);
  }
}

void s21_setSign(s21_decimal* num, int sign) {
  num->bits[3] <<= 1;
  num->bits[3] >>= 1;
  num->bits[3] |= sign << 31;
}

void s21_setDecPow(s21_decimal* num, unsigned int exponent) {
  num->bits[3] = 0;
  num->bits[3] |= (exponent << 16);
}

void s21_setBinaryValue(s21_decimal* num, unsigned int sign,
                        unsigned int exponent, unsigned int low,
                        unsigned int mid, unsigned int high) {
  num->bits[0] = low;
  num->bits[1] = mid;
  num->bits[2] = high;
  num->bits[3] = 0;
  num->bits[3] |= (exponent << 16);
  num->bits[3] |= (sign << 31);
}

int s21_getBit(s21_decimal src, unsigned int index) {
  int bit = 0;
  if (index <= 31) {
    bit = (src.bits[0] & (1 << index)) >> index;
  } else if (index >= 32 && index <= 63) {
    bit = (src.bits[1] & (1 << (index - 32))) >> (index - 32);
  } else if (index >= 64 && index <= 95) {
    bit = (src.bits[2] & (1 << (index - 64))) >> (index - 64);
  } else if (index >= 96 && index <= 127)
    bit = (src.bits[3] & (1 << (index - 96))) >> (index - 96);
  return bit;
}

bool s21_getSign(s21_decimal num) { return (num.bits[3] >> 31) & 0x01; }

int s21_getDecPow(s21_decimal num) {
  int desired_bit = num.bits[3] >> 16, power = 0;
  for (int i = 0; i <= 7; i++) {
    int mask = 1 << i;
    power += (desired_bit & mask);
  }
  return power;
}

int s21_getBinaryPow(float src) {
  unsigned int* ptr = (unsigned int*)&src;
  return ((*ptr & 0x7f800000) >> 23) - 127;
}

int s21_getGreatestMantiss(s21_decimal num) {
  int mant = 0;
  if (num.bits[HIGH] > 0) {
    mant = HIGH;
  } else if (num.bits[MID] > 0) {
    mant = MID;
  } else {
    mant = LOW;
  }
  return mant;
}

int s21_getHighIdx(s21_decimal num) {
  int mant = s21_getGreatestMantiss(num);
  int power = (mant > 1) ? 63 : (mant > 0) ? 31 : -1;
  while (num.bits[mant]) {
    num.bits[mant] /= 2;
    power++;
  }
  return power;
}

int s21_checkDecimal(s21_decimal src) {
  int mask0_15 = 0b1111111111111111, mask24_30 = 0b1111111 << 24;
  return (((src.bits[3] & mask0_15) == 0) &&
          ((src.bits[3] & mask24_30) >> 24 == 0) && s21_getDecPow(src) <= 28)
             ? 0   // dec correct
             : 1;  // error
}

int s21_checkNonNull(s21_decimal value) {
  return (value.bits[LOW] > 0) + (value.bits[MID] > 0) + (value.bits[HIGH] > 0);
}

int s21_checkNonOne(s21_decimal num) {
  int exp = s21_getDecPow(num);
  return !(num.bits[LOW] == 1 && (num.bits[MID] + num.bits[HIGH] == 0) && !exp);
}

int s21_checkTenPower(s21_decimal num) {
  return num.bits[LOW] == 1 && (num.bits[MID] + num.bits[HIGH] == 0);
}

void s21_copyDec(s21_decimal from, s21_decimal* to) {
  for (int i = 0; i < 3; i++) to->bits[i] = from.bits[i];
}

unsigned int s21_decrement(s21_decimal* value) {
  unsigned int rem = 0;
  unsigned long temp = 0;

  for (int i = 2; i >= 0; i--) {
    temp = (1UL << 32) * rem + value->bits[i];
    value->bits[i] = (temp / 10);
    rem = temp % 10;
  }
  return rem;
}

unsigned int s21_shiftLeft(s21_decimal num, int mant) {
  unsigned int res = num.bits[mant];
  res <<= 1;
  if (mant > 0) {
    res += s21_getBit(num, mant * 32 - 1);
  }
  return res;
}

int s21_shiftAllLeft(s21_decimal* num) {
  unsigned int temp_high = num->bits[HIGH];
  num->bits[HIGH] = s21_shiftLeft(*num, HIGH);
  num->bits[MID] = s21_shiftLeft(*num, MID);
  num->bits[LOW] = s21_shiftLeft(*num, LOW);
  return (num->bits[HIGH] < temp_high);
}

unsigned int s21_shiftRight(s21_decimal num, int mant) {
  unsigned int res = num.bits[mant];
  res >>= 1;
  if (mant < 2) {
    res |= (s21_getBit(num, (mant + 1) * 32)) << 31;
  }
  return res;
}

unsigned int s21_shiftAllRight(s21_decimal* num) {
  unsigned int remain = num->bits[HIGH] & 0b1;
  num->bits[LOW] = s21_shiftRight(*num, LOW);
  num->bits[MID] = s21_shiftRight(*num, MID);
  num->bits[HIGH] = s21_shiftRight(*num, HIGH);
  return remain;
}

int s21_bringToCommDenom(s21_decimal* v1, s21_decimal* v2) {
  int pow_1 = s21_getDecPow(*v1), pow_2 = s21_getDecPow(*v2);
  int overflow = 0;
  if (pow_1 < pow_2) {
    overflow = s21_makeSamePow(v1, v2, pow_1, pow_2);
  } else if (pow_2 < pow_1) {
    overflow = s21_makeSamePow(v2, v1, pow_2, pow_1);
  }
  return overflow;
}

int s21_makeSamePow(s21_decimal* low_pow_dec, s21_decimal* high_pow_dec,
                    int min_pow, int max_pow) {
  int overflow = 0;
  s21_decimal temp = *low_pow_dec;
  while (min_pow != max_pow && !overflow) {
    overflow = s21_mulTen(&temp);
    *low_pow_dec = (!overflow) ? temp : *low_pow_dec;
    (!overflow) ? min_pow++ : 0;
  }
  s21_setDecPow(low_pow_dec, min_pow);
  int close_null = 0;
  if (min_pow != max_pow) {
    s21_decimal ten = {{10, 0, 0, 0}}, rem = {0};
    while (min_pow != max_pow && !close_null) {
      s21_setDecPow(&ten, max_pow);
      close_null = s21_divRem(*high_pow_dec, ten, &temp, &rem);
      *high_pow_dec = (!close_null) ? temp : *high_pow_dec;
      max_pow -= (!close_null) ? 1 : 0;
    }
  }
  s21_setDecPow(high_pow_dec, max_pow);
  overflow = (min_pow != max_pow) ? 1 : 0;
  return overflow;
}

int s21_mulTen(s21_decimal* num) {
  int overflow = 0;
  s21_decimal shifted_three = *num, shifted_one = *num;
  overflow += s21_shiftAllLeft(&shifted_three);
  shifted_one = shifted_three;
  for (int i = 0; i < 2 && !overflow; i++) {
    overflow += s21_shiftAllLeft(&shifted_three);
  }
  int power_before = s21_getDecPow(*num);
  overflow += s21_add(shifted_three, shifted_one, num);
  int power_after = s21_getDecPow(*num);
  overflow += (power_after != power_before) ? 1 : 0;
  return overflow;
}

int s21_divTen(s21_decimal* num, s21_decimal* rem) {
  s21_decimal ten = {{10, 0, 0, 0}}, res = {0};
  s21_setDecPow(&ten, s21_getDecPow(*num));
  int close_null = s21_divRem(*num, ten, &res, rem);
  *num = (!close_null) ? res : *num;
  return close_null;
}

int s21_lastRound(s21_decimal v1, s21_decimal v2, s21_decimal* res, int func) {
  int v1_pow = s21_getDecPow(v1), v2_pow = s21_getDecPow(v2), total = 0;
  if (s21_abs(v1_pow - v2_pow) <= 1) {
    s21_decimal one = {0};
    one.bits[LOW] = 1;
    int v1_g = v1_pow > v2_pow, v2_g = v1_pow < v2_pow;
    int min_pow = v1_g ? v2_pow : v1_pow;
    s21_setDecPow(&one, min_pow);
    if (func == PLUS) {
      if (v2_g && v2.bits[LOW] >= 5) {
        total = s21_add(v1, one, &v1);
      } else if (v1_g && v2.bits[LOW] >= 5) {
        total = s21_add(v2, one, &v2);
      }
    } else {
      if (v2_g && v2.bits[LOW] >= 5) {
        total = s21_sub(v1, one, &v1);
      } else if (v1_g && v2.bits[LOW] >= 5) {
        total = s21_sub(v2, one, &v2);
        s21_setSign(&v2, MINUS);
      }
    }
  }
  *res = (v1_pow < v2_pow) ? v1 : v2;
  *res = (v1_pow < v2_pow) ? v1 : v2;
  return total;
}

void s21_bankRound(s21_decimal* res, int remaind) {
  if (remaind >= 5) {
    int last_dig = s21_getLastDig(*res);
    if (!(remaind == 5 && last_dig % 2 == 0)) {
      s21_decimal one = {{1, 0, 0, 0}};
      s21_setDecPow(&one, s21_getDecPow(*res));
      s21_add(*res, one, res);
    }
  }
}

void s21_decToStr(s21_decimal num, char* str) {
  int len = 95;
  int idx = len;
  for (int i = LOW; i <= HIGH; i++) {
    for (int j = 0; j < 32; j++) {
      unsigned int mask = 1 << j;
      char c = (mask & num.bits[i]) ? '1' : '0';
      str[idx--] = c;
    }
  }
  int k = 0, new_idx = 0, flag_1_appear = 0;
  for (; k < len + 1; k++) {
    char c = str[k];
    flag_1_appear = (!flag_1_appear && c == '0') ? 0 : 1;
    (flag_1_appear) ? str[new_idx++] = c : 0;
  }
  str[new_idx] = '\0';
}

s21_decimal s21_strToDec(char* str) {
  s21_decimal num = {0};
  int len = (int)strlen(str);
  int counter = 0, bit = 0;
  for (int t = len - 1; t >= 0; t--) {
    if (str[t] - '0') {
      unsigned int mask = 1 << (counter - bit * 32);
      num.bits[bit] |= mask;
    }
    counter++;
    bit += (counter % 32 == 0) ? 1 : 0;
  }
  return num;
}

double s21_strBitsToNum(char* str) {
  double num = 0, j = 0;
  for (int i = (int)strlen(str) - 1; i >= 0; i--, j++) {
    num += (str[i] - '0') * pow(2, j);
  }
  return num;
}

int s21_abs(int num) { return (num < 0) ? -num : num; }

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int total = 0, overflow = 0;
  int sign_1 = s21_getSign(value_1), sign_2 = s21_getSign(value_2);
  if (!s21_checkNonNull(value_1)) {
    *result = value_2;
  } else if (!s21_checkNonNull(value_2)) {
    *result = value_1;
  } else if (!sign_1 && sign_2) {
    s21_setSign(&value_1, PLUS), s21_setSign(&value_2, PLUS);
    overflow = s21_sub(value_1, value_2, result);
  } else if (sign_1 && !sign_2) {
    s21_setSign(&value_1, PLUS), s21_setSign(&value_2, PLUS);
    overflow = s21_sub(value_2, value_1, result);
  } else if (sign_1 && sign_2) {
    s21_setSign(&value_1, PLUS), s21_setSign(&value_2, PLUS);
    overflow = s21_add(value_1, value_2, result);
    s21_setSign(result, MINUS);
  } else {
    overflow = s21_bringToCommDenom(&value_1, &value_2);
    if (!overflow) {
      unsigned int in_mind = 0;
      result->bits[LOW] = s21_addBit(value_1, value_2, &in_mind, LOW);
      result->bits[MID] = s21_addBit(value_1, value_2, &in_mind, MID);
      result->bits[HIGH] = s21_addBit(value_1, value_2, &in_mind, HIGH);
      int power = s21_getDecPow(value_1);
      overflow = (in_mind) ? 1 : 0;
      (overflow && power) ? s21_reduceAdd(result, &overflow, &power) : 0;
      s21_setDecPow(result, power);
    } else {
      overflow = s21_lastRound(value_1, value_2, result, PLUS);
    }
  }
  total = overflow + (overflow && s21_getSign(*result));
  (total) ? s21_setBinaryValue(result, 0, 0, 0, 0, 0) : 0;
  return total;
}

void s21_reduceAdd(s21_decimal* result, int* overflow, int* power) {
  s21_shiftAllRight(result);
  s21_setBit(result, 95);
  s21_decimal ten = {{10, 0, 0, 0}}, rem = {0};
  s21_divRem(*result, ten, result, &rem);
  s21_shiftAllLeft(result);
  int remaind = (rem.bits[LOW] * 2) % 10;
  s21_bankRound(result, remaind);
  *power -= 1;
  *overflow = 0;
}

unsigned int s21_addBit(s21_decimal v1, s21_decimal v2, unsigned int* in_mind,
                        int mant) {
  unsigned int result = 0;
  for (int i = 0; i < 32; i++) {
    unsigned int mask = 1 << i;
    int cond_1 = (v1.bits[mant] & mask) > 0;
    int cond_2 = (v2.bits[mant] & mask) > 0;
    int sum = cond_1 + cond_2 + *in_mind;
    if (sum == 3) {
      sum = 1;
      *in_mind = 1;
    } else if (sum == 2) {
      sum = 0;
      *in_mind = 1;
    } else if (*in_mind) {
      *in_mind -= 1;
    }
    (sum) ? s21_setBitNum(&result, i) : 0;
  }
  return result;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int total = 0, overflow = 0;
  int sign_1 = s21_getSign(value_1), sign_2 = s21_getSign(value_2);
  if (s21_is_equal(value_1, value_2)) {
    s21_setBinaryValue(result, 0, 0, 0, 0, 0);
  } else if (!s21_checkNonNull(value_1)) {
    *result = value_2;
    (sign_2) ? s21_setSign(result, PLUS) : s21_setSign(result, MINUS);
  } else if (!s21_checkNonNull(value_2)) {
    *result = value_1;
  } else if (!sign_1 && sign_2) {
    s21_setSign(&value_2, PLUS);
    overflow = s21_add(value_1, value_2, result);
  } else if (sign_1 && sign_2) {
    s21_setSign(&value_1, PLUS), s21_setSign(&value_2, PLUS);
    overflow = s21_sub(value_2, value_1, result);
  } else if (sign_1 && !sign_2) {
    s21_setSign(&value_2, MINUS);
    overflow = s21_add(value_1, value_2, result);
  } else {
    overflow = s21_bringToCommDenom(&value_1, &value_2);
    if (s21_is_greater(value_2, value_1) && !overflow) {
      total = s21_sub(value_2, value_1, result);
      s21_setSign(result, MINUS);
    } else if (!overflow) {
      int in_mind = 0;
      result->bits[LOW] = s21_subBit(value_1, value_2, &in_mind, LOW);
      result->bits[MID] = s21_subBit(value_1, value_2, &in_mind, MID);
      result->bits[HIGH] = s21_subBit(value_1, value_2, &in_mind, HIGH);
      s21_setDecPow(result, s21_getDecPow(value_1));
    } else {
      overflow = s21_lastRound(value_1, value_2, result, MINUS);
    }
  }
  total = overflow + (overflow && s21_getSign(*result));
  return total;
}

unsigned int s21_subBit(s21_decimal v1, s21_decimal v2, int* in_mind,
                        int mant) {
  unsigned int result = 0;
  for (int i = 0; i < 32; i++) {
    unsigned int mask = 1 << i;
    int cond_1 = (v1.bits[mant] & mask) > 0;
    int cond_2 = (v2.bits[mant] & mask) > 0;
    int sub = cond_1 - cond_2 - *in_mind;
    if (sub >= 0) {
      *in_mind = 0;
    } else if (sub == -1) {
      sub = 1;
      *in_mind = 1;
    } else if (sub == -2) {
      sub = 0;
      *in_mind = 1;
    }
    (sub) ? s21_setBitNum(&result, i) : 0;
  }
  return result;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int total = 0, overflow = 0;
  int sign = s21_getSign(value_1) + s21_getSign(value_2);
  int v1_pow = s21_getDecPow(value_1), v2_pow = s21_getDecPow(value_2);
  s21_setSign(&value_1, PLUS), s21_setSign(&value_2, PLUS);
  if (!s21_checkNonNull(value_1) || !s21_checkNonNull(value_2)) {
    s21_setBinaryValue(result, 0, 0, 0, 0, 0);
  } else if (!s21_checkNonOne(value_2)) {
    *result = value_1;
  } else if (s21_checkTenPower(value_2) || s21_checkTenPower(value_1)) {
    int cond = s21_checkTenPower(value_2);
    *result = (cond) ? value_1 : value_2;
    s21_setDecPow(result, v1_pow + v2_pow);
  } else {
    s21_decimal rem_1 = {0}, rem_2 = {0};
    int pow_rem = 0;
    if (!overflow && (s21_getHighIdx(value_1) + s21_getHighIdx(value_2) > 94)) {
      overflow = s21_reduceMantis(&value_1, &value_2, &rem_1, &rem_2, &pow_rem);
    }
    if (!overflow) {
      s21_mulRemainds(value_1, value_2, rem_1, rem_2, result);
      s21_setDecPow(result, s21_getDecPow(*result) + pow_rem);
    }
  }
  s21_reducePow(result);
  (sign == 1) ? s21_setSign(result, MINUS) : 0;
  total = overflow + (overflow && s21_getSign(*result));
  (total) ? s21_setBinaryValue(result, 0, 0, 0, 0, 0) : 0;
  return total;
}

int s21_reduceMantis(s21_decimal* v1, s21_decimal* v2, s21_decimal* rem_1,
                     s21_decimal* rem_2, int* pow_rem) {
  int error = 0, close_null_1 = 0, close_null_2 = 0;
  int v1_pow = s21_getDecPow(*v1), v2_pow = s21_getDecPow(*v2);
  int power = v1_pow + v2_pow, v1_pow_new = 0, v2_pow_new = 0;
  s21_setDecPow(v1, 0), s21_setDecPow(v2, 0);
  s21_decimal v1_init = *v1, v2_init = *v2;
  while (s21_getHighIdx(*v1) + s21_getHighIdx(*v2) > 94 && power && !error) {
    if (s21_getHighIdx(*v1) >= s21_getHighIdx(*v2) && !close_null_1) {
      close_null_1 = s21_reduceOneMantiss(v1);
      power -= (!close_null_1) ? 1 : 0;
      v1_pow_new += (!close_null_1) ? 1 : 0;
    } else if (!close_null_2) {
      close_null_2 = s21_reduceOneMantiss(v2);
      power -= (!close_null_2) ? 1 : 0;
      v2_pow_new += (!close_null_2) ? 1 : 0;
    }
    error = close_null_1 && close_null_2 && power;
  }
  error = (s21_getHighIdx(*v1) + s21_getHighIdx(*v2) > 94) ? 1 : error;
  if (!error) {
    s21_decimal ten_1 = {{1, 0, 0, 0}}, ten_2 = {{1, 0, 0, 0}}, temp = {0};
    for (int i = 0; i < v1_pow_new || i < v2_pow_new; i++) {
      (i < v1_pow_new) ? s21_mulTen(&ten_1) : 0;
      (i < v2_pow_new) ? s21_mulTen(&ten_2) : 0;
    }
    s21_divRem(v1_init, ten_1, &temp, rem_1);
    s21_divRem(v2_init, ten_2, &temp, rem_2);
    s21_setDecPow(rem_1, v1_pow_new), s21_setDecPow(rem_2, v2_pow_new);
    *pow_rem = power;
  }
  return error;
}

int s21_reduceOneMantiss(s21_decimal* num) {
  s21_decimal temp = *num, ten = {{10, 0, 0, 0}}, rem = {0};
  int close_null = s21_divRem(*num, ten, &temp, &rem);
  *num = (!close_null) ? temp : *num;
  return close_null;
}

void s21_mulRemainds(s21_decimal v1, s21_decimal v2, s21_decimal rem_1,
                     s21_decimal rem_2, s21_decimal* res) {
  s21_decimal v1_v2 = {0}, v1_rem_2 = {0}, v2_rem_1 = {0};
  s21_decimal rem_1_rem_2 = {0};
  s21_mulCycle(v1, v2, &v1_v2);
  s21_mulCycle(v1, rem_2, &v1_rem_2);
  s21_mulCycle(v2, rem_1, &v2_rem_1);
  s21_mulCycle(rem_1, rem_2, &rem_1_rem_2);

  s21_add(v1_rem_2, v2_rem_1, res);
  s21_add(*res, rem_1_rem_2, res);

  s21_decimal temp_res = *res;
  s21_add(*res, v1_v2, res);
  s21_mulRound(res, temp_res);
}

void s21_mulRound(s21_decimal* res, s21_decimal temp_res) {
  int power_before = s21_getDecPow(temp_res);
  int power_after = s21_getDecPow(*res);
  if (power_after != power_before) {
    s21_decimal rem = {0};
    while (power_after < power_before) {
      s21_divTen(&temp_res, &rem);
      power_after++;
    }
    int remaind = rem.bits[LOW];
    s21_bankRound(res, remaind);
  }
}

int s21_getLastDig(s21_decimal num) {
  s21_decimal rem = {0};
  s21_divTen(&num, &rem);
  return rem.bits[LOW];
}

void s21_mulCycle(s21_decimal v1, s21_decimal v2, s21_decimal* res) {
  s21_setBinaryValue(res, 0, 0, 0, 0, 0);
  for (int i = LOW; i <= HIGH; i++) {
    for (int j = 0; j < 32; j++) {
      unsigned int mask = 1 << j;
      (mask & v2.bits[i]) ? s21_mulAdd(v1, res, i, j) : 0;
    }
  }
  int v1_pow = s21_getDecPow(v1), v2_pow = s21_getDecPow(v2);
  s21_setDecPow(res, v1_pow + v2_pow);
}

void s21_mulAdd(s21_decimal v1, s21_decimal* res, int i, int j) {
  s21_decimal shifted_v1 = v1;
  s21_setDecPow(&shifted_v1, 0);
  for (int k = 0; k < j + 32 * i; k++) {
    s21_shiftAllLeft(&shifted_v1);
  }
  s21_add(*res, shifted_v1, res);
}

void s21_reducePow(s21_decimal* res) {
  int close_null = 0, power = s21_getDecPow(*res);
  s21_decimal ten = {{10, 0, 0, 0}}, rem = {0};
  while (power > 28 && !close_null) {
    close_null = s21_divRem(*res, ten, res, &rem);
    power -= 1;
  }
  s21_setDecPow(res, power);
  int remaind = rem.bits[LOW];
  (power <= 28) ? s21_bankRound(res, remaind) : 0;
  power = (power <= 28) ? power : 28;
  s21_setDecPow(res, power);
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  s21_setBinaryValue(result, 0, 0, 0, 0, 0);
  int sign = s21_getSign(value_1) + s21_getSign(value_2);
  s21_setSign(&value_1, PLUS), s21_setSign(&value_2, PLUS);
  int total = 0, overflow = 0;
  if (!s21_checkNonNull(value_2)) {
    total = 3;
  } else if (!s21_checkNonNull(value_1)) {
    s21_setBinaryValue(result, 0, 0, 0, 0, 0);
  } else if (s21_is_equal(value_1, value_2)) {
    s21_setBinaryValue(result, 0, 0, 1, 0, 0);
  } else if (!s21_checkNonOne(value_2)) {
    *result = value_1;
  } else if (s21_checkNonNull(value_2) && s21_checkNonOne(value_2)) {
    int close_null = s21_divFraction(result, value_1, value_2);
    overflow = (!s21_checkNonNull(*result) && !close_null) ? 1 : 0;
  }
  if (sign == 1) {
    s21_setSign(result, MINUS);
  }
  total = (total != 3) ? overflow + (overflow && s21_getSign(*result)) : total;
  (total) ? s21_setBinaryValue(result, 0, 0, 0, 0, 0) : 0;
  return total;
}

int s21_divRem(s21_decimal v1, s21_decimal v2, s21_decimal* res,
               s21_decimal* rem) {
  s21_setBinaryValue(res, 0, 0, 0, 0, 0);
  int close_null = 1, zero = s21_checkNonNull(v2) ? 0 : 3;
  if (!s21_checkNonOne(v2)) {
    *rem = *res;
    *res = v1;
  } else if (!zero) {
    int v2_max_bit = s21_getHighIdx(v2);
    int v1_pow = s21_getDecPow(v1), v2_pow = s21_getDecPow(v2);
    s21_decimal cur_diff = {0}, temp_v2 = {0};
    cur_diff = v1, s21_setDecPow(&cur_diff, v2_pow);
    while (s21_is_greater_or_equal(cur_diff, v2)) {
      temp_v2 = v2;
      int shift = v2_max_bit;
      int desired_shift = s21_getHighIdx(cur_diff) - 1;
      while (shift <= desired_shift) {
        s21_shiftAllLeft(&temp_v2);
        shift++;
      }
      shift -= s21_adjusmentPow(&temp_v2, cur_diff);
      s21_setBit(res, shift - v2_max_bit);
      if (s21_is_greater_or_equal(cur_diff, temp_v2)) {
        s21_sub(cur_diff, temp_v2, &cur_diff);
      }
      close_null = 0;
    }
    *rem = cur_diff;
    (s21_checkNonNull(*res)) ? s21_setDecPow(res, v1_pow - v2_pow) : 0;
    (s21_checkNonNull(*rem)) ? s21_setDecPow(rem, v1_pow) : 0;
  }
  int total = (zero) ? zero : (close_null) ? close_null : 0;
  return total;
}

int s21_adjusmentPow(s21_decimal* v2, s21_decimal cur_diff) {
  int mant = s21_getGreatestMantiss(cur_diff);
  int flag = 0;
  if (v2->bits[mant] > cur_diff.bits[mant]) {
    flag = 1;
  } else if (mant > 0 && v2->bits[mant] == cur_diff.bits[mant]) {
    if (v2->bits[mant - 1] > cur_diff.bits[mant - 1]) {
      flag = 1;
    } else if (mant > 1 && v2->bits[mant - 1] == cur_diff.bits[mant - 1]) {
      if (v2->bits[mant - 2] > cur_diff.bits[mant - 2]) {
        flag = 1;
      }
    }
  }
  (flag) ? s21_shiftAllRight(v2) : 0;
  return flag;
}

int s21_divFraction(s21_decimal* res, s21_decimal numer, s21_decimal denom) {
  int n_pow = s21_getDecPow(numer), d_pow = s21_getDecPow(denom);
  int power = n_pow - d_pow, too_large = 0, com_pow = 0;
  s21_setDecPow(&numer, com_pow), s21_setDecPow(&denom, com_pow);
  s21_decimal null = {0}, ten = {{10, 0, 0, 0}}, rem = {0}, denom_10 = denom;
  s21_divRem(denom, ten, &denom_10, &rem);
  while (s21_is_greater_or_equal(denom_10, numer) && power < 28 && !too_large) {
    s21_decimal temp = *res;
    too_large = s21_mulTen(&temp);
    *res = s21_is_greater(temp, *res) ? temp : *res;
    if (!too_large) {
      s21_mulTen(&numer);
      power++;
    }
  }
  while (!s21_is_equal(numer, null) && power < 28 && !too_large) {
    s21_decimal temp = *res;
    too_large = s21_mulTen(&temp);
    *res = (!too_large) ? temp : *res;
    if (!too_large) {
      temp = numer;
      if (s21_mulTen(&temp)) {
        s21_divRemMul(&numer, &temp, rem, denom_10);
      } else {
        numer = temp;
        s21_divRem(numer, denom, &temp, &numer);
      }
      s21_add(*res, temp, res);
      power++;
    }
  }
  s21_divRound(res, numer, denom);
  (power < 0) ? s21_increasePow(res, &power) : 0;
  (s21_checkNonNull(*res)) ? s21_setDecPow(res, power) : 0;
  return power == 28;
}

void s21_increasePow(s21_decimal* res, int* power) {
  int overflow = 0;
  while (*power < 0 && !overflow) {
    overflow = s21_mulTen(res);
    (overflow) ? s21_setBinaryValue(res, 0, 0, 0, 0, 0) : 0;
    *power += 1;
  }
}

void s21_divRemMul(s21_decimal* numer, s21_decimal* temp, s21_decimal rem,
                   s21_decimal denom_10) {
  s21_divRem(*numer, denom_10, temp, numer);
  s21_mulTen(numer);
  s21_mul(rem, *temp, &rem);
  s21_sub(*numer, rem, numer);
}

void s21_divRound(s21_decimal* res, s21_decimal numer, s21_decimal denom) {
  s21_decimal temp = {0};
  s21_mulTen(&numer);
  s21_divRem(numer, denom, &temp, &numer);
  int last_digit = temp.bits[LOW];
  if (last_digit >= 5) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_add(*res, one, res);
  }
}

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  int result = -1;
  int sign_num1 = s21_getSign(num1);
  int sign_num2 = s21_getSign(num2);

  bool is_positive_num1 = (sign_num1 == 0);
  bool is_negative_num1 = (sign_num1 == 1);
  bool is_positive_num2 = (sign_num2 == 0);
  bool is_negative_num2 = (sign_num2 == 1);
  bool are_bits_equal = true;

  if (is_positive_num1 && is_positive_num2) {
    result = s21_is_greater_num(num1, num2, result);
  } else if (is_negative_num1 && is_positive_num2) {
    result = 0;
  } else if (is_positive_num1 && is_negative_num2) {
    result = 1;
  } else if (is_negative_num1 && is_negative_num2) {
    for (int i = 0; i < 4 && are_bits_equal; i++) {
      if (num1.bits[i] != num2.bits[i]) {
        are_bits_equal = false;
      }
    }
    if (are_bits_equal) {
      result = 0;
    } else {
      result = !s21_is_greater_num(num1, num2, result);
    }
  }
  return result;
}

int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  return (s21_is_greater(num1, num2) || s21_is_equal(num1, num2));
}

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  int result = -1;
  int sign_num1 = s21_getSign(num1);
  int sign_num2 = s21_getSign(num2);

  bool is_positive_num1 = (sign_num1 == 0);
  bool is_negative_num1 = (sign_num1 == 1);
  bool is_positive_num2 = (sign_num2 == 0);
  bool is_negative_num2 = (sign_num2 == 1);
  bool are_bits_equal = true;

  if (is_positive_num1 && is_positive_num2) {
    result = s21_is_less_num(num1, num2, result);
  } else if (is_negative_num1 && is_positive_num2) {
    result = 1;
  } else if (is_positive_num1 && is_negative_num2) {
    result = 0;
  } else if (is_negative_num1 && is_negative_num2) {
    for (int i = 0; i < 4 && are_bits_equal; i++) {
      if (num1.bits[i] != num2.bits[i]) {
        are_bits_equal = false;
      }
    }
    if (are_bits_equal) {
      result = 0;
    } else {
      result = !s21_is_less_num(num1, num2, result);
    }
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  return (s21_is_less(num1, num2) || s21_is_equal(num1, num2));
}

int s21_is_less_num(s21_decimal num1, s21_decimal num2, int result) {
  s21_decimal tmp_num1 = num1;
  s21_decimal tmp_num2 = num2;
  s21_bringToCommDenom(&tmp_num1, &tmp_num2);
  if (tmp_num1.bits[HIGH] == tmp_num2.bits[HIGH]) {
    if (tmp_num1.bits[MID] == tmp_num2.bits[MID]) {
      if (tmp_num1.bits[LOW] == tmp_num2.bits[LOW]) {
        result = 0;
      } else if (tmp_num1.bits[LOW] < tmp_num2.bits[LOW]) {
        result = 1;
      } else {
        result = 0;
      }
    } else if (tmp_num1.bits[MID] < tmp_num2.bits[MID]) {
      result = 1;
    } else {
      result = 0;
    }
  } else if (tmp_num1.bits[HIGH] < tmp_num2.bits[HIGH]) {
    result = 1;
  } else {
    result = 0;
  }
  return result;
}

int s21_is_greater_num(s21_decimal num1, s21_decimal num2, int result) {
  s21_decimal tmp_num1 = num1;
  s21_decimal tmp_num2 = num2;
  s21_bringToCommDenom(&tmp_num1, &tmp_num2);
  if (tmp_num1.bits[HIGH] == tmp_num2.bits[HIGH]) {
    if (tmp_num1.bits[MID] == tmp_num2.bits[MID]) {
      if (tmp_num1.bits[LOW] == tmp_num2.bits[LOW]) {
        result = 0;
      } else if (tmp_num1.bits[LOW] > tmp_num2.bits[LOW]) {
        result = 1;
      } else {
        result = 0;
      }
    } else if (tmp_num1.bits[MID] > tmp_num2.bits[MID]) {
      result = 1;
    } else {
      result = 0;
    }
  } else if (tmp_num1.bits[HIGH] > tmp_num2.bits[HIGH]) {
    result = 1;
  } else {
    result = 0;
  }
  return result;
}

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int sign_num1 = s21_getSign(num1);
  int sign_num2 = s21_getSign(num2);
  int result = -1;

  bool is_sign_equal = (sign_num1 == sign_num2);
  bool is_degree_equal = (num1.bits[DEC] == num2.bits[DEC]);
  bool is_degree_equal_after_conversion = false;

  if (is_sign_equal) {
    if (is_degree_equal) {
      if (num1.bits[HIGH] == num2.bits[HIGH] &&
          num1.bits[MID] == num2.bits[MID] &&
          num1.bits[LOW] == num2.bits[LOW]) {
        result = 1;
      } else {
        result = 0;
      }
    } else {
      s21_decimal tmp_num1 = num1;
      s21_decimal tmp_num2 = num2;
      s21_bringToCommDenom(&tmp_num1, &tmp_num2);
      is_degree_equal_after_conversion =
          (tmp_num1.bits[HIGH] == tmp_num2.bits[HIGH] &&
           tmp_num1.bits[MID] == tmp_num2.bits[MID] &&
           tmp_num1.bits[LOW] == tmp_num2.bits[LOW]);
      result = is_degree_equal_after_conversion ? 1 : 0;
    }
  } else {
    result = 0;
  }

  return result;
}

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  return !s21_is_equal(num1, num2);
}

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
  int error = 0;
  if (dst) {
    s21_setBinaryValue(dst, 0, 0, 0, 0, 0);
    if (src < 0) {
      src += 1;
      src *= -1;
      dst->bits[3] = 1 << 31;
      dst->bits[0] = src;
      dst->bits[0] += 1;
    } else
      dst->bits[0] = src;
  } else
    error = 1;
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal* dst) {
  int error = 0;
  if (dst && !isnan(src)) {
    int power = 0, binary_power = 0, sign = 0;
    double res = src;
    s21_setBinaryValue(dst, 0, 0, 0, 0, 0);
    unsigned int* ptr = (unsigned int*)&src;
    sign = *ptr >> 31;
    binary_power = s21_getBinaryPow(src);
    (sign) ? res *= -1 : 0;
    if (binary_power <= 95 && binary_power >= -94) {
      for (; !((int)res); res *= 10, power++) {
        ;
      }
      for (; (int)res != res && res <= 1000000; res *= 10, power++) {
        ;
      }
      for (; res > 9999999; res /= 10, power--) {
        ;
      }
      src = round(res);
      if (power) {
        for (; (int)(src / 10) * 10 == (int)src; src /= 10, power--) {
          ;
        }
      }
      if (power <= 28) {
        binary_power = s21_getBinaryPow(src);
        (sign) ? s21_setBit(dst, 127) : 0;
        power > 0 ? dst->bits[3] |= (power << 16) : 0;
        s21_setBit(dst, binary_power--);
        unsigned int fbits = *((unsigned int*)&src);
        s21_floatDecCycle(binary_power, fbits, dst);
      } else
        error = 1;
    } else
      error = 1;
  } else
    error = 1;
  return error;
}

void s21_floatDecCycle(int binary_power, unsigned int fbits, s21_decimal* dst) {
  for (int mask = 0x400000; mask > 0 && binary_power >= 0;
       mask >>= 1, binary_power--) {
    (!!(fbits & mask)) ? s21_setBit(dst, binary_power) : 0;
  }
}

int s21_from_decimal_to_int(s21_decimal src, int* dst) {
  int error = 0;
  if (dst && !s21_checkDecimal(src)) {
    int power = s21_getDecPow(src);
    char str[100] = {0};
    s21_decToStr(src, str);
    double mantissa = s21_strBitsToNum(str);
    for (int i = 0; i < power; i++) {
      mantissa /= 10;
    }
    if (s21_getSign(src) && mantissa == 2147483648) {
      *dst = -2147483648;
    } else if (mantissa <= INT_MAX) {
      *dst = mantissa;
      if (s21_getSign(src)) *dst *= -1;
    } else
      error = 1;
  } else
    error = 1;
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
  int error = 0;
  if (dst && !s21_checkDecimal(src)) {
    *dst = 0;
    int power = s21_getDecPow(src);
    for (int i = 0; i < 96; i++) {
      if (s21_getBit(src, i)) {
        *dst += powf(2, i);
      }
    }
    long long int divider = 1;
    while (power != 0) {
      divider *= 10;
      power--;
    }
    *dst /= divider;
    if (s21_getSign(src)) *dst = -*dst;
  } else {
    error = 1;
    if (s21_getDecPow(src) > 28) *dst = 0;
  }
  return error;
}

int s21_floor(s21_decimal value, s21_decimal* result) {
  s21_setBinaryValue(result, 0, 0, 0, 0, 0);
  int sign = 0;
  int exp = 0;
  unsigned minima = -2147483648;

  int check = s21_truncate(value, result);

  if (value.bits[3]) {
    sign = s21_getSign(value);
    exp = s21_getDecPow(*result);
  }

  if (exp > 28 || exp < 0) check = 1;

  result->bits[3] |= (sign << 31);
  if ((sign && value.bits[3] != minima) && (!check)) {
    s21_decimal one = {.bits = {1, 0, 0, 0}};
    one.bits[3] |= (sign << 31);
    one.bits[3] |= (exp << 16);
    s21_add(*result, one, result);
  }
  return check;
}

int s21_round(s21_decimal value, s21_decimal* result) {
  s21_setBinaryValue(result, 0, 0, 0, 0, 0);
  int exp = 0;
  int sign = 0;
  int check = 0;
  unsigned int rem = 0;

  if (value.bits[3]) {
    exp = s21_getDecPow(value);
    sign = s21_getSign(value);
  }

  if (exp > 28 || exp < 0) check = 1;

  if (!check) {
    while (exp && !check) {
      rem = s21_decrement(&value);
      exp--;
    }

    s21_copyDec(value, result);
    result->bits[3] |= (sign << 31);
    if (rem >= 5) {
      s21_decimal one = {.bits = {1, 0, 0, 0}};
      one.bits[3] |= (sign << 31);
      one.bits[3] |= (exp << 16);
      s21_add(*result, one, result);
    }
  }
  return check;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
  s21_setBinaryValue(result, 0, 0, 0, 0, 0);
  int exp = 0;
  int sign = 0;
  int check = 0;
  if (value.bits[3]) {
    exp = s21_getDecPow(value);
    sign = s21_getSign(value);
  }
  if (exp > 28 || exp < 0) {
    check = 1;
  }

  if (check == 0) {
    while (exp) {
      s21_decrement(&value);
      exp--;
    }
    result->bits[3] |= (sign << 31);
    s21_copyDec(value, result);
  }
  return check;
}

int s21_negate(s21_decimal value, s21_decimal* result) {
  s21_setBinaryValue(result, 0, 0, 0, 0, 0);
  int check = 0;
  int exp = s21_getDecPow(value);
  if (exp > 28 || exp < 0) {
    check = 1;
  }

  s21_copyDec(value, result);
  result->bits[3] = value.bits[3];
  result->bits[3] ^= (1U << 31);
  return check;
}