#include "tests.h"

#include <check.h>

#include "../backend/s21_backend.h"

START_TEST(ordinary_test) {
  errors_e error = 0;
  int is_x = 0;
  double res = 0, tol = 1e-6;
  lexems_t *head_l;
  char inp1[] = "123.32+343-64.2*(36+(15*33-32))/3+34-23*1-1-10+0";
  head_l = getLexemResult(inp1, &error, &is_x);
  res = getResult(head_l);
  ck_assert(error == 0);
  ck_assert_double_eq_tol(res, -10212.28, tol);
  lexemsDelete(head_l);

  char inp2[] = "123.32+343-64.2*(36+(15*33-32))/sin(1)-21+432*34+5";
  head_l = getLexemResult(inp2, &error, &is_x);

  res = getResult(head_l);
  head_l = lexemsDelete(head_l);
  ck_assert(error == 0);
  ck_assert_double_eq_tol(res, -22932.867930, tol);

  char inp3[] = "5*10/2*2";
  head_l = getLexemResult(inp3, &error, &is_x);

  res = getResult(head_l);
  head_l = lexemsDelete(head_l);
  ck_assert(error == 0 && res == 50);

  char inp4[] = "5*10/2/2/2*6";
  head_l = getLexemResult(inp4, &error, &is_x);

  res = getResult(head_l);
  head_l = lexemsDelete(head_l);
  ck_assert(error == 0);
  ck_assert_double_eq_tol(res, 37.5, tol);

  char inp5[] = "8*3sqrt(4)";
  head_l = getLexemResult(inp5, &error, &is_x);
  head_l = lexemsDelete(head_l);
  ck_assert_int_eq(error, CONTACT);

  error = 0;
  char inp6[] = "8*3*sqrt(4)";
  head_l = getLexemResult(inp6, &error, &is_x);
  res = getResult(head_l);
  head_l = lexemsDelete(head_l);
  ck_assert(error == 0);
  ck_assert_double_eq_tol(res, 48, tol);

  error = 0;
  is_x = 0;
  char inp8[] = "(-6+30) *(-0.5)";
  head_l = getLexemResult(inp8, &error, &is_x);
  res = getResult(head_l);
  head_l = lexemsDelete(head_l);
  ck_assert(error == 0);
  ck_assert_double_eq_tol(res, -12, tol);

  char inp9[] = "sqrt(-10)*15";
  head_l = getLexemResult(inp9, &error, &is_x);
  parse(head_l, &error);
  head_l = lexemsDelete(head_l);
  ck_assert(error);

  error = 0;
  char inp10[] = "(((-6)))+30-(-1-(-0.5))";
  head_l = getLexemResult(inp10, &error, &is_x);
  res = getResult(head_l);
  head_l = lexemsDelete(head_l);
  ck_assert(error == 0);
  ck_assert_double_eq_tol(res, 24.5, tol);

  error = 0;
  char inp11[] = "4,*9";
  head_l = getLexemResult(inp11, &error, &is_x);
  res = getResult(head_l);
  head_l = lexemsDelete(head_l);
  ck_assert(error == CONTACT);

  error = 0;
  char inp12[] = "ln(5)*log(11)*6mod3";
  head_l = getLexemResult(inp12, &error, &is_x);
  res = getResult(head_l);
  head_l = lexemsDelete(head_l);
  ck_assert(error == 0);
  ck_assert_double_eq_tol(res, 2.1555813, tol);

  error = 0;
  char inp13[] = "cos(5)*atan(1)*sin(6)/asin(1)";
  head_l = getLexemResult(inp13, &error, &is_x);
  res = getResult(head_l);
  head_l = lexemsDelete(head_l);
  ck_assert(error == 0);
  ck_assert_double_eq_tol(res, -0.0396298, tol);

  error = 0;
  char inp14[] = "tan(5)*acos(0.4)^sin(8)";
  head_l = getLexemResult(inp14, &error, &is_x);
  res = getResult(head_l);
  lexemsPrint(head_l);
  lexems_t *copy = lexemsCopy(head_l, &error);
  head_l = lexemsDelete(head_l);
  copy = lexemsDelete(copy);
  ck_assert(error == 0);
  ck_assert_double_eq_tol(res, -3.912803, tol);
}
END_TEST

START_TEST(vars_x_test) {
  errors_e error = 0;
  int is_x = 0;
  lexems_t *head_l;
  char inp7[] = "xx";
  head_l = getLexemResult(inp7, &error, &is_x);
  if (is_x) {
    changeX(head_l, 5);
    parse(head_l, &error);
  }
  getResult(head_l);
  head_l = lexemsDelete(head_l);
  ck_assert(error == CONTACT);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc_calc = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc_calc);
  tcase_add_test(tc_calc, ordinary_test);
  tcase_add_test(tc_calc, vars_x_test);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  tests_credit(&nf);
  tests_deposit(&nf);
  return nf == 0 ? 0 : 1;
}
