// #include <math.h>
#include <stdio.h>

#include "s21_math.h"

int main() {
  printf("%Lf %Lf %Lf %Lf\n", s21_fmod(3, 1.3), s21_fmod(3, -1.3),
         s21_fmod(3, 1.7), s21_fmod(3, -1.7));
  printf("%Lf %Lf %Lf %Lf\n", s21_fmod(3, 2.3), s21_fmod(3, -2.3),
         s21_fmod(3, 2.7), s21_fmod(3, -2.7));
  return 0;
}