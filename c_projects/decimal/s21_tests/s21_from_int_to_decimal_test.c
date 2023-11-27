#include "tests.h"

START_TEST(s21_from_int_to_decimal_test_1) {
  int num = 78293592;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 78293592);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_2) {
  int num = -2392934;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 2392934);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_3) {
  int num = -1;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_4) {
  int num = -72342934;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 72342934);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_5) {
  int num = 82000000;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 82000000);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_6) {
  int num = 734892824;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 734892824);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_7) {
  int num = -9174892;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 9174892);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_8) {
  int num = -23478432;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 23478432);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_9) {
  int num = -283434;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 283434);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_10) {
  int num = 2347;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 2347);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_11) {
  int num = 28823;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 28823);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_12) {
  int num = 199000000;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 199000000);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_13) {
  int num = -2340000;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 2340000);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_14) {
  int num = 3456789;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 3456789);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_15) {
  int num = 912384;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 912384);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_16) {
  int num = -23849234;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 23849234);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_17) {
  int num = 1;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_18) {
  int num = 0;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_19) {
  int num = -27234;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 27234);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_20) {
  int num = -811231;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_int_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 811231);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

Suite *s21_from_int_to_decimal_suite(void) {
  Suite *s = suite_create("s21_from_int_to_decimal");
  TCase *o = tcase_create("from_int_to_decimal");

  tcase_add_test(o, s21_from_int_to_decimal_test_1);
  tcase_add_test(o, s21_from_int_to_decimal_test_2);
  tcase_add_test(o, s21_from_int_to_decimal_test_3);
  tcase_add_test(o, s21_from_int_to_decimal_test_4);
  tcase_add_test(o, s21_from_int_to_decimal_test_5);
  tcase_add_test(o, s21_from_int_to_decimal_test_6);
  tcase_add_test(o, s21_from_int_to_decimal_test_7);
  tcase_add_test(o, s21_from_int_to_decimal_test_8);
  tcase_add_test(o, s21_from_int_to_decimal_test_9);
  tcase_add_test(o, s21_from_int_to_decimal_test_10);
  tcase_add_test(o, s21_from_int_to_decimal_test_11);
  tcase_add_test(o, s21_from_int_to_decimal_test_12);
  tcase_add_test(o, s21_from_int_to_decimal_test_13);
  tcase_add_test(o, s21_from_int_to_decimal_test_14);
  tcase_add_test(o, s21_from_int_to_decimal_test_15);
  tcase_add_test(o, s21_from_int_to_decimal_test_16);
  tcase_add_test(o, s21_from_int_to_decimal_test_17);
  tcase_add_test(o, s21_from_int_to_decimal_test_18);
  tcase_add_test(o, s21_from_int_to_decimal_test_19);
  tcase_add_test(o, s21_from_int_to_decimal_test_20);

  suite_add_tcase(s, o);
  return s;
}
