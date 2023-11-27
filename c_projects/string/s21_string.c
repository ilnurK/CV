#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *ptr = str;
  void *result = s21_NULL;

  while (n--)
    if ((unsigned char)c == *ptr++) {
      result = (void *)(ptr - 1);
      n = 0;
    }
  return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *c1 = str1, *c2 = str2, *end = c1 + n;
  int result = 0;

  while (c1 < end && result == 0) {
    result = *c1++ - *c2++;
  }
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *c1 = (unsigned char *)dest;
  const unsigned char *c2 = (const unsigned char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    *c1++ = *c2++;
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *p = str;
  while (n-- > 0) {
    *p++ = (unsigned char)c;
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *p = dest + s21_strlen(dest);
  while (*src != '\0' && n-- > 0) {
    *p++ = *src++;
  }
  *p = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  int flag = 1;
  while (*str && flag) {
    if (*str == c) {
      result = (char *)str;
      flag = 0;
    }
    str++;
  }
  if (c == '\0') {
    result = (char *)str;
  }
  return result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  int flag = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i] && !flag) {
      result = str1[i] - str2[i];
      flag = 1;
    }
    if (str1[i] == '\0' && str2[i] == '\0' && !flag) {
      result = 0;
    }
  }
  return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if ((int)n > 0) {
    for (s21_size_t i = 0; i < n && i < s21_strlen(src); i++) {
      dest[i] = src[i];
    }
    if (src[0] == '\0') {
      dest[0] = src[0];
    }
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t length = 0;
  int mfr = 0;
  while (length < s21_strlen(str1) && !mfr) {
    for (s21_size_t i = 0; i < s21_strlen(str2); i++) {
      if (str1[length] == str2[i]) mfr++;
    }
    if (!mfr) length++;
  }
  return length;
}

char *s21_strerror(int errnum) {
  char *err_array[] = s21_errors;
  char *error = s21_NULL;
  if (errnum >= ERR_FIRST && errnum <= ERR_LAST)
    error = (char *)err_array[errnum];
  else {
    static char unknown_error[500] = {0};
    s21_sprintf(unknown_error, "%s %d", err_array[ERR_LAST + 1], errnum);
    error = unknown_error;
  }
  return error;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  if (str) {
    while (str[length] != '\0') {
      length++;
    }
  }
  return length;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *find = s21_NULL;
  s21_size_t cr = 0;
  for (s21_size_t i = 0; i < s21_strlen(str2); i++) {
    char *temp_find = s21_strchr(str1, str2[i]);
    s21_size_t len = s21_strlen(temp_find);
    if (len > cr) {
      find = temp_find;
      cr = len;
    }
  }
  return find;
}

char *s21_strrchr(const char *str, int c) {
  s21_size_t len = s21_strlen(str);
  s21_size_t i = (len) ? len : 0, flag_find = 0, flag_end = 0;
  while (!flag_find && !flag_end) {
    flag_end = (!i) ? 1 : 0;
    flag_find = (str[i] == c) ? 1 : 0;
    i -= (!flag_end) ? 1 : 0;
  }
  int add = (!i) ? 0 : 1;
  const char *find = str;
  if (flag_find) {
    find = str + i + add;
  } else {
    find = s21_NULL;
  }
  return (char *)find;
}

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t len = s21_strlen(needle), pos_hays = 0, pos_need = 0;
  int flag_find = 0;
  for (s21_size_t i = 0; i < s21_strlen(haystack) && !flag_find && len; i++) {
    pos_hays = i, pos_need = 0;
    while (haystack[pos_hays] == needle[pos_need] && !flag_find) {
      pos_hays++, pos_need++;
      flag_find = (pos_need == len) ? 1 : 0;
    }
  }
  int state = flag_find || len == 0;
  const char *find = (state) ? haystack + pos_hays - len : s21_NULL;
  return (char *)find;
}

char *s21_strtok(char *str, const char *delim) {
  static char *rest_str = s21_NULL;
  char *ptr = s21_NULL;
  str = (str) ? str : (rest_str) ? rest_str : s21_NULL;
  if (str || rest_str) {
    while (*str != '\0' && s21_strchr(delim, *str)) {
      str++;
    }
    ptr = str;
    while (str != s21_NULL && *str != '\0' && !s21_strchr(delim, *str)) {
      str++;
    }
    if (str && *str != '\0') {
      rest_str = str + 1;
      *str = '\0';
    } else {
      rest_str = s21_NULL;
      ptr = (*ptr == '\0') ? s21_NULL : ptr;
    }
  }
  return ptr;
}

