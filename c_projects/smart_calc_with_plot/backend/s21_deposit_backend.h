#ifndef DEPOSIT_BACK_H
#define DEPOSIT_BACK_H

#include "s21_backend.h"

#define RF_TAX 15e4

typedef enum {
  AT_LAST,
  DAILY,
  WEEKLY,
  MONTHLY,
  QUARTLY,
  HALF_YEAR,
  YEARLY
} capital_e;

typedef enum {
  NONE,
  MONTHLY1,
  MONTHLY2,
  QUARTLY1,
  MONTHLY4,
  HALF_YEAR1,
  YEARLY1
} inc_dec_e;

typedef struct {
  double sum;
  double rate;
  double tax_rate;
  double increase;
  double decrease;
  int capitalization;
  int period;
  capital_e cap_period;
  inc_dec_e inc_period;
  inc_dec_e dec_period;
  char str_rate_gain[MAX_STR];
  char str_tax_sum[MAX_STR];
  char str_total[MAX_STR];
} deposit_t;

void calcDeposit(deposit_t *deposit);
double getRateGain(deposit_t *deposit, double *sum, double *tax_rate);
void checkTax(double *tax_sum, double tax_rate, double rate_gain);

#endif