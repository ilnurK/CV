#include "tests.h"

int main() {
  int number_failed = 0;
  Suite *s = suite_create("core");
  suite_add_tcase(s, matrices_tcase());
  suite_add_tcase(s, moves_tcase());

  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}