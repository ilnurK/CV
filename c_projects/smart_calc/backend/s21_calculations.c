#include "s21_calculations.h"

lexems_t* getLexemResult(char* inp, errors_e* error, int* is_x) {
  lexems_t* head_l = NULL;
  if (strlen(inp)) {
    head_l = calloc(1, sizeof(struct lexems_t));
    if (head_l) {
      head_l = lexemsSeparate(inp, head_l, is_x, error);
      if (*error == 0 && *is_x == 0) {
        head_l = parse(head_l, error);
        head_l = checkCalcDone(head_l, error);
      }
    } else {
      *error = MEMORY;
    }
  }
  return head_l;
}

double getResult(lexems_t* head_l) {
  double res = 0;
  if (head_l && head_l->next) {
    res = head_l->next->num;
  }
  return res;
}

lexems_t* checkCalcDone(lexems_t* head_l, errors_e* error) {
  double len = getLexemsLen(head_l);
  if (!*error) {
    if (len != 1 || head_l->next->type != NUM) {
      *error = CALC;
    }
  }
  return head_l;
}

lexems_t* parse(lexems_t* head_l, errors_e* error) {
  lexems_t* cur = head_l->next;
  while ((cur = getMostInnerPairPars(head_l->next, error)) != NULL &&
         *error == 0) {
    cur = calcParenthesis(cur, error);
  }
  head_l = calc(head_l, error);
  *error = (getLexemsLen(head_l) != 1) ? CONTACT : *error;
  return head_l;
}

lexems_t* getMostInnerPairPars(lexems_t* cur_start, errors_e* error) {
  lexems_t* cur_open_par = NULL;
  lexems_t* cur = cur_start;
  while (cur != NULL && cur->type != CLOSE_PAR) {
    if (cur->type == OPEN_PAR) {
      cur_open_par = cur;
    }
    cur = cur->next;
  }
  *error = (cur == NULL && cur_open_par != NULL) ? PARENTHESIS : *error;
  return cur_open_par;
}

lexems_t* calcParenthesis(lexems_t* cur, errors_e* error) {
  if (*error == 0) {
    cur = calc(cur, error);
    cur = removeParenthesis(cur);
    int potential_func = cur->type;
    if (potential_func >= SIN && potential_func <= LOG) {
      cur = lexemsApplyFunction(cur, potential_func, error);
    }
  }
  return cur;
}

lexems_t* calc(lexems_t* cur_start, errors_e* error) {
  for (int i = POWER; i <= PLUS && *error == 0; i++) {
    lexems_t* cur = cur_start;
    while (cur != NULL && cur->type != CLOSE_PAR && *error == 0) {
      if (cur->type == i && isCorrectOperation(cur, error)) {
        cur = lexemsApplyOperation(cur, cur->type, error);
      }
      cur = cur->next;
    }
  }
  return cur_start;
}

lexems_t* removeParenthesis(lexems_t* cur) {
  lexems_t* temp = cur;
  if (cur) {
    cur = cur->next;
    if (cur && cur->next && cur->next->type == CLOSE_PAR) {
      cur = lexemsRemoveCurrent(cur->next);
    }
    if (cur && cur->prev->type == OPEN_PAR) {
      cur = lexemsRemoveCurrent(cur->prev);
    }
  }
  return (cur) ? cur : temp;
}

int isCorrectOperation(lexems_t* cur, errors_e* error) {
  int is_correct = 0;
  int prev = cur->prev->type, next;
  if (isOperation(prev) || prev == NUM || prev == CLOSE_PAR ||
      (prev == OPEN_PAR && cur->type == MINUS)) {
    if (cur->next != NULL) {
      next = cur->next->type;
      if (isOperation(next) || next == NUM || next == OPEN_PAR) {
        is_correct = 1;
      }
    }
  }
  *error = (is_correct) ? 0 : CONTACT;
  if (is_correct == 0) {
  }
  return is_correct;
}

int isOperation(int type) { return type >= POWER && type <= DIV; }

lexems_t* lexemsApplyOperation(lexems_t* cur, int type, errors_e* error) {
  if (cur->next->type == VAR_X || cur->prev->type == VAR_X) {
    ;
  } else if (cur->next->num == 0 && (type == DIV || type == MOD)) {
    *error = ZERO;
  } else {
    if (type == POWER) {
      cur->prev->num = pow(cur->prev->num, cur->next->num);
    } else if (type == MUL) {
      cur->prev->num *= cur->next->num;
    } else if (type == DIV) {
      cur->prev->num /= cur->next->num;
    } else if (type == MOD) {
      cur->prev->num = fmod(cur->prev->num, cur->next->num);
    } else if (type == PLUS) {
      cur->prev->num += cur->next->num;
    } else if (type == MINUS) {
      if (!cur->prev || cur->prev->type != NUM) {
        cur->type = NUM;
        cur->num = -cur->next->num;
      } else {
        cur->prev->num -= cur->next->num;
      }
    }
    if (cur->type >= POWER && cur->type <= PLUS) {
      cur = lexemsRemoveCurrent(cur);
    }
    if (cur->next->type == NUM) {
      cur = lexemsRemoveCurrent(cur->next);
    }
  }
  return cur;
}

lexems_t* lexemsApplyFunction(lexems_t* func, int type, errors_e* error) {
  lexems_t* num = func->next;
  if (func->next->num < 0 && type >= SQRT && type <= LOG) {
    *error = DOMAIN_DEF;
  } else if ((type == ACOS || type == ASIN) && fabs(func->next->num) > 1) {
    *error = DOMAIN_DEF;
  } else {
    if (type == SIN) {
      num->num = sin(num->num);
    } else if (type == COS) {
      num->num = cos(num->num);
    } else if (type == TAN) {
      num->num = tan(num->num);
    } else if (type == ACOS) {
      num->num = acos(num->num);
    } else if (type == ASIN) {
      num->num = asin(num->num);
    } else if (type == ATAN) {
      num->num = atan(num->num);
    } else if (type == SQRT) {
      num->num = sqrt(num->num);
    } else if (type == LN) {
      num->num = log(num->num);
    } else if (type == LOG) {
      num->num = log(num->num);
    }
    num->prev = lexemsRemoveCurrent(func);
  }
  return num;
}

lexems_t* changeX(lexems_t* head_l, double x_i) {
  lexems_t* cur = head_l;
  while (cur != NULL) {
    if (cur->type == VAR_X) {
      cur->type = NUM;
      cur->num = x_i;
    } else {
      cur = cur->next;
    }
  }
  return head_l;
}