#include "tests.h"

START_TEST(s21_add_test_1) {
  s21_decimal a = {{-1, -1, -1, 0}};         // 79228162514264337593543950335
  s21_decimal b = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -2);
  ck_assert_int_eq((int)res_bits.bits[1], -1);
  ck_assert_int_eq((int)res_bits.bits[2], -1);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_2) {
  s21_decimal a = {{-2017942635, 47083, 0, 65536}};  // 20222222222222.9
  s21_decimal b = {{0, 0, 0, 0}};                    // 0
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -2017942635);
  ck_assert_int_eq((int)res_bits.bits[1], 47083);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 65536);
}
END_TEST

START_TEST(s21_add_test_3) {
  s21_decimal a = {{292342, 0, 0, 327680}};  // 2.92342
  s21_decimal b = {{0, 0, 0, 0}};            // 0
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 292342);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 327680);
}
END_TEST

START_TEST(s21_add_test_4) {
  s21_decimal a = {{292342, 0, 0, -2147155968}};  // -2.92342
  s21_decimal b = {{781413, 0, 0, -2147483648}};  // -781413
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 832181014);
  ck_assert_int_eq((int)res_bits.bits[1], 18);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147155968);
}
END_TEST

START_TEST(s21_add_test_5) {
  s21_decimal a = {{-1158315456, -197194979, 33, 0}};  // 626342352523521000000
  s21_decimal b = {{781413, 0, 0, -2147483648}};       // -781413
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1159096869);
  ck_assert_int_eq((int)res_bits.bits[1], -197194979);
  ck_assert_int_eq((int)res_bits.bits[2], 33);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_6) {
  s21_decimal a = {
      {-1, -1, -1, -2147483648}};     // -79228162514264337593543950335
  s21_decimal b = {{-1, -1, -1, 0}};  // 79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_add_test_7) {
  s21_decimal a = {{-1, -1, -1, 0}};  // 79228162514264337593543950335
  s21_decimal b = {{-1, -1, -1, 0}};  // 79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 1);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_8) {
  s21_decimal a = {{1015837740, 287445, 0, 0}};  // 1234567890236460
  s21_decimal b = {{-2045900063, 28744, 0, 0}};  // 123456789023457
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1030062323);
  ck_assert_int_eq((int)res_bits.bits[1], 316189);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_9) {
  s21_decimal a = {{-1345409089, 146074521, 0, 0}};  // 627385293423423423
  s21_decimal b = {
      {1668895137, 1064696021, 0, -2147483648}};  // -4572834592045224353
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1280663070);
  ck_assert_int_eq((int)res_bits.bits[1], 918621499);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_add_test_10) {
  s21_decimal a = {{5, 0, 0, -2147483648}};  // -5
  s21_decimal b = {{0, 0, 0, 0}};            // 0
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 5);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_add_test_11) {
  s21_decimal a = {{351661334, 63675, 0, 0}};  // 273482394234134
  s21_decimal b = {{7, 0, 0, 0}};              // 7
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 351661341);
  ck_assert_int_eq((int)res_bits.bits[1], 63675);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_12) {
  s21_decimal a = {{61237812, 0, 0, -2147024896}};  // -6.1237812
  s21_decimal b = {{81230311, 0, 0, 196608}};       // 81230.311
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 493053244);
  ck_assert_int_eq((int)res_bits.bits[1], 189);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 458752);
}
END_TEST

START_TEST(s21_add_test_13) {
  s21_decimal a = {{17403, 0, 0, 0}};              // 17403
  s21_decimal b = {{4789282, 0, 0, -2147352576}};  // -47892.82
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 3048982);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147352576);
}
END_TEST

START_TEST(s21_add_test_14) {
  s21_decimal a = {{72342342, 0, 0, 524288}};  // 0.72342342
  s21_decimal b = {{2, 0, 0, 1703936}};        // 0.00000000000000000000000002
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1364721666);
  ck_assert_int_eq((int)res_bits.bits[1], 936107310);
  ck_assert_int_eq((int)res_bits.bits[2], 3921686);
  ck_assert_int_eq((int)res_bits.bits[3], 1703936);
}
END_TEST

START_TEST(s21_add_test_15) {
  s21_decimal a = {{610781734, 168435, 0, 983040}};  // 0.723423427283494
  s21_decimal b = {{784, 0, 0, 196608}};             // 0.784
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1575537190);
  ck_assert_int_eq((int)res_bits.bits[1], 350974);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 983040);
}
END_TEST

START_TEST(s21_add_test_16) {
  s21_decimal a = {{7938402, 0, 0, 0}};               // 7938402
  s21_decimal b = {{1830490002, 0, 0, -2147155968}};  // -18304.90002
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1735727534);
  ck_assert_int_eq((int)res_bits.bits[1], 184);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 327680);
}
END_TEST

