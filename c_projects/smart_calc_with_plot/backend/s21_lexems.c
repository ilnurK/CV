#include "s21_lexems.h"

lexems_t* lexemsSeparate(char* inp, lexems_t* head_l, int* is_x,
                         errors_e* error) {
  char lexems_sym[9] = {"()^/*-+"};
  int len = (int)strlen(inp);
  int i = 0;
  while (i < len && !*error) {
    if (isdigit(inp[i])) {
      head_l = lexemsAddNum(inp, head_l, &i, error, len);
    } else if (isalpha(inp[i])) {
      if (inp[i] == 'x') {
        *error = (i > 0 && isdigit(inp[i - 1])) ? CONTACT : *error;
        lexemsAdd(&head_l, "x", 1, VAR_X), i++;
        *is_x = 1;
      } else {
        head_l = lexemsAddFun(inp, head_l, &i, error, len);
      }
    } else if (strchr(lexems_sym, inp[i])) {
      head_l = lexemsAddSym(inp, head_l, &i, error);
    } else if (inp[i] == ' ') {
      i++;
    } else {
      *error = 1;
    }
  }
  return head_l;
}

lexems_t* lexemsAddNum(char* inp, lexems_t* head_l, int* i, errors_e* error,
                       int len) {
  int i_start = *i, flag_dot_uniq = 0;
  while ((isdigit(inp[*i]) || inp[*i] == DOT || inp[*i] == COMMA) && *i < len) {
    (*i)++;
    if (inp[*i] == DOT || inp[*i] == COMMA) {
      if (!flag_dot_uniq) {
        flag_dot_uniq++;
      } else {
        *error = CONTACT;
      }
    }
  }
  *error = (!isdigit(inp[*i - 1])) ? CONTACT : *error;
  if (!*error) {
    *error = lexemsAdd(&head_l, inp + i_start, *i - i_start, NUM);
  }
  return head_l;
}

lexems_t* lexemsAddFun(char* inp, lexems_t* head_l, int* i, errors_e* error,
                       int len) {
  char temp[5] = {0};
  int j = 0, len_w = 5;
  while (*i < len && j < len_w && isalpha(inp[*i]) && inp[*i] != 'x') {
    temp[j++] = inp[(*i)++];
  }
  lexs_enum type = -1;
  if (!strcmp("sin", temp)) {
    type = SIN;
  } else if (!strcmp("cos", temp)) {
    type = COS;
  } else if (!strcmp("tan", temp)) {
    type = TAN;
  } else if (!strcmp("acos", temp)) {
    type = ACOS;
  } else if (!strcmp("asin", temp)) {
    type = ASIN;
  } else if (!strcmp("atan", temp)) {
    type = ATAN;
  } else if (!strcmp("sqrt", temp)) {
    type = SQRT;
  } else if (!strcmp("ln", temp)) {
    type = LN;
  } else if (!strcmp("log", temp)) {
    type = LOG;
  } else if (!strcmp("mod", temp)) {
    type = MOD;
  }
  if ((int)type == -1) {
    *error = 1;
  } else {
    lexemsAdd(&head_l, temp, j, type);
  }
  return head_l;
}

lexems_t* lexemsAddSym(char* inp, lexems_t* head_l, int* i, errors_e* error) {
  char c = inp[*i];
  lexs_enum type = 0;
  if (c == '(') {
    type = OPEN_PAR;
  } else if (c == ')') {
    type = CLOSE_PAR;
  } else if (c == '^') {
    type = POWER;
  } else if (c == '*') {
    type = MUL;
  } else if (c == '/') {
    type = DIV;
  } else if (c == '+') {
    type = PLUS;
  } else if (c == '-') {
    type = MINUS;
  }
  *error = lexemsAdd(&head_l, inp + *i, 1, type);
  (*i) += 1;
  return head_l;
}

int lexemsAdd(lexems_t** head_l, char* inp, int len, int type) {
  errors_e error = 0;
  lexems_t* cur = *head_l;
  lexems_t* new = calloc(1, sizeof(struct lexems_t));
  if (new) {
    new->type = type;
    new->num = (type == NUM) ? strToDouble(inp, len, &error) : 0;
    new->next = NULL;
    while (cur->next != NULL) {
      cur = cur->next;
    }
    cur->next = new;
    new->prev = cur;
  } else {
    error = MEMORY;
  }
  return error;
}

double strToDouble(char* inp, int len, errors_e* error) {
  double num = 0;
  char* temp = calloc(len + 1, sizeof(char));
  if (temp) {
    memcpy(temp, inp, len);
    num = atof(temp);
    free(temp);
  } else {
    *error = 1;
  }
  return num;
}

lexems_t* lexemsRemoveCurrent(lexems_t* cur) {
  lexems_t* temp = cur->prev;
  if (cur->next != NULL) {
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
  } else {
    cur->prev->next = NULL;
  }
  free(cur);
  return temp;
}

void lexemsPrint(lexems_t* head_l) {
  lexems_t* cur = head_l;
  int flag_end = 1;
  char all_lexems[19][5] = {
      "(",   ")",   "^",   "/",    "*",    "mod",  "-",    "+",  "x",
      "sin", "cos", "tan", "acos", "asin", "atan", "sqrt", "ln", "log",
  };
  while (flag_end) {
    if (cur->type != NUM) {
      printf("%s\n", all_lexems[cur->type]);
    } else {
      printf("%lf\n", cur->num);
    }
    if (cur->next == NULL) {
      flag_end = 0;
    } else {
      cur = cur->next;
    }
  }
}

lexems_t* lexemsCopy(lexems_t* head_l, errors_e* error) {
  lexems_t* copy_l = NULL;
  copy_l = calloc(1, sizeof(struct lexems_t));
  if (copy_l) {
    lexems_t* cur_head = head_l;
    lexems_t* cur_copy = copy_l;
    while (cur_head != NULL && !*error) {
      cur_copy->type = cur_head->type;
      cur_copy->num = (cur_copy->type == NUM) ? cur_head->num : 0;
      cur_head = cur_head->next;
      if (cur_head) {
        *error = lexemsAdd(&copy_l, "\0", 1, 0);
        cur_copy = cur_copy->next;
      }
    }
  } else {
    *error = MEMORY;
  }
  return copy_l;
}

int getLexemsLen(lexems_t* head_l) {
  int len = -1;
  lexems_t* cur = head_l;
  while (cur) {
    cur = cur->next;
    len++;
  }
  return len;
}

lexems_t* lexemsDelete(lexems_t* head_l) {
  while (head_l != NULL) {
    lexems_t* temp = head_l;
    head_l = head_l->next;
    free(temp);
  }
  return head_l;
}