void *s21_to_upper(const char *str) {
  char *result = s21_NULL;
  int length = s21_strlen(str);
  if (str) {
    result = (char *)malloc((length + 1) * sizeof(char));
  }
  if (result) {
    s21_strncpy(result, str, length);
    for (char *i = result; *i; i++) {
      if (*i >= 'a' && *i <= 'z') {
        *i -= 32;
      }
    }
    result[length] = '\0';
  }
  return result;
}

void *s21_to_lower(const char *str) {
  char *result = s21_NULL;
  int length = s21_strlen(str);
  if (str) {
    result = (char *)malloc((length + 1) * sizeof(char));
  }
  if (result) {
    s21_strncpy(result, str, length);
    for (char *i = result; *i; i++) {
      if (*i >= 'A' && *i <= 'Z') {
        *i += 32;
      }
    }
    result[length] = '\0';
  }
  return result;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = s21_NULL;
  s21_size_t length = 0;
  if (str && src && start_index <= s21_strlen(src)) {
    length = s21_strlen(src) + s21_strlen(str);
    result = malloc(length + 1);
  }
  if (result) {
    s21_size_t i = 0, j = 0;
    for (; i < start_index; i++) result[i] = src[i];
    for (; i < s21_strlen(str) + start_index; i++, j++) result[i] = str[j];
    for (j = start_index; i < length; i++, j++) result[i] = src[j];
    result[length] = '\0';
  }
  return result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  const char *psrc = src;
  const char *rsrc = src;
  s21_size_t i = 0, j = s21_strlen(src), flag = 0;
  if (src && trim_chars) {
    while (s21_strchr(trim_chars, psrc[i]) && psrc[i] != '\0') {
      i++;
    }
    while (j > 0 && s21_strrchr(trim_chars, rsrc[j - 1]) && j > i) {
      j--;
    }
    flag = 1;
  }
  char *result = (flag) ? s21_getZeroArr(j - i + 1) : 0;
  s21_size_t idx = i, k = 0;
  if (result) {
    while (idx < j) {
      result[k++] = src[idx++];
    }
    result[k] = '\0';
  }
  return (void *)result;
}

int s21_isInt(char value) {
  return (value - '0' >= 0 && value - '0' <= 9) ? 1 : 0;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int count = 0;
  while (*format != '\0') {
    if (s21_checkSpec(*format)) {
      Flags flags = {0};
      int buff = 16;
      char *str_value = s21_getZeroArr(buff);
      format++;
      format += s21_strHandler(format, &flags, &args);
      (*format == 'n') ? s21_flagN(&args, count) : 0;
      str_value = s21_cHandler(str_value, &buff, *format, &args, &flags);
      count += s21_recordToStr(str + count, str_value, &flags);
      s21_freeStr(str_value);
      format++;
    } else {
      str[count++] = *format;
      format++;
    }
  }
  str[count] = '\0';
  va_end(args);
  return count;
}

int s21_checkSpec(char c) { return (c == '%') ? 1 : 0; }

int s21_strHandler(const char *frm, Flags *flags, va_list *args) {
  int i = 0;
  flags->precision = -1;
  const char *specifiers = "nXxeEGgiuedcsf.*%";
  while (!s21_isInt(frm[i]) && !s21_strchr(specifiers, frm[i])) {
    i++;
  }
  int flag_is_option = 1, j = 0;
  for (; j < i && flag_is_option; j++) {
    flag_is_option = s21_flagParse(frm[j], flags);
  }
  i += s21_getSpace(frm + i, &flags->space);

  if (frm[i] == '*') {
    flags->space = va_arg(*args, int);
    i++;
  }
  if (frm[i] == '.') {
    i++;
    if (s21_isInt(frm[i])) {
      flags->precision = 0;
      i += s21_getSpace(frm + i, &flags->precision);
    } else if (frm[i] == '*') {
      flags->precision = va_arg(*args, int);
      i++;
    } else {
      flags->precision = 0;
    }
  }
  i += s21_flagParse(frm[i], flags);
  return i;
}

int s21_getSpace(const char *format, int *space) {
  int count = 0, sign = 0;
  if (*format == '-') {
    sign++;
    format++;
    count++;
  }
  while (s21_isInt((char)*format)) {
    *space = *space * 10 + (int)*format - 48;
    format++;
    count++;
  }
  if (sign) {
    *space = -*space;
  }
  return count;
}

int s21_flagParse(char c, Flags *flags) {
  int flag = 0;
  const char *lenghts = "+-#0hlL ";
  if (s21_strchr(lenghts, c)) {
    flag++;
    (c == ' ') ? flags->invisible_plus = 1 : 0;
    (c == 'h') ? flags->h = 1 : 0;
    (c == 'l') ? flags->l = 1 : 0;
    (c == 'L') ? flags->L = 1 : 0;
    (c == '+')                    ? flags->plus = 1, flags->invisible_plus = 0,
                 flags->minus = 0 : 0;
    (c == '-' && !flags->plus) ? flags->minus = 1 : 0;
    (c == '0') ? flags->zero = 1 : 0;
    (c == '#') ? flags->sharp = 1 : 0;
  }
  return flag;
}