START_TEST(s21_add_test_17) {
  s21_decimal a = {{2024072662, 184830, 0, 589824}};  // 793840.829392342
  s21_decimal b = {{1265466682, 55512, 0, 524288}};   // 2384234.90002234
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1793837594);
  ck_assert_int_eq((int)res_bits.bits[1], 739953);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 589824);
}
END_TEST

START_TEST(s21_add_test_18) {
  s21_decimal a = {
      {809805404, 16957601, 0, -2147483648}};         // -72832342523422300
  s21_decimal b = {{-1998155945, 28268, 0, 196608}};  // 121412432334.679
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 54741001);
  ck_assert_int_eq((int)res_bits.bits[1], -222296264);
  ck_assert_int_eq((int)res_bits.bits[2], 3);
  ck_assert_int_eq((int)res_bits.bits[3], -2147287040);
}
END_TEST

START_TEST(s21_add_test_19) {
  s21_decimal a = {
      {809805404, 16957601, 0, -2147483648}};             // -72832342523422300
  s21_decimal b = {{652204261, 150968, 0, -2147221504}};  // -64840327494.6789
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1602075995);
  ck_assert_int_eq((int)res_bits.bits[1], 2072438309);
  ck_assert_int_eq((int)res_bits.bits[2], 39);
  ck_assert_int_eq((int)res_bits.bits[3], -2147221504);
}
END_TEST

START_TEST(s21_add_test_20) {
  s21_decimal a = {{-1318475665, 151177, 0, 0}};          // 649303247399023
  s21_decimal b = {{652206196, 150968, 0, -2147221504}};  // -64840327494.8724
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 140742524);
  ck_assert_int_eq((int)res_bits.bits[1], 1511625962);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 262144);
}
END_TEST

START_TEST(s21_add_test_21) {
  s21_decimal a = {{0, 0, 0, 0}};  // 0
  s21_decimal b = {{0, 0, 0, 0}};  // 0
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_22) {
  s21_decimal a = {{292342, 0, 0, -2147155968}};  // -2.92342
  s21_decimal b = {{781413, 0, 0, -2147483648}};  // -781413
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 832181014);
  ck_assert_int_eq((int)res_bits.bits[1], 18);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], -2147155968);
}
END_TEST

START_TEST(s21_add_test_23) {
  s21_decimal a = {{999999999, 0, 0, 0}};  // 999999999
  s21_decimal b = {{999999999, 0, 0, 0}};  // 999999999
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1999999998);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_add_test_24) {
  s21_decimal a = {{-1, -1, -78293423, 0}};  // 77783903795975396563441680383
  s21_decimal b = {{-2147483648, -2147483648, 628902378,
                    0}};  // 11601201223536716331618402304
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 1);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_add_test_25) {
  s21_decimal a = {
      {-1, -1, -78293423, -2147483648}};  // -77783903795975396563441680383
  s21_decimal b = {{-2147483648, -2147483648, 628902378,
                    -2147483648}};  // -11601201223536716331618402304
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 2);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_add_test_26) {
  s21_decimal a = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal b = {
      {-1, -1, -1, -2147483648}};  // -79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 2);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_27) {
  s21_decimal a = {{8, 0, 0, 0}};        // 8
  s21_decimal b = {{1, 0, 0, 1835008}};  // 0.0000000000000000000000000001
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 1073741824);
  ck_assert_int_eq((int)res_bits.bits[1], -24903193);
  ck_assert_int_eq((int)res_bits.bits[2], 433680868);
  ck_assert_int_eq((int)res_bits.bits[3], 1769472);
}
END_TEST

START_TEST(s21_add_test_28) {
  s21_decimal a = {{10, 0, 0, 0}};       // 10
  s21_decimal b = {{1, 0, 0, 1835008}};  // 0.0000000000000000000000000001
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 268435456);
  ck_assert_int_eq((int)res_bits.bits[1], 1042612833);
  ck_assert_int_eq((int)res_bits.bits[2], 542101086);
  ck_assert_int_eq((int)res_bits.bits[3], 1769472);
}
END_TEST

