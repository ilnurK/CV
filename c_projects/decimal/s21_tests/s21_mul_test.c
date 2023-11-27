#include "tests.h"

START_TEST(s21_mul_test_1) {
  s21_decimal a = {{-1, -1, -1, 0}};         // 79228162514264337593543950335
  s21_decimal b = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1);
  ck_assert_int_eq((int)res_bits.bits[1], -1);
  ck_assert_int_eq((int)res_bits.bits[2], -1);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_mul_test_2) {
  s21_decimal a = {{-2017942635, 47083, 0, 65536}};  // 20222222222222.9
  s21_decimal b = {{0, 0, 0, 0}};                    // 0
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_3) {
  s21_decimal a = {{292342, 0, 0, 327680}};  // 2.92342
  s21_decimal b = {{0, 0, 0, 0}};            // 0
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_4) {
  s21_decimal a = {{292342, 0, 0, -2147155968}};  // -2.92342
  s21_decimal b = {{781413, 0, 0, -2147483648}};  // -781413
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 806572558);
  ck_assert_int_eq((int)res_bits.bits[1], 53);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 327680);
}
END_TEST

START_TEST(s21_mul_test_5) {
  s21_decimal a = {{-1158315456, -197194979, 33, 0}};  // 626342352523521000000
  s21_decimal b = {{781413, 0, 0, -2147483648}};       // -781413
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1347460288);
  ck_assert_int_eq((int)res_bits.bits[1], -177876063);
  ck_assert_int_eq((int)res_bits.bits[2], 26532164);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_mul_test_6) {
  s21_decimal a = {
      {-1, -1, -1, -2147483648}};     // -79228162514264337593543950335
  s21_decimal b = {{-1, -1, -1, 0}};  // 79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 2);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_mul_test_7) {
  s21_decimal a = {{-1, -1, -1, 0}};  // 79228162514264337593543950335
  s21_decimal b = {{-1, -1, -1, 0}};  // 79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 1);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_mul_test_8) {
  s21_decimal a = {{1015837740, 287445, 0, 0}};  // 1234567890236460
  s21_decimal b = {{-2045900063, 28744, 0, 0}};  // 123456789023457
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 1);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_mul_test_9) {
  s21_decimal a = {{-1345409089, 146074521, 0, 0}};  // 627385293423423423
  s21_decimal b = {
      {1668895137, 1064696021, 0, -2147483648}};  // -4572834592045224353
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 2);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_10) {
  s21_decimal a = {{5, 0, 0, -2147483648}};  // -5
  s21_decimal b = {{0, 0, 0, 0}};            // 0
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_mul_test_11) {
  s21_decimal a = {{351661334, 63675, 0, 0}};  // 273482394234134
  s21_decimal b = {{7, 0, 0, 0}};              // 7
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1833337958);
  ck_assert_int_eq((int)res_bits.bits[1], 445725);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_12) {
  s21_decimal a = {{61237812, 0, 0, -2147024896}};  // -6.1237812
  s21_decimal b = {{81230311, 0, 0, 196608}};       // 81230.311
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -183998228);
  ck_assert_int_eq((int)res_bits.bits[1], 1158184);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2146828288);
}
END_TEST

START_TEST(s21_mul_test_13) {
  s21_decimal a = {{17403, 0, 0, 0}};              // 17403
  s21_decimal b = {{4789282, 0, 0, -2147352576}};  // -47892.82
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1743496022);
  ck_assert_int_eq((int)res_bits.bits[1], 19);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147352576);
}
END_TEST

START_TEST(s21_mul_test_14) {
  s21_decimal a = {{72342342, 0, 0, 524288}};  // 0.72342342
  s21_decimal b = {{2, 0, 0, 1703936}};        // 0.00000000000000000000000002
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 145);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 1835008);
}
END_TEST

START_TEST(s21_mul_test_15) {
  s21_decimal a = {{610781734, 168435, 0, 983040}};  // 0.723423427283494
  s21_decimal b = {{784, 0, 0, 196608}};             // 0.784
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 2111509600);
  ck_assert_int_eq((int)res_bits.bits[1], 132053151);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 1179648);
}
END_TEST

START_TEST(s21_mul_test_16) {
  s21_decimal a = {{7938402, 0, 0, 0}};               // 7938402
  s21_decimal b = {{1830490002, 0, 0, -2147155968}};  // -18304.90002
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1654667292);
  ck_assert_int_eq((int)res_bits.bits[1], 3383300);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147155968);
}
END_TEST