char *s21_cHandler(char *val, int *buff, char c, va_list *args, Flags *flags) {
  const char *specs_int = "idouxXp";
  const char *specs_float = "efgEFG";
  if (c == 'c' || c == '%') {
    val = s21_getFromChar(args, flags, val, c);
  } else if (s21_strchr(specs_int, c)) {
    flags->which_int = c;
    val = s21_getFromInt(args, flags, val, buff);
  } else if (s21_strchr(specs_float, c)) {
    flags->which_int = 'd';
    flags->which_float = c;
    val = s21_getFromFlt(args, flags, val, buff);
  } else if (c == 's') {
    val = s21_getFromStr(args, flags, val, buff);
  }
  return val;
}

void s21_changeSpace(int *space, int value_length) {
  if (abs(*space) <= value_length) {
    *space = 0;
  } else {
    *space += (*space > 0) ? -value_length : value_length;
  }
}

int s21_addSpace(char *str, Flags flags) {
  char c = ' ';
  if (flags.zero && flags.precision <= 0) {
    c = '0';
  }
  if (flags.space < 0) {
    flags.space = -flags.space;
  }
  for (int k = 0; k < flags.space; k++) {
    str[k] = c;
  }
  return flags.space;
}

char *s21_getFromChar(va_list *args, Flags *flags, char *str_value, char c) {
  char value;
  if (c == 'c') {
    value = (char)va_arg(*args, int);
  } else {
    value = '%';
  }
  if (value == 0) {
    flags->zerochar = 1;
  }
  str_value[0] = value;
  return str_value;
}

char *s21_getFromInt(va_list *args, Flags *flags, char *str_value, int *buff) {
  const char *unsign = "ouxX";
  int unsign_state = (s21_strchr(unsign, flags->which_int) != s21_NULL);
  long long int value;
  if (flags->which_int == 'p') {
    flags->which_int = 'x';
    flags->sharp = 1;
    value = va_arg(*args, long long int);
  } else if (flags->h) {
    if (unsign_state) {
      value = (unsigned short)va_arg(*args, unsigned int);
    } else {
      value = (short int)va_arg(*args, int);
    }
  } else if (flags->l) {
    if (unsign_state) {
      value = (unsigned long)va_arg(*args, unsigned long int);
    } else {
      value = (long int)va_arg(*args, long int);
    }
  } else {
    if (unsign_state) {
      value = (unsigned)va_arg(*args, unsigned int);
    } else {
      value = (int)va_arg(*args, int);
    }
  }
  flags->zerozero = (flags->precision == 0 && value == 0) ? 1 : 0;  // 0.0
  flags->precision = (flags->precision == -1) ? 0 : flags->precision;
  int new_buff = flags->precision + s21_intLength(value, flags->which_int) +
                 flags->sharp * 2 + 1;
  str_value = s21_reallocStr(str_value, buff, new_buff);
  s21_itoa(str_value, value, flags);
  return str_value;
}

char *checkNanInf(long double num, char *str_value, int *flag_ord_num) {
  if (num == s21_INF) {
    s21_strncpy(str_value, "inf", 3);
  } else if (num == s21_NINF) {
    s21_strncpy(str_value, "-inf", 4);
  } else if (isnan(num)) {
    s21_strncpy(str_value, "nan", 3);
  } else {
    *flag_ord_num = 1;
  }
  return str_value;
}

char *s21_getFromFlt(va_list *args, Flags *flags, char *str_value, int *buff) {
  long double val;
  if (flags->L) {
    val = va_arg(*args, long double);
  } else if (flags->l) {
    val = (double)va_arg(*args, double);
  } else {
    val = (float)va_arg(*args, double);
  }
  int flag_ord_num = 0;
  str_value = checkNanInf(val, str_value, &flag_ord_num);
  if (flag_ord_num) {
    char c = flags->which_float;
    flags->precision = (flags->precision < 0) ? 6 : flags->precision;
    const char *adds_f = "-+ .", *adds_e = "-+ .e-00";
    int add = (s21_strchr("eEgG", c)) ? s21_strlen(adds_e) : s21_strlen(adds_f);
    int new_buff = flags->precision + s21_intLength((int)val, c) + add;
    str_value = s21_reallocStr(str_value, buff, new_buff);
    (s21_strchr("gG", c)) ? s21_specG(str_value, val, flags)
                          : s21_ftoa(str_value, val, flags);
  }
  return str_value;
}

