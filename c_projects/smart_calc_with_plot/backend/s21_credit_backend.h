#ifndef CREDIT_BACK_H
#define CREDIT_BACK_H

#include "s21_backend.h"

#define MONTHS 0
#define YEARS 1

#define ANNUIT 0
#define DIFFER 1

typedef struct {
  double sum;
  double rate;
  double time;
  int time_type;
  int pay_type;
  char str_monthly[MAX_STR];
  char str_overpay[MAX_STR];
  char str_total[MAX_STR];
} credit_t;

void calcCredit(credit_t* credit);
double calcDif(double sum, double rate, double time, double* max, double* min);

#endif