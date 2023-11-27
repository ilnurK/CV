#include "tests.h"

START_TEST(s21_round_test_1) {
  s21_decimal a = {{0, 0, 0, 0}};  // 0
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test_2) {
  s21_decimal a = {{885678421, 180172, 0, 589824}};  // 773833.733333333
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 773834);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test_3) {
  s21_decimal a = {{1317904309, 19, 0, 393216}};  // 82922.282933
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 82922);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test_4) {
  s21_decimal a = {{1513097376, 132222, 0, -2146893824}};  // -567890.678909088
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 567891);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_round_test_5) {
  s21_decimal a = {{-967725593, 870, 0, -2147024896}};  // -373994.8789223
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 373995);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_round_test_6) {
  s21_decimal a = {
      {-1, -1, -1, -2147483648}};  // -79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1);
  ck_assert_int_eq((int)res_bits.bits[1], -1);
  ck_assert_int_eq((int)res_bits.bits[2], -1);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_round_test_7) {
  s21_decimal a = {{-1, -1, -1, 0}};  // 79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1);
  ck_assert_int_eq((int)res_bits.bits[1], -1);
  ck_assert_int_eq((int)res_bits.bits[2], -1);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test_8) {
  s21_decimal a = {{1779055156, 182266, 0, 0}};  // 782828288227892
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1779055156);
  ck_assert_int_eq((int)res_bits.bits[1], 182266);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test_9) {
  s21_decimal a = {
      {998586545, 1601468955, 0, -2147483648}};  // -6878256788282882225
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 998586545);
  ck_assert_int_eq((int)res_bits.bits[1], 1601468955);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_round_test_10) {
  s21_decimal a = {{1779615721, 182266, 0, 196608}};  // 782828288788.457
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1144240916);
  ck_assert_int_eq((int)res_bits.bits[1], 182);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test_11) {
  s21_decimal a = {{1779083721, 182266, 0, -2147287040}};  // -782828288256.457
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1144240384);
  ck_assert_int_eq((int)res_bits.bits[1], 182);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_round_test_12) {
  s21_decimal a = {{-940046727, 121876, 0, 917504}};  // 5.23456789087865
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 5);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test_13) {
  s21_decimal a = {{-1867261908, 148600, 0, -2146697216}};  // -638.234567890988
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 638);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_round_test_14) {
  s21_decimal a = {{-458206728, 204849, 0, 458752}};  // 87982359.2378872
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 87982359);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test_15) {
  s21_decimal a = {{-2018871682, 41499, 0, -2147352576}};  //-1782391239123.18
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -20188717);
  ck_assert_int_eq((int)res_bits.bits[1], 414);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_round_test_16) {
  s21_decimal a = {{-27362242, 75629, 0, -2147287040}};  // -324828349234.238
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1589165262);
  ck_assert_int_eq((int)res_bits.bits[1], 75);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_round_test_17) {
  s21_decimal a = {{2116047141, 54697, 0, -2147090432}};  // -234923942.236453
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 234923942);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_round_test_18) {
  s21_decimal a = {{1832389311, 65997, 0, 720896}};  // 2834.56789023423
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 2835);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test_19) {
  s21_decimal a = {{3, 0, 0, 0}};  // 3
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 3);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_round_test_20) {
  s21_decimal a = {{3, 0, 0, -2147483648}};  // -3
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_round(a, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 3);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

Suite *s21_round_suite(void) {
  Suite *s = suite_create("s21_round");
  TCase *o = tcase_create("round");

  tcase_add_test(o, s21_round_test_1);
  tcase_add_test(o, s21_round_test_2);
  tcase_add_test(o, s21_round_test_3);
  tcase_add_test(o, s21_round_test_4);
  tcase_add_test(o, s21_round_test_5);
  tcase_add_test(o, s21_round_test_6);
  tcase_add_test(o, s21_round_test_7);
  tcase_add_test(o, s21_round_test_8);
  tcase_add_test(o, s21_round_test_9);
  tcase_add_test(o, s21_round_test_10);
  tcase_add_test(o, s21_round_test_11);
  tcase_add_test(o, s21_round_test_12);
  tcase_add_test(o, s21_round_test_13);
  tcase_add_test(o, s21_round_test_14);
  tcase_add_test(o, s21_round_test_15);
  tcase_add_test(o, s21_round_test_16);
  tcase_add_test(o, s21_round_test_17);
  tcase_add_test(o, s21_round_test_18);
  tcase_add_test(o, s21_round_test_19);
  tcase_add_test(o, s21_round_test_20);

  suite_add_tcase(s, o);
  return s;
}