void s21_flagN(va_list *args, int count) {
  int *value = va_arg(*args, int *);
  *value = count;
}

char *s21_getFromStr(va_list *args, Flags *flags, char *str_value, int *buff) {
  char *value = va_arg(*args, char *);
  int len = s21_strlen(value), new_buff;
  if (flags->precision >= 0 && flags->precision < len) {
    new_buff = flags->precision;
  } else {
    new_buff = len + 1;
  }
  str_value = s21_reallocStr(str_value, buff, new_buff);
  s21_strncpy(str_value, value, new_buff);
  str_value[new_buff] = '\0';
  return str_value;
}

int s21_recordToStr(char *str, char *value, Flags *flags) {
  int i = 0, len = s21_strlen(value);
  len += flags->zerochar;  // char c = 0
  flags->space *= (flags->minus) ? -1 : 1;
  s21_changeSpace(&flags->space, len);
  i += (flags->space > 0) ? s21_addSpace(str + i, *flags) : 0;
  for (int j = i; j < i + len; j++) {
    str[j] = value[j - i];
  }
  i += len;
  i += (flags->space < 0) ? s21_addSpace(str + i, *flags) : 0;
  return i;
}

int s21_itoa(char *str, long long int num, Flags *flags) {
  const char xBase[] = "0123456789abcdef";
  const char XBase[] = "0123456789ABCDEF";
  const char oBase[] = "01234567";
  char c = flags->which_int;
  int i = 0;
  str = s21_itoaPreFlags(str, &num, &i, flags);
  int len = s21_intLength(num, c);
  if (flags->precision > len) {
    i += flags->precision - len;
    for (int k = i - 1; k > i - flags->precision + len - 1; k--) {
      str[k] = '0';
    }
  }
  i += len;
  for (int j = i - 1; !flags->zerozero && j > i - len - 1; j--) {
    if (c == 'x' || c == 'X') {
      str[j] = (c == 'X') ? XBase[num % 16] : xBase[num % 16];
      num /= 16;
    } else if (c == 'o') {
      str[j] = oBase[num % 8];
      num /= 8;
    } else {
      str[j] = (num % 10) + '0';
      num /= 10;
    }
  }
  return i;
}

char *s21_itoaPreFlags(char *str, long long int *num, int *i, Flags *flags) {
  const char digit8_16[] = "oxX";
  char c = flags->which_int;
  if (flags->sharp && s21_strchr(digit8_16, c)) {
    str[(*i)++] = '0';
    if (c == 'x') {
      str[(*i)++] = 'x';
    } else if (c == 'X') {
      str[(*i)++] = 'X';
    }
  }
  if (*num < 0) {
    *num = -*num;
    str[(*i)++] = '-';
    flags->plus = 0, flags->invisible_plus = 0;
  } else if (flags->plus && flags->which_int != 'u') {
    str[(*i)++] = '+';
    flags->plus = 0;
    flags->invisible_plus = 0;
  } else if (flags->invisible_plus) {
    str[(*i)++] = ' ';
    flags->invisible_plus = 0;
  }
  return str;
}

int s21_ftoa(char *str, long double num, Flags *flags) {
  int i = 0;
  char c = flags->which_float;
  if (!flags->precision && !flags->sharp) {
    float minus_check = num;
    num = (num > 0) ? (int)(num + 0.5) : (int)(num - 0.5);
    if (num == 0 && minus_check < 0) {
      str[i++] = '-';
    }
  }
  int is_exp = (s21_strchr("eE", c) && !flags->ftoa_g) ? 1 : 0;
  flags->exp_pow = (is_exp) ? s21_ftoaIntPartExp(&num) : 0;
  flags->g_pow = (flags->ftoa_g) ? s21_ftoaIntPartExp(&num) + 1 : 0;
  (flags->ftoa_g) ? num /= 10 : 0;
  str = s21_ftoaRecIntPart(str, num, &i, flags);
  if ((flags->precision || flags->sharp) && !(flags->ftoa_g && num == 0)) {
    str = s21_ftoaDecPart(str, num, &i, flags);
    if (is_exp) {
      str[i++] = (c == 'e') ? 'e' : 'E';
      str[i++] = (flags->exp_pow < 0) ? '-' : '+';
      flags->precision = 2;
      i += s21_itoa(str + i, abs(flags->exp_pow), flags);
    } else if (flags->ftoa_g) {
      while (str[i - 1] == '0' && i > flags->g_pow + 2) {
        str[--i] = '\0';
      }
    }
  }
  return i;
}

