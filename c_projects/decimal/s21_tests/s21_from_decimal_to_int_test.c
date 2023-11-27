#include "tests.h"

START_TEST(s21_from_decimal_to_int_test_1) {
  int num = 0;
  s21_decimal a = {{78293592, 0, 0, 0}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, 78293592);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_2) {
  int num = 0;
  s21_decimal a = {{2392934, 0, 0, -2147483648}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, -2392934);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_3) {
  int num = 0;
  s21_decimal a = {{1, 0, 0, -2147483648}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, -1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_4) {
  int num = 0;
  s21_decimal a = {{72342934, 0, 0, -2147483648}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, -72342934);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_5) {
  int num = 0;
  s21_decimal a = {{82000000, 0, 0, 0}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, 82000000);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_6) {
  int num = 0;
  s21_decimal a = {{734892824, 0, 0, 0}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, 734892824);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_7) {
  int num = 0;
  s21_decimal a = {{9174892, 0, 0, -2147483648}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, -9174892);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_8) {
  int num = 0;
  s21_decimal a = {{23478432, 0, 0, -2147483648}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, -23478432);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_9) {
  int num = 0;
  s21_decimal a = {{283434, 0, 0, -2147483648}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, -283434);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_10) {
  int num = 0;
  s21_decimal a = {{2347, 0, 0, 0}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, 2347);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_11) {
  int num = 0;
  s21_decimal a = {{28823, 0, 0, 0}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, 28823);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_12) {
  int num = 0;
  s21_decimal a = {{199000000, 0, 0, 0}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, 199000000);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_13) {
  int num = 0;
  s21_decimal a = {{2340000, 0, 0, -2147483648}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, -2340000);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_14) {
  int num = 0;
  s21_decimal a = {{3456789, 0, 0, 0}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, 3456789);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_15) {
  int num = 0;
  s21_decimal a = {{912384, 0, 0, 0}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, 912384);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_16) {
  int num = 0;
  s21_decimal a = {{23849234, 0, 0, -2147483648}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, -23849234);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_17) {
  int num = 0;
  s21_decimal a = {{1, 0, 0, 0}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_18) {
  int num = 0;
  s21_decimal a = {{0, 0, 0, 0}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_19) {
  int num = 0;
  s21_decimal a = {{27234, 0, 0, -2147483648}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, -27234);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_20) {
  int num = 0;
  s21_decimal a = {{811231, 0, 0, -2147483648}};

  int res = s21_from_decimal_to_int(a, &num);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(num, -811231);
}
END_TEST

Suite *s21_from_decimal_to_int_suite(void) {
  Suite *s = suite_create("s21_from_decimal_to_int");
  TCase *o = tcase_create("from_decimal_to_int");

  tcase_add_test(o, s21_from_decimal_to_int_test_1);
  tcase_add_test(o, s21_from_decimal_to_int_test_2);
  tcase_add_test(o, s21_from_decimal_to_int_test_3);
  tcase_add_test(o, s21_from_decimal_to_int_test_4);
  tcase_add_test(o, s21_from_decimal_to_int_test_5);
  tcase_add_test(o, s21_from_decimal_to_int_test_6);
  tcase_add_test(o, s21_from_decimal_to_int_test_7);
  tcase_add_test(o, s21_from_decimal_to_int_test_8);
  tcase_add_test(o, s21_from_decimal_to_int_test_9);
  tcase_add_test(o, s21_from_decimal_to_int_test_10);
  tcase_add_test(o, s21_from_decimal_to_int_test_11);
  tcase_add_test(o, s21_from_decimal_to_int_test_12);
  tcase_add_test(o, s21_from_decimal_to_int_test_13);
  tcase_add_test(o, s21_from_decimal_to_int_test_14);
  tcase_add_test(o, s21_from_decimal_to_int_test_15);
  tcase_add_test(o, s21_from_decimal_to_int_test_16);
  tcase_add_test(o, s21_from_decimal_to_int_test_17);
  tcase_add_test(o, s21_from_decimal_to_int_test_18);
  tcase_add_test(o, s21_from_decimal_to_int_test_19);
  tcase_add_test(o, s21_from_decimal_to_int_test_20);

  suite_add_tcase(s, o);
  return s;
}
