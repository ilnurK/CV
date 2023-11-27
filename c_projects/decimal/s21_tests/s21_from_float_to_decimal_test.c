#include "tests.h"

START_TEST(s21_from_float_to_decimal_test_1) {
  float num = 829834.3;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 8298343);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 65536);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_2) {
  float num = 8934.278;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 8934278);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 196608);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_3) {
  float num = -23423.82;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 2342382);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147352576);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_4) {
  float num = -27348.28;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 2734828);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147352576);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_5) {
  float num = 823923;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 823923);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_6) {
  float num = -129312300;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 129312300);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_7) {
  float num = 23744.78;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 2374478);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 131072);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_8) {
  float num = -2393.823;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 2393823);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147287040);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_9) {
  float num = 912479.2;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 9124792);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 65536);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_10) {
  float num = -123234.7;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1232347);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147418112);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_11) {
  float num = 10121.7;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 101217);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 65536);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_12) {
  float num = -23748280;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 23748280);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_13) {
  float num = 802000;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 802000);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_14) {
  float num = 1.3331;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 13331);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 262144);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_15) {
  float num = -1.667283;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1667283);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147090432);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_16) {
  float num = 0.5632482;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 5632482);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 458752);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_17) {
  float num = -0.6527385;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 6527385);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147024896);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_18) {
  float num = -4.294967E+09;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -296);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_19) {
  float num = 4.294967E+09;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -296);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_20) {
  float num = -8932.617;
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_from_float_to_decimal(num, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 8932617);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147287040);
}
END_TEST

Suite *s21_from_float_to_decimal_suite(void) {
  Suite *s = suite_create("s21_from_float_to_decimal");
  TCase *o = tcase_create("from_float_to_decimal");

  tcase_add_test(o, s21_from_float_to_decimal_test_1);
  tcase_add_test(o, s21_from_float_to_decimal_test_2);
  tcase_add_test(o, s21_from_float_to_decimal_test_3);
  tcase_add_test(o, s21_from_float_to_decimal_test_4);
  tcase_add_test(o, s21_from_float_to_decimal_test_5);
  tcase_add_test(o, s21_from_float_to_decimal_test_6);
  tcase_add_test(o, s21_from_float_to_decimal_test_7);
  tcase_add_test(o, s21_from_float_to_decimal_test_8);
  tcase_add_test(o, s21_from_float_to_decimal_test_9);
  tcase_add_test(o, s21_from_float_to_decimal_test_10);
  tcase_add_test(o, s21_from_float_to_decimal_test_11);
  tcase_add_test(o, s21_from_float_to_decimal_test_12);
  tcase_add_test(o, s21_from_float_to_decimal_test_13);
  tcase_add_test(o, s21_from_float_to_decimal_test_14);
  tcase_add_test(o, s21_from_float_to_decimal_test_15);
  tcase_add_test(o, s21_from_float_to_decimal_test_16);
  tcase_add_test(o, s21_from_float_to_decimal_test_17);
  tcase_add_test(o, s21_from_float_to_decimal_test_18);
  tcase_add_test(o, s21_from_float_to_decimal_test_19);
  tcase_add_test(o, s21_from_float_to_decimal_test_20);

  suite_add_tcase(s, o);
  return s;
}