START_TEST(s21_mul_test_17) {
  s21_decimal a = {{2024072662, 184830, 0, 589824}};  // 793840.829392342
  s21_decimal b = {{1265466682, 55512, 0, 524288}};   // 2384234.90002234
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1462472307);
  ck_assert_int_eq((int)res_bits.bits[1], -313858492);
  ck_assert_int_eq((int)res_bits.bits[2], 1026036357);
  ck_assert_int_eq((int)res_bits.bits[3], 1048576);
}
END_TEST

START_TEST(s21_mul_test_18) {
  s21_decimal a = {
      {809805404, 16957601, 0, -2147483648}};         // -72832342523422300
  s21_decimal b = {{-1998155945, 28268, 0, 196608}};  // 121412432334.679
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1804270694);
  ck_assert_int_eq((int)res_bits.bits[1], -938711381);
  ck_assert_int_eq((int)res_bits.bits[2], 479366538);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_mul_test_19) {
  s21_decimal a = {
      {809805404, 16957601, 0, -2147483648}};             // -72832342523422300
  s21_decimal b = {{652204261, 150968, 0, -2147221504}};  // -64840327494.6789
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1062267621);
  ck_assert_int_eq((int)res_bits.bits[1], 1278149839);
  ck_assert_int_eq((int)res_bits.bits[2], -1734909585);
  ck_assert_int_eq((int)res_bits.bits[3], 65536);
}
END_TEST

START_TEST(s21_mul_test_20) {
  s21_decimal a = {{-1318475665, 151177, 0, 0}};          // 649303247399023
  s21_decimal b = {{652206196, 150968, 0, -2147221504}};  // -64840327494.8724
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 446185121);
  ck_assert_int_eq((int)res_bits.bits[1], -1509086043);
  ck_assert_int_eq((int)res_bits.bits[2], -2012665605);
  ck_assert_int_eq((int)res_bits.bits[3], -2147287040);
}
END_TEST

START_TEST(s21_mul_test_21) {
  s21_decimal a = {{0, 0, 0, 0}};  // 0
  s21_decimal b = {{0, 0, 0, 0}};  // 0
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_22) {
  s21_decimal a = {{292342, 0, 0, -2147155968}};  // -2.92342
  s21_decimal b = {{781413, 0, 0, -2147483648}};  // -781413
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 806572558);
  ck_assert_int_eq((int)res_bits.bits[1], 53);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 327680);
}
END_TEST

START_TEST(s21_mul_test_23) {
  s21_decimal a = {{999999999, 0, 0, 0}};  // 999999999
  s21_decimal b = {{999999999, 0, 0, 0}};  // 999999999
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 808348673);
  ck_assert_int_eq((int)res_bits.bits[1], 232830643);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_mul_test_24) {
  s21_decimal a = {{-1, -1, -78293423, 0}};  // 77783903795975396563441680383
  s21_decimal b = {{-2147483648, -2147483648, 628902378,
                    0}};  // 11601201223536716331618402304
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 1);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_mul_test_25) {
  s21_decimal a = {
      {-1, -1, -78293423, -2147483648}};  // -77783903795975396563441680383
  s21_decimal b = {{-2147483648, -2147483648, 628902378,
                    -2147483648}};  // -11601201223536716331618402304
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 1);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_26) {
  s21_decimal a = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal b = {
      {-1, -1, -1, -2147483648}};  // -79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1);
  ck_assert_int_eq((int)res_bits.bits[1], -1);
  ck_assert_int_eq((int)res_bits.bits[2], -1);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_27) {
  s21_decimal a = {{8, 0, 0, 0}};        // 8
  s21_decimal b = {{1, 0, 0, 1835008}};  // 0.0000000000000000000000000001
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 8);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 1835008);
}
END_TEST

START_TEST(s21_mul_test_28) {
  s21_decimal a = {{10, 0, 0, 0}};       // 10
  s21_decimal b = {{1, 0, 0, 1835008}};  // 0.0000000000000000000000000001
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 10);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 1835008);
}
END_TEST

