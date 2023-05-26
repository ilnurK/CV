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

#endif