int s21_ftoaIntPartExp(long double *num) {
  int exp_pow = 0;
  if (*num > 0) {
    while (*num >= 10) {
      *num /= 10, exp_pow++;
    }
    while (*num < 1 && *num != 0) {
      *num *= 10, exp_pow--;
    }
  } else if (*num < 0) {
    while (*num <= -10) {
      *num /= 10, exp_pow++;
    }
    while (*num > -1) {
      *num *= 10, exp_pow--;
    }
  }
  return exp_pow;
}

char *s21_ftoaRecIntPart(char *str, long double num, int *i, Flags *flags) {
  int temp_precision = flags->precision;
  flags->precision = 0;
  long long int int_part = (long long int)num;
  (num < 0 && !int_part) ? str[(*i)++] = '-', flags->plus = 0,
                           flags->invisible_plus = 0 : 0;
  *i += s21_itoa(str + *i, int_part, flags);
  flags->precision = temp_precision;
  return str;
}

char *s21_ftoaDecPart(char *str, long double num, int *i, Flags *flags) {
  str[(*i)++] = '.';
  long double dec_part = num - (long long int)num;
  int cr = 0, flag_not_significant = 0, origin_precision = flags->precision;
  dec_part = (dec_part > 0) ? dec_part : -dec_part;
  while (flags->precision > 0) {
    cr++;
    int temp_precision = flags->precision - 1;
    flags->precision = 1;
    dec_part *= 10;
    int int_part = (int)dec_part;
    if (int_part) {
      cr = (flag_not_significant) ? cr : 0;
      flag_not_significant = 1;
    } else if (flags->ftoa_g && int_part == 0 && !flag_not_significant) {
      temp_precision++;
    } else if (flags->ftoa_g && flag_not_significant &&
               cr >= origin_precision) {
      temp_precision = 0;
    }
    if (!temp_precision) {
      int_part += (dec_part - int_part >= 0.5) ? 1 : 0;
      if (int_part == 10) {
        str = s21_ftoaLastDec(str, i, flags);
        int_part = 0;
      }
    }
    dec_part -= int_part;
    *i += s21_itoa(str + *i, int_part, flags);
    flags->precision = temp_precision;
  }
  return str;
}

char *s21_ftoaLastDec(char *str, int *i, Flags *flags) {
  int temp_i = *i, flag_not_changed = 1;
  while (str[--(*i)] == '9' || (str[*i] == '.' && flag_not_changed)) {
    if (str[*i] == '.') {
      int before_dot_pos = *i - 1;
      flags->exp_pow += (str[before_dot_pos] == '9') ? 1 : 0;
      str[before_dot_pos] += (str[before_dot_pos] == '9') ? -8 : 1;
      flag_not_changed--;
    } else {
      str[*i] = (flags->ftoa_g) ? '\0' : '0';
    }
  }
  if (s21_isInt(str[*i]) && flag_not_changed) {
    str[*i] += 1;
  }
  *i = temp_i;
  if (flags->g_pow && str[0] != '0') {
    str[2] = str[0];
    str[0] = '0';
    flags->g_pow += 1;
  }
  return str;
}

int s21_specG(char *str, long double num, Flags *flags) {
  int i = 0, temp_precision = flags->precision;
  flags->ftoa_g = 1;
  flags->which_float = (flags->which_float == 'g') ? 'e' : 'E';
  i += s21_ftoa(str, num, flags);
  flags->precision = temp_precision;
  if (flags->g_pow >= -3 && flags->g_pow - 1 < flags->precision) {
    flags->which_float = 'f';
  }
  str = s21_ftoaRewriteG(str, flags);
  return i;
}

char *s21_ftoaRewriteG(char *str, Flags *flags) {
  if (flags->which_float == 'f') {
    s21_rewriteSpecF(str, flags);
  } else {
    int null_dot = 2;
    int i = (str[0] == '-') ? 1 : 0;
    int null_cond = (str[i + null_dot] == 0);
    str[i] = (null_cond) ? '1' : str[i + null_dot];
    i += 2;
    for (; str[i] != '\0'; i++) {
      str[i] = str[i + 1];
    }
    int flag_null_end = 1;
    for (int j = i - 2; j > 0 && flag_null_end; j--, i--) {
      if (str[j] == '0' || str[j] == '.') {
        str[j] = '\0';
      } else {
        flag_null_end = 0;
      }
    }
    if (flags->g_pow < 0) {
      i -= 1;
    }
    str[i++] = (flags->which_float == 'e') ? 'e' : 'E';
    (flags->ftoa_g && flags->g_pow >= 0) ? str[i++] = '+' : 0;
    flags->precision = 2;
    int pow = (null_cond) ? flags->g_pow : flags->g_pow - 1;
    i += s21_itoa(str + i, pow, flags);
  }
  return str;
}

