#ifndef LEXEMS_H
#define LEXEMS_H

#include <ctype.h>

#include "s21_calculations.h"
#include "s21_structs.h"

#define DOT '.'
#define COMMA ','

lexems_t* lexemsSeparate(char* inp, lexems_t* lexems, int* is_x,
                         errors_e* error);
lexems_t* lexemsAddNum(char* inp, lexems_t* lexems, int* i, errors_e* error,
                       int len);
lexems_t* lexemsAddFun(char* inp, lexems_t* lexems, int* i, errors_e* error,
                       int len);
lexems_t* lexemsAddSym(char* inp, lexems_t* lexems, int* i, errors_e* error);
int lexemsAdd(lexems_t** lexems, char* inp, int len, int type);
double strToDouble(char* inp, int len, errors_e* error);

lexems_t* lexemsRemoveCurrent(lexems_t* cur);

void lexemsPrint(lexems_t* lexems);
lexems_t* lexemsCopy(lexems_t* head_l, errors_e* error);
int getLexemsLen(lexems_t* head_l);
lexems_t* lexemsDelete(lexems_t* lexems);

#endif