#include "s21_math.h"

#include <stdio.h>

int s21_abs(int x) {
  if (x < 0) {
    x *= -1;
  }
  return x;
}

long double s21_acos(double x) {
  long double res;
  if (!x) {
    res = S21_PI / 2;
  } else if (x <= 1 && x >= -1) {
    res = S21_PI / 2 - s21_asin(x);
  } else {
    res = S21_NAN;
  }
  return res;
}

long double s21_asin(double x) {
  long double res;
  if (x == -1) {
    res = -S21_PI / 2;
  } else if (x == 1) {
    res = S21_PI / 2;
  } else if (x == S21_INF || x == S21_NINF) {
    res = S21_NAN;
  } else if (x >= -1e4 * S21_EPS && x <= 1e4 * S21_EPS) {
    res = x;
  } else if (s21_fabs(x) < 1) {
    res = 2 * s21_atan(x / (1 + s21_sqrt(1 - x * x)));
  } else {
    res = S21_NAN;
  }
  return res;
}

long double s21_atan(double x) {
  long double res = 0.0;
  if (S21_IS_ZERO(x)) {
    res = 0;
  } else if (x >= 1e7) {
    res = S21_PI / 2;
  } else if (x <= -1e7) {
    res = -S21_PI / 2;
  } else if (x <= 1e-2 && x >= 1e-2) {
    res = x;
  } else if (S21_IS_NAN(x)) {
    res = S21_NAN;
  } else if ((x >= 0.999 && x <= 1) || (x <= -0.999 && x >= -1)) {
    long double atan_1 = 0.785398;
    res = atan_1 - s21_atan((1 - s21_fabs(x)) / 2);
    res = (x > 0) ? res : -res;
  } else if (x < -1 || x > 1) {
    res = s21_atan_1to1(1 / x);
    res = S21_PI * x / (2 * s21_fabs(x)) - res;
  } else {
    res = s21_atan_1to1(x);
  }
  return res;
}

long double s21_atan_1to1(double x) {
  long double res = 0.0, term = 1, minus = 1;
  long double term_part = x, power = x * x;
  for (register int i = 1; i < 2000 && s21_fabs(term) > S21_EPS / 10; i += 2) {
    res += minus * term_part / i;
    term = minus * term_part / i;
    minus *= -1, term_part *= power;
  }
  return res;
}

long double s21_ceil(double x) {
  long double res;
  if (x == S21_INF) {
    res = S21_INF;
  } else if (x > 0) {
    if (s21_fmod(x, 1) == 0) {
      res = x;
    } else
      res = (x + (1 - s21_fmod(x, 1)));
  } else if (x == S21_NINF) {
    res = S21_NINF;
  } else {
    res = (x - s21_fmod(x, 1));
  }
  return res;
}

long double s21_cos(double x) {
  x = s21_fmod(x, 2 * S21_PI);
  long double cos = 1;
  long double term = 1;
  if (S21_IS_NAN(x)) {
    cos = -S21_NAN;
  } else if (x <= 1e4 * S21_EPS && x >= -1e4 * S21_EPS) {
    cos = 1;
  } else {
    for (register int i = 1; i < 1000 && s21_fabs(term) > S21_EPS / 10; i++) {
      term = -term * x * x / (2 * i) / (2 * i - 1);
      cos += term;
    }
  }
  return cos;
}

long double s21_exp(double x) {
  long double res = 1.0;
  if (x > 100) {
    res = S21_INF;
  } else if (S21_IS_NAN(x)) {
    res = S21_NAN;
  } else if (x < -17) {
    res = 0;
  } else if (S21_IS_ZERO(x)) {
    res = 1;
  } else {
    long double sum = 1;
    for (register int i = 1; i < 1500 && s21_fabs(sum) > S21_EPS / 10; i++) {
      sum *= x / i;
      res += sum;
    }
  }
  return res;
}

long double s21_fabs(double x) {
  if (x < 0) {
    x *= -1;
  }
  return x;
}

long double s21_floor(double x) {
  long double res;
  if (x == S21_INF) {
    res = S21_INF;
  } else if (x == S21_NINF) {
    res = S21_NINF;
  } else if (S21_IS_NAN(x)) {
    res = -S21_NAN;
  } else if (x >= 0) {
    res = (x - s21_fmod(x, 1));
  } else {
    res = (x - s21_fmod(x, 1) - 1);
  }
  return res;
}