char *s21_rewriteSpecF(char *str, Flags *flags) {
  int dig_pos = 0, null_dot = 2, first_dig_after_dot;
  while (!s21_isInt(str[dig_pos])) {
    dig_pos++;
  }
  if (flags->g_pow > 0 && s21_strncmp("0", str, s21_strlen(str))) {
    first_dig_after_dot = null_dot + flags->g_pow + dig_pos;
    for (int i = dig_pos + null_dot; i < first_dig_after_dot; i++) {
      str[i - null_dot] = str[i];
    }
    if (str[first_dig_after_dot] != '\0') {
      str[flags->g_pow + dig_pos] = '.';
      for (int i = first_dig_after_dot - 1; str[i] != '\0'; i++) {
        str[i] = str[i + 1];
      }
    } else {
      for (int i = flags->g_pow + dig_pos; i < first_dig_after_dot; i++) {
        str[i] = '\0';
      }
    }
  } else {
    flags->g_pow *= -1;
    first_dig_after_dot = dig_pos + null_dot;
    int end_nulls = first_dig_after_dot + flags->g_pow;
    int old_len = s21_strlen(str);
    for (int i = old_len + flags->g_pow - 1; i > end_nulls - 1; i--) {
      str[i] = str[i - flags->g_pow];
    }
    for (int i = end_nulls - 1; i > first_dig_after_dot - 1; i--) {
      str[i] = '0';
    }
  }
  return str;
}

int s21_intLength(long long int value, char c) {
  int length = 0;
  if (value <= 0) {
    value = -value;
    length++;
  }
  while (value > 0) {
    value /= (c == 'x' || c == 'X') ? 16 : (c == 'o') ? 8 : 10;
    length++;
  }
  return length;
}

char *s21_reallocStr(char *str, int *buff, int new_buff) {
  if (*buff < new_buff) {
    *buff = new_buff;
    char *temp = realloc(str, *buff * sizeof(char));
    if (temp) {
      str = temp;
      s21_memset(str, '\0', *buff);
    }
  }
  return str;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  Tptrs ptr = {.str = (char *)str, .frm = (char *)format};
  int count = 0, flag_err = 0, flag_need_check = 0;
  s21_size_t sum_rec = 0;
  while (ptr.frm[0] != '\0' && !flag_err) {
    Tsscanf sscanfs = {0};
    s21_size_t idx_str = 0, idx_frm = 0, trim_shift = s21_leftTrim(ptr.str);
    ptr.str += trim_shift;
    ptr.frm += s21_leftTrim(ptr.frm), ptr.lstr = s21_strlen(ptr.str);
    flag_need_check = s21_readSpecPtrChange(ptr.frm, &sscanfs, &idx_frm);
    ptr.frm += idx_frm;
    if (ptr.lstr) {
      if (sscanfs.is_char) {
        idx_str += s21_recordChar(sscanfs, &ptr, args);
      } else if (sscanfs.is_int) {
        idx_str += s21_recordInt(sscanfs, &ptr, args);
      } else if (sscanfs.is_float) {
        idx_str += s21_recordFloat(sscanfs, &ptr, args);
      } else if (sscanfs.is_str) {
        idx_str += s21_recordStr(sscanfs, &ptr, args);
      }
    }
    if (sscanfs.is_count) {
      s21_recSum(sum_rec, sscanfs, args);
    }
    sum_rec += idx_str + trim_shift;
    (idx_str) ? ptr.str += idx_str, count++ : 0;
    if (flag_need_check) {
      flag_err = s21_checkRest(&ptr);
    }
    count = (!sum_rec) ? -1 : count;
  }
  va_end(args);
  return count;
}

int s21_readSpecPtrChange(char *frm, Tsscanf *sscanfs, s21_size_t *idx) {
  const char delims[] = " %\t\n\0";
  s21_size_t j = 0;
  int flag_need_check = 0, all_find = 0, sucess_rec = 1;
  if (frm[j++] == '%') {
    char *wide = s21_getZeroArr(s21_strlen(frm));
    char c = frm[j];
    while (!s21_strchr(delims, c) && !all_find) {
      sucess_rec = 1;
      all_find = s21_checkOpt(sscanfs, wide, c, &sucess_rec);
      c = frm[++j];
    }
    *idx = (sucess_rec) ? j : j - 1;
    s21_size_t n = 0;
    sscanfs->opt_wide = (s21_strlen(wide)) ? s21_atoiPlus(wide, 'd', &n) : 0;
    s21_freeStr(wide);
  } else {
    flag_need_check = 1;
  }
  flag_need_check = (*idx == 1) ? 1 : flag_need_check;
  return flag_need_check;
}

