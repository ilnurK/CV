#include "s21_credit_backend.h"

void calcCredit(credit_t* credit) {
  double sum = credit->sum, rate = credit->rate / 100, time = credit->time;
  int time_type = credit->time_type, pay_type = credit->pay_type;
  time *= (time_type == YEARS) ? 12 : 1;
  double overpay = 0, total_pay = sum;
  if (pay_type == DIFFER) {
    double monthly_pay_max, monthly_pay_min;
    char min[127], three_dots[] = "...";
    overpay = calcDif(sum, rate, time, &monthly_pay_max, &monthly_pay_min);
    sprintf(credit->str_monthly, "%.2lf", monthly_pay_max);
    sprintf(min, "%.2lf", monthly_pay_min);
    strcat(credit->str_monthly, three_dots);
    strcat(credit->str_monthly, min);
  } else {
    double m = rate / 12;
    double pow_m = pow(1 + m, (int)time);
    double coef = (pow_m != 1) ? m * pow_m / (pow_m - 1) : m;
    double monthly_pay = sum * coef;
    sprintf(credit->str_monthly, "%.2lf", monthly_pay);
    overpay = monthly_pay * time - sum;
  }
  sprintf(credit->str_overpay, "%.2lf", overpay);
  total_pay += overpay;
  sprintf(credit->str_total, "%.2lf", total_pay);
}

double calcDif(double sum, double rate, double time, double* max, double* min) {
  double total = 0, rem = 0;
  double monthly_pay = (time) ? sum / time : 0;
  for (int i = 0; i < (int)time; i++) {
    rem = sum * rate / 12;
    if (i == 0) {
      *max = rem + monthly_pay;
    } else if (i == (int)time - 1) {
      *min = rem + monthly_pay;
    }
    total += rem;
    sum -= monthly_pay;
  }
  return total;
}