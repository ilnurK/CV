#ifndef ERROR_MSG_H
#define ERROR_MSG_H

extern const char* errors[];

typedef enum {
  DOMAIN_DEF = 1,
  ZERO = 2,
  PARENTHESIS = 3,
  SYMBOL = 4,
  CONTACT = 5,
  MEMORY = 6,
  CALC = 7
} errors_e;

#endif