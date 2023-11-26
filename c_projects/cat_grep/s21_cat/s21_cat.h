#ifndef CAT_H
#define CAT_H

typedef struct {
  unsigned int file_on : 1;
  unsigned int option_on : 1;

  unsigned int number_nonblank : 1;
  unsigned int end_show : 1;
  unsigned int number : 1;
  unsigned int squeeze_blank : 1;
  unsigned int tab_show : 1;
  unsigned int view : 1;
} Tcat;

#include "../common/common.h"

void checker(Tcat *cat, int argc, char *argv[], int *files, Tflags *flags);
void isLongOption(Tcat *cat, char *option, Tflags *flags);
void isSmallOption(Tcat *cat, char c, Tflags *flags);

void printer(Tcat *cat, int argc, char *argv[], int *files, Tflags *flags);
void onlyShow();
void doWhatOptionMean(FILE *f, Tcat cat, int *cr, Tflags *flags);
char *getString(FILE *f, Tcat cat, Tflags *flags);
void view(Tcat cat, char *str, int *i, char c);
void counter(int *cr);
void endShow();

#endif
