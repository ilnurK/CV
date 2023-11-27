#include <check.h>

#include "../backend/s21_backend.h"

START_TEST(credit_test) {
  double res = 0, tol = 1e-6;
  credit_t credit = {.sum = 1234568,
                     .rate = 10,
                     .time = 14,
                     .time_type = MONTHS,
                     .pay_type = DIFFER};
  calcCredit(&credit);
  ck_assert_pstr_eq("98471.50...88918.29", credit.str_monthly);
  res = atof(credit.str_overpay);
  ck_assert_double_eq_tol(res, 77160.5, tol);
  res = atof(credit.str_total);
  ck_assert_double_eq_tol(res, 1311728.50, tol);

  credit_t credit1 = {.sum = 12345680,
                      .rate = 12,
                      .time = 14,
                      .time_type = YEARS,
                      .pay_type = ANNUIT};
  calcCredit(&credit1);
  res = atof(credit1.str_monthly);
  ck_assert_double_eq_tol(res, 152028.35, tol);
  res = atof(credit1.str_overpay);
  ck_assert_double_eq_tol(res, 13195082.6, tol);
  res = atof(credit1.str_total);
  ck_assert_double_eq_tol(res, 25540762.6, tol);
}
END_TEST

START_TEST(deposit_test) {
  double res = 0, tol;
  deposit_t deposit = {.sum = 1234568,
                       .rate = 10,
                       .tax_rate = 13,
                       .period = 14,
                       .capitalization = 0,
                       .increase = 0,
                       .decrease = 0,
                       .cap_period = 0,
                       .inc_period = 0,
                       .dec_period = 0};
  tol = 1e2;
  calcDeposit(&deposit);
  res = atof(deposit.str_rate_gain);
  ck_assert_double_eq_tol(res, 144089.28, tol);
  res = atof(deposit.str_tax_sum);
  ck_assert_double_eq_tol(res, 0, tol);
  res = atof(deposit.str_total);
  ck_assert_double_eq_tol(res, 1378657.28, tol);

  deposit_t deposit2 = {.sum = 1000000,
                        .rate = 10,
                        .tax_rate = 14,
                        .period = 12,
                        .capitalization = 1,
                        .increase = 0,
                        .decrease = 0,
                        .cap_period = MONTHLY,
                        .inc_period = 0,
                        .dec_period = 0};
  tol = 1e3;
  calcDeposit(&deposit2);
  res = atof(deposit2.str_rate_gain);
  ck_assert_double_eq_tol(res, 104744.86, tol);
  res = atof(deposit2.str_tax_sum);
  ck_assert_double_eq_tol(res, 0, tol);
  res = atof(deposit2.str_total);
  ck_assert_double_eq_tol(res, 1104744.86, tol);

  deposit_t deposit3 = {.sum = 1423513,
                        .rate = 131,
                        .tax_rate = 13,
                        .period = 3,
                        .capitalization = 1,
                        .increase = 12340,
                        .decrease = 40,
                        .cap_period = MONTHLY,
                        .inc_period = MONTHLY1,
                        .dec_period = MONTHLY2};
  tol = 1e3;
  calcDeposit(&deposit3);
  res = atof(deposit3.str_rate_gain);
  ck_assert_double_eq_tol(res, 527702, tol);
  res = atof(deposit3.str_tax_sum);
  ck_assert_double_eq_tol(res, 49101.4, tol);
  res = atof(deposit3.str_total);
  ck_assert_double_eq_tol(res, 1983660, tol);

  deposit_t deposit4 = {.sum = 1000000,
                        .rate = 12.5,
                        .tax_rate = 13,
                        .period = 36,
                        .capitalization = 1,
                        .increase = 15000,
                        .decrease = 0,
                        .cap_period = MONTHLY,
                        .inc_period = MONTHLY1,
                        .dec_period = 0};
  tol = 2e3;
  calcDeposit(&deposit4);
  res = atof(deposit4.str_rate_gain);
  ck_assert_double_eq_tol(res, 564732, tol);
  res = atof(deposit4.str_tax_sum);
  ck_assert_double_eq_tol(res, 15713, tol);
  res = atof(deposit4.str_total);
  ck_assert_double_eq_tol(res, 2103732, tol);
}
END_TEST

void tests_credit(int *nf) {
  Suite *s1 = suite_create("Core");
  TCase *tc_credit = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc_credit);
  tcase_add_test(tc_credit, credit_test);

  srunner_run_all(sr, CK_ENV);
  *nf += srunner_ntests_failed(sr);
  srunner_free(sr);
}

void tests_deposit(int *nf) {
  Suite *s1 = suite_create("Core");
  TCase *tc_deposit = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc_deposit);
  tcase_add_test(tc_deposit, deposit_test);

  srunner_run_all(sr, CK_ENV);
  *nf += srunner_ntests_failed(sr);
  srunner_free(sr);
}
