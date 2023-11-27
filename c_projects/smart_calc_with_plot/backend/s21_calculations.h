#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "s21_backend.h"
#include "s21_error_messages.h"
#include "s21_lexems.h"
#include "s21_structs.h"

lexems_t* getLexemResult(char* inp, errors_e* error, int* is_x);
double getResult(lexems_t* head_l);
lexems_t* parse(lexems_t* head_l, errors_e* error);
lexems_t* calcParenthesis(lexems_t* cur, errors_e* error);
lexems_t* getMostInnerPairPars(lexems_t* cur_start, errors_e* error);
lexems_t* calc(lexems_t* cur_start, errors_e* error);
lexems_t* checkCalcDone(lexems_t* head_l, errors_e* error);
int isCorrectOperation(lexems_t* cur, errors_e* error);
int isOperation(int type);
lexems_t* lexemsApplyOperation(lexems_t* cur, int type, errors_e* error);
lexems_t* lexemsApplyFunction(lexems_t* cur, int type, errors_e* error);
lexems_t* removeParenthesis(lexems_t* cur);
lexems_t* changeX(lexems_t* head_l, double x_i);

#endif