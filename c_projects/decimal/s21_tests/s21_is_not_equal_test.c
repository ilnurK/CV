#include "tests.h"

START_TEST(s21_is_not_equal_test_1) {
  s21_decimal a = {
      {7823482, 278348234, 23742342, 131072}};  // 4379689077799819450709034.18
  s21_decimal b = {
      {7238423, 2378423, 2734234, 262144}};  // 5043771484585041116151.4775

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_2) {
  s21_decimal a = {{72342, 0, 0, -2147352576}};  // -723.42
  s21_decimal b = {{72342, 0, 0, -2147352576}};  // -723.42

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_not_equal_test_3) {
  s21_decimal a = {{8234, 238423, 23482, 65536}};  // 43316644536286667866935.4
  s21_decimal b = {{234, 2342, 0, -2147155968}};   // -100588134.07466

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_4) {
  s21_decimal a = {
      {7234, 238423, -234723, -2147483648}};  // -79223832639156148285447609410
  s21_decimal b = {
      {7234, 238423, -234723, -2147483648}};  // -79223832639156148285447609410

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_not_equal_test_5) {
  s21_decimal a = {{2124678, 0, 0, -2147287040}};  // -2124.678
  s21_decimal b = {{2124678, 0, 0, -2147155968}};  // -21.24678

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_6) {
  s21_decimal a = {{7283842, 0, 0, 720896}};  // 0.00007283842
  s21_decimal b = {{7283842, 0, 0, 720896}};  // 0.00007283842

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_not_equal_test_7) {
  s21_decimal a = {{28342, 293942, 9123, 262144}};  // 16828964744692351634.1942
  s21_decimal b = {{823, 2234, 234234, 262144}};  // 432085465137087807016.2231

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_8) {
  s21_decimal a = {{723, 2323, 9, 983040}};  // 166020.706640594993875
  s21_decimal b = {{723, 2323, 9, 983040}};  // 166020.706640594993875

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_not_equal_test_9) {
  s21_decimal a = {{8923, 90, 0, -2147155968}};  // -3865470.65563
  s21_decimal b = {{8923, 90, 2, -2147352576}};  // -368934885339661687.95

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_10) {
  s21_decimal a = {{0, 0, 23423, 720896}};  // 4320780864384.98827501568
  s21_decimal b = {{0, 0, 23423, 720896}};  // 4320780864384.98827501568

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_not_equal_test_11) {
  s21_decimal a = {{-234234, 932, 19231, 655360}};  // 35474933528551.5591380230
  s21_decimal b = {
      {-234823, -2387423, 237472, 655360}};  // 438060364516212.8938920633

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_12) {
  s21_decimal a = {
      {0, 83423, 23423, -2147287040}};  // -432078086796797884235.776
  s21_decimal b = {
      {0, 83423, 23423, -2147287040}};  // -432078086796797884235.776

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_not_equal_test_13) {
  s21_decimal a = {
      {823, 2387482, -23842, 1310720}};  // 792277227.07002386367524111159
  s21_decimal b = {
      {8234, 23891, -1347324, -2147221504}};  // -7920330877325207355668615.1722

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_14) {
  s21_decimal a = {
      {-7238423, 0, 923423, -2147024896}};  // -1703414775277709956.9630441
  s21_decimal b = {
      {-7238423, 0, 923423, -2147024896}};  // -1703414775277709956.9630441

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_not_equal_test_15) {
  s21_decimal a = {{28994, 2378193, -13843,
                    -2147221504}};  // -7922790715599633949337953.5170
  s21_decimal b = {
      {200023, 878323, 134234234, 0}};  // 2476184560532213568217746775

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_16) {
  s21_decimal a = {
      {7234, 234923, 23423, -2147483648}};  // -432078087447485429587010
  s21_decimal b = {
      {7234, 234923, 23423, -2147483648}};  // -432078087447485429587010

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_not_equal_test_17) {
  s21_decimal a = {
      {289293, 237823, -12391, 655360}};  // 7922793394065954170.0497402381
  s21_decimal b = {
      {82342, -234, 2838, -2147221504}};  // -5237030642425639477.2902

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_18) {
  s21_decimal a = {{237423, 23942, 0, 0}};  // 102830107238255
  s21_decimal b = {{237423, 23942, 0, 0}};  // 102830107238255

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_is_not_equal_test_19) {
  s21_decimal a = {{2, 392, 0, 0}};          // 1683627180034
  s21_decimal b = {{823, 239923, 9923, 0}};  // 183047042473881319244599

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_is_not_equal_test_20) {
  s21_decimal a = {
      {2734, -23874283, 2384234, -2147221504}};  // -4398137275404162809672.7726
  s21_decimal b = {
      {2734, -23874283, 2384234, -2147221504}};  // -4398137275404162809672.7726

  int res = s21_is_not_equal(a, b);

  ck_assert_int_eq(res, 0);
}
END_TEST

Suite *s21_is_not_equal_suite(void) {
  Suite *s = suite_create("s21_is_not_equal");
  TCase *o = tcase_create("is_not_equal");

  tcase_add_test(o, s21_is_not_equal_test_1);
  tcase_add_test(o, s21_is_not_equal_test_2);
  tcase_add_test(o, s21_is_not_equal_test_3);
  tcase_add_test(o, s21_is_not_equal_test_4);
  tcase_add_test(o, s21_is_not_equal_test_5);
  tcase_add_test(o, s21_is_not_equal_test_6);
  tcase_add_test(o, s21_is_not_equal_test_7);
  tcase_add_test(o, s21_is_not_equal_test_8);
  tcase_add_test(o, s21_is_not_equal_test_9);
  tcase_add_test(o, s21_is_not_equal_test_10);
  tcase_add_test(o, s21_is_not_equal_test_11);
  tcase_add_test(o, s21_is_not_equal_test_12);
  tcase_add_test(o, s21_is_not_equal_test_13);
  tcase_add_test(o, s21_is_not_equal_test_14);
  tcase_add_test(o, s21_is_not_equal_test_15);
  tcase_add_test(o, s21_is_not_equal_test_16);
  tcase_add_test(o, s21_is_not_equal_test_17);
  tcase_add_test(o, s21_is_not_equal_test_18);
  tcase_add_test(o, s21_is_not_equal_test_19);
  tcase_add_test(o, s21_is_not_equal_test_20);

  suite_add_tcase(s, o);
  return s;
}