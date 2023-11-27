#include "tests.h"

START_TEST(s21_from_decimal_to_float_test_1) {
  float num = 0;
  s21_decimal a = {{8298343, 0, 0, 65536}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, 829834.3);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_2) {
  float num = 0;
  s21_decimal a = {{8934278, 0, 0, 196608}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, 8934.278);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_3) {
  float num = 0;
  s21_decimal a = {{2342382, 0, 0, -2147352576}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, -23423.82);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_4) {
  float num = 0;
  s21_decimal a = {{2734828, 0, 0, -2147352576}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, -27348.28);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_5) {
  float num = 0;
  s21_decimal a = {{823923, 0, 0, 0}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, 823923);
}
END_TEST
// 111101101010010011000101100
// 110001010101000010011110
START_TEST(s21_from_decimal_to_float_test_6) {
  float num = 0;
  s21_decimal a = {{129312300, 0, 0, -2147483648}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, -129312300);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_7) {
  float num = 0;
  s21_decimal a = {{2374478, 0, 0, 131072}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, 23744.78);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_8) {
  float num = 0;
  s21_decimal a = {{2393823, 0, 0, -2147287040}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, -2393.823);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_9) {
  float num = 0;
  s21_decimal a = {{9124792, 0, 0, 65536}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, 912479.2);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_10) {
  float num = 0;
  s21_decimal a = {{1232347, 0, 0, -2147418112}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, -123234.7);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_11) {
  float num = 0;
  s21_decimal a = {{101217, 0, 0, 65536}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, 10121.7);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_12) {
  float num = 0;
  s21_decimal a = {{23748280, 0, 0, -2147483648}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, -23748280);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_13) {
  float num = 0;
  s21_decimal a = {{802000, 0, 0, 0}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, 802000);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_14) {
  float num = 0;
  s21_decimal a = {{13331, 0, 0, 262144}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, 1.3331);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_15) {
  float num = 0;
  s21_decimal a = {{1667283, 0, 0, -2147090432}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, -1.667283);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_16) {
  float num = 0;
  s21_decimal a = {{5632482, 0, 0, 458752}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, 0.5632482);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_17) {
  float num = 0;
  s21_decimal a = {{6527385, 0, 0, -2147024896}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, -0.6527385);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_18) {
  float num = 0;
  s21_decimal a = {{-296, 0, 0, -2147483648}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, -4294967000);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_19) {
  float num = 0;
  s21_decimal a = {{-296, 0, 0, 0}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, 4294967000);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_20) {
  float num = 0;
  s21_decimal a = {{8932617, 0, 0, -2147287040}};

  int res = s21_from_decimal_to_float(a, &num);

  ck_assert_int_eq((int)res, 0);
  ck_assert_float_eq(num, -8932.617);
}
END_TEST

Suite *s21_from_decimal_to_float_suite(void) {
  Suite *s = suite_create("s21_from_decimal_to_float");
  TCase *o = tcase_create("from_decimal_to_float");

  tcase_add_test(o, s21_from_decimal_to_float_test_1);
  tcase_add_test(o, s21_from_decimal_to_float_test_2);
  tcase_add_test(o, s21_from_decimal_to_float_test_3);
  tcase_add_test(o, s21_from_decimal_to_float_test_4);
  tcase_add_test(o, s21_from_decimal_to_float_test_5);
  tcase_add_test(o, s21_from_decimal_to_float_test_6);
  tcase_add_test(o, s21_from_decimal_to_float_test_7);
  tcase_add_test(o, s21_from_decimal_to_float_test_8);
  tcase_add_test(o, s21_from_decimal_to_float_test_9);
  tcase_add_test(o, s21_from_decimal_to_float_test_10);
  tcase_add_test(o, s21_from_decimal_to_float_test_11);
  tcase_add_test(o, s21_from_decimal_to_float_test_12);
  tcase_add_test(o, s21_from_decimal_to_float_test_13);
  tcase_add_test(o, s21_from_decimal_to_float_test_14);
  tcase_add_test(o, s21_from_decimal_to_float_test_15);
  tcase_add_test(o, s21_from_decimal_to_float_test_16);
  tcase_add_test(o, s21_from_decimal_to_float_test_17);
  tcase_add_test(o, s21_from_decimal_to_float_test_18);
  tcase_add_test(o, s21_from_decimal_to_float_test_19);
  tcase_add_test(o, s21_from_decimal_to_float_test_20);

  suite_add_tcase(s, o);
  return s;
}