int s21_checkOpt(Tsscanf *sscanfs, char *wide, char c, int *rec) {
  const char *options = "*hlL";
  const char *specs_all = "cidouxXefgEFGsp%n";
  const char *specs_int = "idouxX";
  const char *specs_float = "efgEFG";
  const char *specs_str_ptr = "sp";
  int flag = 1;
  s21_size_t idx_wide = 0;
  if (s21_isInt(c) && !(sscanfs->option_on || sscanfs->spec_on)) {
    wide[idx_wide++] = c;
  } else if (s21_strchr(options, c) && !sscanfs->option_on) {
    sscanfs->option_on = 1;
    sscanfs->opt_astx = (c == '*') ? 1 : 0;
    sscanfs->opt_short = (c == 'h') ? 1 : 0;
    sscanfs->opt_long = (c == 'l') ? 1 : 0;
    sscanfs->opt_dlong = (c == 'L') ? 1 : 0;
  } else if (s21_strchr(specs_all, c) && !sscanfs->spec_on) {
    sscanfs->spec_on = 1;
    sscanfs->is_char = (c == 'c') ? flag--, 1 : 0;
    sscanfs->is_count = (flag && c == 'n') ? flag--, 1 : 0;
    sscanfs->is_str = (flag && s21_strchr(specs_str_ptr, c)) ? flag--, 1 : 0;
    sscanfs->is_float = (flag && s21_strchr(specs_float, c)) ? flag--, 1 : 0;
    if (flag && s21_strchr(specs_int, c)) {
      flag--;
      sscanfs->is_int = 1;
      sscanfs->which_int = c;
    }
  } else {
    *rec = 0;
  }
  return (*rec == 0) ? 1 : sscanfs->option_on && sscanfs->spec_on;
}

s21_size_t s21_recordChar(Tsscanf sscanfs, Tptrs *ptr, va_list args) {
  if (!sscanfs.opt_astx) {
    char *value = va_arg(args, char *);
    *value = (sscanfs.opt_long) ? ptr->str[0] : ptr->str[0];
  }
  return 1;
  // на оригинале lc не работает, изменить если сделаем lc
}

s21_size_t s21_recordInt(Tsscanf sscanfs, Tptrs *ptr, va_list args) {
  s21_size_t lim = sscanfs.opt_wide, idx = 0;
  long long int value = 0, size = (lim && lim < ptr->lstr) ? lim : ptr->lstr;
  char digs[size + 1];
  s21_strncpy(digs, ptr->str, size);
  digs[size] = '\0';
  value = s21_atoiPlus(digs, sscanfs.which_int, &idx);
  if (!sscanfs.opt_astx) {
    const char *specs_int = "id";
    int isnt_unsign = (s21_strchr(specs_int, sscanfs.which_int) != s21_NULL);
    if (sscanfs.opt_long) {
      if (isnt_unsign) {
        long int *temp = va_arg(args, long int *);
        *temp = (long int)value;
      } else {
        unsigned long int *temp = va_arg(args, unsigned long int *);
        *temp = (unsigned long int)value;
      }
    } else if (sscanfs.opt_short) {
      if (isnt_unsign) {
        short int *temp = va_arg(args, short int *);
        *temp = (short int)value;
      } else {
        short unsigned int *temp = va_arg(args, short unsigned int *);
        *temp = (short unsigned int)value;
      }
    } else {
      if (isnt_unsign) {
        int *temp = va_arg(args, int *);
        *temp = (int)value;
      } else {
        unsigned int *temp = va_arg(args, unsigned int *);
        *temp = (unsigned int)value;
      }
    }
  }
  return idx;
}

s21_size_t s21_recordFloat(Tsscanf sscanfs, Tptrs *ptr, va_list args) {
  s21_size_t lim = sscanfs.opt_wide;
  s21_size_t idx = 0, size = (lim && lim < ptr->lstr) ? lim : ptr->lstr;
  long double value = 0;
  char digs[size + 1];
  s21_strncpy(digs, ptr->str, size);
  digs[size] = '\0';
  value = s21_atofPlus(digs, &idx);
  if (!sscanfs.opt_astx) {
    if (sscanfs.opt_dlong) {
      long double *temp = va_arg(args, long double *);
      *temp = value;
    } else if (sscanfs.opt_long) {
      double *temp = va_arg(args, double *);
      *temp = (double)value;
    } else {
      float *temp = va_arg(args, float *);
      *temp = (float)value;
    }
  }
  return idx;
}

