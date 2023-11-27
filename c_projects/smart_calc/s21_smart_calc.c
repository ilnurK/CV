#include "s21_smart_calc.h"

int main(int argc, char* argv[]) {
  calc_gui(argc, argv);
  errors_e error = 0;
  int is_x = 0;
  lexems_t* head_l = getLexemResult("7modx", &error, &is_x);
  printf("res %lf\n", getResult(head_l));
  printf("%c%s\n", argc, *argv);
  return 0;
}