START_TEST(s21_add_test_29) {
  s21_decimal a = {{8, 0, 0, 0}};            // 8
  s21_decimal b = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 7);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_30) {
  s21_decimal a = {{10, 0, 0, 0}};           // 10
  s21_decimal b = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], 9);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_31) {
  s21_decimal a = {{1, 0, 0, -2147483648}};  // -1
  s21_decimal b = {{-1, -1, -1, 0}};         // 79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -2);
  ck_assert_int_eq((int)res_bits.bits[1], -1);
  ck_assert_int_eq((int)res_bits.bits[2], -1);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_32) {
  s21_decimal a = {{1, 0, 0, 0}};  // 1
  s21_decimal b = {
      {-1, -1, -1, -2147483648}};  // -79228162514264337593543950335
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -2);
  ck_assert_int_eq((int)res_bits.bits[1], -1);
  ck_assert_int_eq((int)res_bits.bits[2], -1);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_add_test_33) {
  s21_decimal a = {{-1, -1, -1, 0}};   // 79228162514264337593543950335
  s21_decimal b = {{6, 0, 0, 65536}};  // 0.6
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 1);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

// Value was either too large or too small for a Decimal.
START_TEST(s21_add_test_34) {
  s21_decimal a = {
      {-1, -1, -1, -2147483648}};            // -79228162514264337593543950335
  s21_decimal b = {{6, 0, 0, -2147418112}};  // -0.6
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 2);
  ck_assert_int_eq((int)res_bits.bits[0], 0);
  ck_assert_int_eq((int)res_bits.bits[1], 0);
  ck_assert_int_eq((int)res_bits.bits[2], 0);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_35) {
  s21_decimal a = {{-1, -1, -1, 0}};         // 79228162514264337593543950335
  s21_decimal b = {{6, 0, 0, -2147418112}};  // -0.6
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -2);
  ck_assert_int_eq((int)res_bits.bits[1], -1);
  ck_assert_int_eq((int)res_bits.bits[2], -1);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

START_TEST(s21_add_test_36) {
  s21_decimal a = {
      {-1, -1, -1, -2147483648}};      // -79228162514264337593543950335
  s21_decimal b = {{6, 0, 0, 65536}};  // 0.6
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -2);
  ck_assert_int_eq((int)res_bits.bits[1], -1);
  ck_assert_int_eq((int)res_bits.bits[2], -1);
  ck_assert_int_eq((int)res_bits.bits[3], -2147483648);
}
END_TEST

START_TEST(s21_add_test_37) {
  s21_decimal a = {{-1, -1, -1, 0}};    // 79228162514264337593543950335
  s21_decimal b = {{1, 0, 0, 196608}};  // 0.001
  s21_decimal res_bits = {{0, 0, 0, 0}};

  int res = s21_add(a, b, &res_bits);

  ck_assert_int_eq((int)res, 0);
  ck_assert_int_eq((int)res_bits.bits[0], -1);
  ck_assert_int_eq((int)res_bits.bits[1], -1);
  ck_assert_int_eq((int)res_bits.bits[2], -1);
  ck_assert_int_eq((int)res_bits.bits[3], 0);
}
END_TEST

Suite *s21_add_suite(void) {
  Suite *s = suite_create("s21_add");
  TCase *o = tcase_create("add");

  tcase_add_test(o, s21_add_test_1);
  tcase_add_test(o, s21_add_test_2);
  tcase_add_test(o, s21_add_test_3);
  tcase_add_test(o, s21_add_test_4);
  tcase_add_test(o, s21_add_test_5);
  tcase_add_test(o, s21_add_test_6);
  tcase_add_test(o, s21_add_test_7);
  tcase_add_test(o, s21_add_test_8);
  tcase_add_test(o, s21_add_test_9);
  tcase_add_test(o, s21_add_test_10);
  tcase_add_test(o, s21_add_test_11);
  tcase_add_test(o, s21_add_test_12);
  tcase_add_test(o, s21_add_test_13);
  tcase_add_test(o, s21_add_test_14);
  tcase_add_test(o, s21_add_test_15);
  tcase_add_test(o, s21_add_test_16);
  tcase_add_test(o, s21_add_test_17);
  tcase_add_test(o, s21_add_test_18);
  tcase_add_test(o, s21_add_test_19);
  tcase_add_test(o, s21_add_test_20);
  tcase_add_test(o, s21_add_test_21);
  tcase_add_test(o, s21_add_test_22);
  tcase_add_test(o, s21_add_test_23);
  tcase_add_test(o, s21_add_test_24);
  tcase_add_test(o, s21_add_test_25);
  tcase_add_test(o, s21_add_test_26);
  tcase_add_test(o, s21_add_test_27);
  tcase_add_test(o, s21_add_test_28);
  tcase_add_test(o, s21_add_test_29);
  tcase_add_test(o, s21_add_test_30);
  tcase_add_test(o, s21_add_test_31);
  tcase_add_test(o, s21_add_test_32);
  tcase_add_test(o, s21_add_test_33);
  tcase_add_test(o, s21_add_test_34);
  tcase_add_test(o, s21_add_test_35);
  tcase_add_test(o, s21_add_test_36);
  tcase_add_test(o, s21_add_test_37);

  suite_add_tcase(s, o);
  return s;
}
