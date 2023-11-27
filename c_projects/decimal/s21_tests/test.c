#include "tests.h"

int main() {
  int failed_count_add = 0;
  int failed_count_sub = 0;
  int failed_count_mul = 0;
  int failed_count_div = 0;
  int failed_count_is_less = 0;
  int failed_count_is_less_or_equal = 0;
  int failed_count_is_greater = 0;
  int failed_count_is_greater_or_equal = 0;
  int failed_count_is_equal = 0;
  int failed_count_is_not_equal = 0;
  int failed_count_from_int_to_decimal = 0;
  int failed_count_from_float_to_decimal = 0;
  int failed_count_from_decimal_to_int = 0;
  int failed_count_from_decimal_to_float = 0;
  int failed_count_floor = 0;
  int failed_count_round = 0;
  int failed_count_truncate = 0;
  int failed_count_negate = 0;

  //   Suite *s21_from_decimal_to_float;
  Suite *s21_add, *s21_sub, *s21_div, *s21_mul, *s21_is_less,
      *s21_is_less_or_equal, *s21_is_greater, *s21_is_greater_or_equal,
      *s21_is_equal, *s21_is_not_equal, *s21_from_int_to_decimal,
      *s21_from_float_to_decimal, *s21_from_decimal_to_int,
      *s21_from_decimal_to_float, *s21_floor, *s21_round, *s21_truncate,
      *s21_negate;

  //   SRunner *runner_from_decimal_to_float;
  SRunner *runner_add, *runner_sub, *runner_div, *runner_mul,
      *runner_is_less, *runner_is_less_or_equal, *runner_is_greater,
      *runner_is_greater_or_equal, *runner_is_equal, *runner_is_not_equal,
      *runner_from_int_to_decimal, *runner_from_float_to_decimal,
      *runner_from_decimal_to_int, *runner_from_decimal_to_float, *runner_floor,
      *runner_round, *runner_truncate, *runner_negate;

  s21_add = s21_add_suite();
  runner_add = srunner_create(s21_add);
  srunner_set_fork_status(runner_add, CK_NOFORK);
  srunner_run_all(runner_add, CK_NORMAL);
  failed_count_add = srunner_ntests_failed(runner_add);
  srunner_free(runner_add);

  s21_sub = s21_sub_suite();
  runner_sub = srunner_create(s21_sub);
  srunner_set_fork_status(runner_sub, CK_NOFORK);
  srunner_run_all(runner_sub, CK_NORMAL);
  failed_count_sub = srunner_ntests_failed(runner_sub);
  srunner_free(runner_sub);

  s21_div = s21_div_suite();
  runner_div = srunner_create(s21_div);
  srunner_set_fork_status(runner_div, CK_NOFORK);
  srunner_run_all(runner_div, CK_NORMAL);
  failed_count_div = srunner_ntests_failed(runner_div);
  srunner_free(runner_div);

  s21_mul = s21_mul_suite();
  runner_mul = srunner_create(s21_mul);
  srunner_set_fork_status(runner_mul, CK_NOFORK);
  srunner_run_all(runner_mul, CK_NORMAL);
  failed_count_mul = srunner_ntests_failed(runner_mul);
  srunner_free(runner_mul);

  s21_is_less = s21_is_less_suite();
  runner_is_less = srunner_create(s21_is_less);
  srunner_set_fork_status(runner_is_less, CK_NOFORK);
  srunner_run_all(runner_is_less, CK_NORMAL);
  failed_count_is_less = srunner_ntests_failed(runner_is_less);
  srunner_free(runner_is_less);

  s21_is_less_or_equal = s21_is_less_or_equal_suite();
  runner_is_less_or_equal = srunner_create(s21_is_less_or_equal);
  srunner_set_fork_status(runner_is_less_or_equal, CK_NOFORK);
  srunner_run_all(runner_is_less_or_equal, CK_NORMAL);
  failed_count_is_less_or_equal =
      srunner_ntests_failed(runner_is_less_or_equal);
  srunner_free(runner_is_less_or_equal);

  s21_is_greater = s21_is_greater_suite();
  runner_is_greater = srunner_create(s21_is_greater);
  srunner_set_fork_status(runner_is_greater, CK_NOFORK);
  srunner_run_all(runner_is_greater, CK_NORMAL);
  failed_count_is_greater = srunner_ntests_failed(runner_is_greater);
  srunner_free(runner_is_greater);

  s21_is_greater_or_equal = s21_is_greater_or_equal_suite();
  runner_is_greater_or_equal = srunner_create(s21_is_greater_or_equal);
  srunner_set_fork_status(runner_is_greater_or_equal, CK_NOFORK);
  srunner_run_all(runner_is_greater_or_equal, CK_NORMAL);
  failed_count_is_greater_or_equal =
      srunner_ntests_failed(runner_is_greater_or_equal);
  srunner_free(runner_is_greater_or_equal);

  s21_is_equal = s21_is_equal_suite();
  runner_is_equal = srunner_create(s21_is_equal);
  srunner_set_fork_status(runner_is_equal, CK_NOFORK);
  srunner_run_all(runner_is_equal, CK_NORMAL);
  failed_count_is_equal = srunner_ntests_failed(runner_is_equal);
  srunner_free(runner_is_equal);

  s21_is_not_equal = s21_is_not_equal_suite();
  runner_is_not_equal = srunner_create(s21_is_not_equal);
  srunner_set_fork_status(runner_is_not_equal, CK_NOFORK);
  srunner_run_all(runner_is_not_equal, CK_NORMAL);
  failed_count_is_not_equal = srunner_ntests_failed(runner_is_not_equal);
  srunner_free(runner_is_not_equal);

  s21_from_int_to_decimal = s21_from_int_to_decimal_suite();
  runner_from_int_to_decimal = srunner_create(s21_from_int_to_decimal);
  srunner_set_fork_status(runner_from_int_to_decimal, CK_NOFORK);
  srunner_run_all(runner_from_int_to_decimal, CK_NORMAL);
  failed_count_from_int_to_decimal =
      srunner_ntests_failed(runner_from_int_to_decimal);
  srunner_free(runner_from_int_to_decimal);

  s21_from_float_to_decimal = s21_from_float_to_decimal_suite();
  runner_from_float_to_decimal = srunner_create(s21_from_float_to_decimal);
  srunner_set_fork_status(runner_from_float_to_decimal, CK_NOFORK);
  srunner_run_all(runner_from_float_to_decimal, CK_NORMAL);
  failed_count_from_float_to_decimal =
      srunner_ntests_failed(runner_from_float_to_decimal);
  srunner_free(runner_from_float_to_decimal);

  s21_from_decimal_to_float = s21_from_decimal_to_float_suite();
  runner_from_decimal_to_float = srunner_create(s21_from_decimal_to_float);
  srunner_set_fork_status(runner_from_decimal_to_float, CK_NOFORK);
  srunner_run_all(runner_from_decimal_to_float, CK_NORMAL);
  failed_count_from_decimal_to_float =
      srunner_ntests_failed(runner_from_decimal_to_float);
  srunner_free(runner_from_decimal_to_float);

  s21_from_decimal_to_int = s21_from_decimal_to_int_suite();
  runner_from_decimal_to_int = srunner_create(s21_from_decimal_to_int);
  srunner_set_fork_status(runner_from_decimal_to_int, CK_NOFORK);
  srunner_run_all(runner_from_decimal_to_int, CK_NORMAL);
  failed_count_from_decimal_to_int =
      srunner_ntests_failed(runner_from_decimal_to_int);
  srunner_free(runner_from_decimal_to_int);

  s21_floor = s21_floor_suite();
  runner_floor = srunner_create(s21_floor);
  srunner_set_fork_status(runner_floor, CK_NOFORK);
  srunner_run_all(runner_floor, CK_NORMAL);
  failed_count_floor = srunner_ntests_failed(runner_floor);
  srunner_free(runner_floor);

  s21_round = s21_round_suite();
  runner_round = srunner_create(s21_round);
  srunner_set_fork_status(runner_round, CK_NOFORK);
  srunner_run_all(runner_round, CK_NORMAL);
  failed_count_round = srunner_ntests_failed(runner_round);
  srunner_free(runner_round);

  s21_truncate = s21_truncate_suite();
  runner_truncate = srunner_create(s21_truncate);
  srunner_set_fork_status(runner_truncate, CK_NOFORK);
  srunner_run_all(runner_truncate, CK_NORMAL);
  failed_count_truncate = srunner_ntests_failed(runner_truncate);
  srunner_free(runner_truncate);

  s21_negate = s21_negate_suite();
  runner_negate = srunner_create(s21_negate);
  srunner_set_fork_status(runner_negate, CK_NOFORK);
  srunner_run_all(runner_negate, CK_NORMAL);
  failed_count_negate = srunner_ntests_failed(runner_negate);
  srunner_free(runner_negate);

  int all_count =
      failed_count_add + failed_count_sub + failed_count_div +
      failed_count_mul + failed_count_is_less +
      failed_count_is_less_or_equal + failed_count_is_greater +
      failed_count_is_greater_or_equal + failed_count_is_equal +
      failed_count_is_not_equal + failed_count_from_int_to_decimal +
      failed_count_from_float_to_decimal + failed_count_from_decimal_to_int +
      failed_count_from_decimal_to_float + failed_count_floor +
      failed_count_round + failed_count_truncate + failed_count_negate;

  return (all_count != 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}