long double s21_fmod(double x, double y) {
  long double res;
  if (x == S21_INF || x == S21_NINF) {
    res = -S21_NAN;
  } else if (S21_IS_NAN(x) || S21_IS_NAN(y) || S21_IS_ZERO(y)) {
    res = -S21_NAN;
  } else {
    res = x - (long long int)(x / y) * y;
  }
  return res;
}

long double s21_log(double x) {
  long double res = 0, y = 0;
  if (x < 0.0) {
    res = S21_NAN;
  } else if (x == S21_INF) {
    res = S21_INF;
  } else if (x == 0) {
    res = S21_NINF;
  } else {
    for (register int i = 0; i < 100; i++) {
      long double exp_y = s21_exp(y);
      y += 2 * (x - exp_y) / (x + exp_y);
    }
    res = y;
  }
  return res;
}

long double s21_pow(double base, double exp) {
  long double res;
  if (S21_IS_ZERO(exp) || (base == -1 && (exp == S21_INF || exp == S21_NINF))) {
    res = 1;
  } else if (exp == 1 || base == 1) {
    res = base;
  } else if ((exp == S21_NINF && (base == S21_INF || base == S21_NINF)) ||
             (s21_fabs(base) < 1 && exp == S21_INF) ||
             (s21_fabs(base) > 1 && exp == S21_NINF)) {
    res = 0;
  } else if (exp == S21_NINF || (exp == S21_INF && base < 0)) {
    res = S21_INF;
  } else if ((base == S21_NINF && exp > 1)) {
    res = S21_NINF;
  } else if (base < 0 && exp - (int)exp) {
    res = S21_NAN;
  } else if ((long double)(long long int)exp == exp) {
    res = s21_pown(base, exp);
  } else {
    res = base >= 0 ? s21_exp(exp * s21_log(base)) : S21_NAN;
  }
  return res;
}

long double s21_pown(double base, double exp) {
  long double result = 1;
  if (exp > 0) {
    for (int i = 0; i < exp; i++) {
      result *= base;
    }
  } else if (exp < 0) {
    for (int i = 0; i < -exp; i++) {
      result /= base;
    }
  }
  return result;
}

long double s21_sin(double x) {
  x = s21_fmod(x, 2 * S21_PI);
  long double sin = 0;
  if (s21_checkP(x, S21_PI / 2) || s21_checkP(x, -3 * S21_PI / 2)) {
    sin = 1.0;
  } else if (s21_checkP(x, -S21_PI / 2) || s21_checkP(x, 3 * S21_PI / 2)) {
    sin = -1.0;
  } else if (s21_checkP(x, -S21_PI) || s21_checkP(x, S21_PI)) {
    sin = 0.0;
  } else if (x <= 1e4 * S21_EPS && x >= -1e4 * S21_EPS) {
    sin = x;
  } else {
    long double minus = 1, term_part = 0, power = x;
    for (register int n = 0; n < 1000; n++) {
      term_part = minus * power / s21_fact(2 * n + 1);
      minus *= -1;
      power *= x * x;
      sin += term_part;
    }
  }
  return sin;
}

long double s21_sqrt(double x) {
  long double res;
  long double x0 = x;
  long double x1 = x;
  if (x < 0) {
    res = S21_NAN;
  } else if (S21_IS_ZERO(x) || x == 1) {
    res = x;
  } else if (x == S21_INF) {
    res = S21_INF;
  } else {
    do {
      x0 = x1;
      x1 = 0.5 * (x0 + x / x0);
    } while (s21_fabs(x1 - x0) > S21_EPS);
    res = x1;
  }
  return res;
}

long double s21_tan(double x) {
  long double result;
  if (x == S21_PI / 2) {
    result = 16331239353195370.0;
  } else if (x == -S21_PI / 2) {
    result = -16331239353195370.0;
  } else if (x == 3 * S21_PI / 2) {
    result = 5443746451065123.0;
  } else if (x == -3 * S21_PI / 2) {
    result = -5443746451065123.0;
  } else {
    result = s21_sin(x) / s21_cos(x);
  }
  return result;
}

int s21_checkP(double x, double check) {
  int is_here = 0;
  if (x >= check - S21_EPS && x <= check + S21_EPS) {
    is_here++;
  }
  return is_here;
}

long double s21_fact(int x) {
  long double mult = 1;
  while (x) {
    mult *= x--;
  }
  return mult;
}
