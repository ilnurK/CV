#ifndef S21_MATH
#define S21_MATH

#define S21_EPS 1e-6
#define S21_PI 3.14159265358979323
#define S21_INF 1.0 / 0.0
#define S21_NAN 0.0 / 0.0
#define S21_NINF -1.0 / 0.0
#define S21_IS_ZERO(x) (x == -0.0 || x == 0.0)
#define S21_IS_NAN(x) (x != x)

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_atan_1to1(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);
long double s21_pown(double base, double exp);
int s21_checkP(double x, double check);
long double s21_fact(int x);

#endif