START_TEST(s21_mul_test_29) {
  s21_decimal a = {{8, 0, 0, 0}};            // 8
  s21_decimal b = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 8);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_mul_test_30) {
  s21_decimal a = {{10, 0, 0, 0}};           // 10
  s21_decimal b = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 10);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_mul_test_31) {
  s21_decimal a = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal b = {{-1, -1, -1, 0}};         // 79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1);
  ck_assert_int_eq((int)res_bits.bits[1], -1);
  ck_assert_int_eq((int)res_bits.bits[2], -1);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_mul_test_32) {
  s21_decimal a = {{1, 0, 0, 0}};  // 1
  s21_decimal b = {
      {-1, -1, -1, -2147483648}};  // -79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1);
  ck_assert_int_eq((int)res_bits.bits[1], -1);
  ck_assert_int_eq((int)res_bits.bits[2], -1);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_mul_test_33) {
  s21_decimal a = {{-1, -1, -1, 0}};   // 79228162514264337593543950335
  s21_decimal b = {{6, 0, 0, 65536}};  // 0.6
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1717986919);
  ck_assert_int_eq((int)res_bits.bits[1], -1717986919);
  ck_assert_int_eq((int)res_bits.bits[2], -1717986919);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_34) {
  s21_decimal a = {
      {-1, -1, -1, -2147483648}};            // -79228162514264337593543950335
  s21_decimal b = {{6, 0, 0, -2147418112}};  // -0.6
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1717986919);
  ck_assert_int_eq((int)res_bits.bits[1], -1717986919);
  ck_assert_int_eq((int)res_bits.bits[2], -1717986919);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_mul_test_35) {
  s21_decimal a = {{-1, -1, -1, 0}};         // 79228162514264337593543950335
  s21_decimal b = {{6, 0, 0, -2147418112}};  // -0.6
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1717986919);
  ck_assert_int_eq((int)res_bits.bits[1], -1717986919);
  ck_assert_int_eq((int)res_bits.bits[2], -1717986919);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_mul_test_36) {
  s21_decimal a = {
      {-1, -1, -1, -2147483648}};      // -79228162514264337593543950335
  s21_decimal b = {{6, 0, 0, 65536}};  // 0.6
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1717986919);
  ck_assert_int_eq((int)res_bits.bits[1], -1717986919);
  ck_assert_int_eq((int)res_bits.bits[2], -1717986919);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_mul_test_37) {
  s21_decimal a = {{-1, -1, -1, 0}};    // 79228162514264337593543950335
  s21_decimal b = {{1, 0, 0, 196608}};  // 0.001
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_mul(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1);
  ck_assert_int_eq((int)res_bits.bits[1], -1);
  ck_assert_int_eq((int)res_bits.bits[2], -1);
  ck_assert_int_eq((int)res_bits.bits[3], 196608);
}
END_TEST

Suite *s21_mul_suite(void) {
  Suite *s = suite_create("s21_mul");
  TCase *o = tcase_create("mul");

  tcase_add_test(o, s21_mul_test_1);
  tcase_add_test(o, s21_mul_test_2);
  tcase_add_test(o, s21_mul_test_3);
  tcase_add_test(o, s21_mul_test_4);
  tcase_add_test(o, s21_mul_test_5);
  tcase_add_test(o, s21_mul_test_6);
  tcase_add_test(o, s21_mul_test_7);
  tcase_add_test(o, s21_mul_test_8);
  tcase_add_test(o, s21_mul_test_9);
  tcase_add_test(o, s21_mul_test_10);
  tcase_add_test(o, s21_mul_test_11);
  tcase_add_test(o, s21_mul_test_12);
  tcase_add_test(o, s21_mul_test_13);
  tcase_add_test(o, s21_mul_test_14);
  tcase_add_test(o, s21_mul_test_15);
  tcase_add_test(o, s21_mul_test_16);
  tcase_add_test(o, s21_mul_test_17);
  tcase_add_test(o, s21_mul_test_18);
  tcase_add_test(o, s21_mul_test_19);
  tcase_add_test(o, s21_mul_test_20);
  tcase_add_test(o, s21_mul_test_21);
  tcase_add_test(o, s21_mul_test_22);
  tcase_add_test(o, s21_mul_test_23);
  tcase_add_test(o, s21_mul_test_24);
  tcase_add_test(o, s21_mul_test_25);
  tcase_add_test(o, s21_mul_test_26);
  tcase_add_test(o, s21_mul_test_27);
  tcase_add_test(o, s21_mul_test_28);
  tcase_add_test(o, s21_mul_test_29);
  tcase_add_test(o, s21_mul_test_30);
  tcase_add_test(o, s21_mul_test_31);
  tcase_add_test(o, s21_mul_test_32);
  tcase_add_test(o, s21_mul_test_33);
  tcase_add_test(o, s21_mul_test_34);
  tcase_add_test(o, s21_mul_test_35);
  tcase_add_test(o, s21_mul_test_36);
  tcase_add_test(o, s21_mul_test_37);

  suite_add_tcase(s, o);
  return s;
}