s21_size_t s21_recordStr(Tsscanf sscanfs, Tptrs *ptr, va_list args) {
  s21_size_t lim = sscanfs.opt_wide;
  s21_size_t idx = 0, size = (lim && lim < ptr->lstr) ? lim : ptr->lstr;
  char value[size + 1];
  while (!s21_strchr(" \t\n", ptr->str[idx]) && idx < size) {
    value[idx] = ptr->str[idx];
    idx++;
  }
  value[idx] = '\0';
  if (!sscanfs.opt_astx) {
    if (sscanfs.str_or_ptr == 's') {
      char *temp = va_arg(args, char *);
      s21_strncpy(temp, value, idx + 1);
    } else {
      void *temp = va_arg(args, void *);
      s21_strncpy(temp, value, idx + 1);
    }
  }
  return idx;
}

void s21_recSum(s21_size_t sum, Tsscanf sscanfs, va_list args) {
  if (!sscanfs.opt_astx) {
    int *value = va_arg(args, int *);
    *value = (int)sum;
  }
}

int s21_checkRest(Tptrs *ptr) {
  int flag_err = 0;
  const char delims[] = " %\t\n\0";
  s21_size_t idx = 0;
  while (!s21_strchr(delims, ptr->frm[idx]) && !flag_err) {
    if (ptr->frm[idx] == ptr->str[idx]) {
      idx++;
    } else {
      flag_err = 1;
    }
  }
  int percent_percent_condition = (!idx && ptr->frm[0] == '%');
  (percent_percent_condition) ? idx++ : 0;
  ptr->str += idx;
  ptr->frm += idx;
  return flag_err;
}

long long int s21_atoiPlus(char *str, char which_int, s21_size_t *idx) {
  long long int num = 0, factor = 1;
  int minus = (str[0] == '-') ? 1 : 0, oct = 0, hex = 0;
  s21_size_t i = (minus) ? 1 : 0, len = s21_strlen(str);
  const char *specs_int = "ioxX";
  if (s21_strchr(specs_int, which_int)) {
    oct = (str[i] == '0') ? 1 : 0;
    hex = (oct && (str[i + 1] == 'x' || str[i + 1] == 'X')) ? 1 : 0;
  }
  i += (hex) ? 2 : (oct) ? 1 : 0;
  const char *specs_hex = "xX", *hex_alpha = "abcdefABCDEF";
  int hex_state = (hex || s21_strchr(specs_hex, which_int)), is_num = 1;
  while (i < len && is_num) {
    if (!s21_isInt(str[i])) {
      is_num = (hex_state && s21_strchr(hex_alpha, str[i])) ? i++, 1 : 0;
    } else {
      i++;
    }
  }
  *idx = i;
  s21_size_t end_cycle = minus + hex + oct;
  while (len && i > end_cycle) {
    char c = str[--i];
    c -= (c >= 'a') ? 'a' - '0' - 10 : (c >= 'A') ? 'A' - '0' - 10 : 0;
    num += (c - '0') * factor;
    factor *= (hex_state) ? 16 : (oct || which_int == 'o') ? 8 : 10;
  }
  return (!minus) ? num : -num;
}

long double s21_atofPlus(char *str, s21_size_t *idx) {
  long double num = 0, factor = 1;
  int minus = (str[0] == '-') ? 1 : 0;
  s21_size_t i = (minus) ? 1 : 0, len = s21_strlen(str), dec_pos = 0;
  while (i < len && s21_isInt(str[i])) {
    i++;
  }
  s21_size_t null_pos = i, end_cycle = minus;
  while (i > end_cycle) {
    int base = (str[--i] - '0');
    if (base) {
      num += base * factor;
      factor *= 10;
    }
  }
  i = null_pos + 1;
  if (s21_strchr(".e", str[null_pos])) {
    dec_pos = null_pos;
    if (str[null_pos] == '.') {
      dec_pos++;
      while (i < len && s21_isInt(str[i])) {
        i++;
      }
      factor = 10;
      while (dec_pos < i) {
        char c = str[dec_pos++];
        num += (long double)(c - '0') / factor;
        factor *= 10;
      }
    }
    if (str[dec_pos++] == 'e') {
      s21_size_t len_e = 1, exp_len = 0;
      long int exp = s21_atoiPlus(str + dec_pos, 'd', &exp_len);
      num = (num) ? num * pow(10, exp) : num;
      i += exp_len + len_e;
    }
    *idx = i;
  }
  return (!minus) ? num : -num;
}

s21_size_t s21_leftTrim(char *str) {
  const char delims[] = " \t\n";
  s21_size_t i = 0;
  while (s21_strchr(delims, str[i]) && str[i] != '\0') {
    i += 1;
  }
  return i;
}

char *s21_getZeroArr(int len) {
  char *rest = malloc(len * sizeof(char));
  s21_memset(rest, '\0', len);
  return rest;
}

void s21_freeStr(char *str) {
  if (str) {
    free(str);
  }
}
