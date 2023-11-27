#include "s21_deposit_backend.h"

void calcDeposit(deposit_t *deposit) {
  double tax_rate = deposit->tax_rate / 100;
  double sum = deposit->sum, tax_sum = 0;
  double rate_gain = getRateGain(deposit, &sum, &tax_sum);
  if (!tax_sum && rate_gain > RF_TAX) {
    tax_sum = (rate_gain - RF_TAX) * tax_rate;
  }
  sprintf(deposit->str_rate_gain, "%.2lf", rate_gain);
  sprintf(deposit->str_tax_sum, "%.2lf", tax_sum);
  sprintf(deposit->str_total, "%.2lf", sum);
}

double getRateGain(deposit_t *deposit, double *sum, double *tax_sum) {
  double rate_gain = 0;
  double rate = deposit->rate / 100;
  double tax_rate = deposit->tax_rate / 100;
  int period = deposit->period;
  capital_e cap_per = deposit->cap_period;
  inc_dec_e inc_per = deposit->inc_period;
  inc_dec_e dec_per = deposit->dec_period;
  int inc_dec_periods[] = {0, 30, 60, 90, 120, 180, 360};
  int cap_periods[] = {0, 1, 7, 30, 90, 120, 270, 360};
  inc_per = inc_dec_periods[inc_per];
  dec_per = inc_dec_periods[dec_per];
  cap_per = cap_periods[cap_per];
  double increase = deposit->increase, decrease = deposit->decrease;
  double rate_yearly = 0;
  int days = period * 30.4;
  for (int i = 0; i <= days; i++) {
    double daily = *sum * rate / 365;
    rate_gain += daily;
    *sum +=
        (cap_per && i && i % cap_per == 0) ? *sum * rate / (365 / cap_per) : 0;
    *sum += (increase && inc_per && i && i % inc_per == 0) ? increase : 0;
    *sum -= (decrease && dec_per && i && i % dec_per == 0) ? decrease : 0;

    (i && i % 364 == 0) ? checkTax(tax_sum, tax_rate, rate_gain - rate_yearly)
                        : 0;
    rate_yearly = (i % 364 == 0) ? rate_gain : rate_yearly;
  }
  *sum = (deposit->capitalization) ? *sum : *sum + rate_gain;
  return rate_gain;
}

void checkTax(double *tax_sum, double tax_rate, double income) {
  if (income > RF_TAX) {
    *tax_sum += (income - RF_TAX) * tax_rate;
  }
}
