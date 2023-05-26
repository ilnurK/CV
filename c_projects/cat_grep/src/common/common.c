#include "common.h"

char* increaseStr(Tflags* flags, char* str, int* buffer) {
  *buffer *= 2;
  char* str_temp = realloc(str, *buffer);
  if (str_temp) {
    str = str_temp;
  } else {
    flags->err = 1;
  }
  return str;
}