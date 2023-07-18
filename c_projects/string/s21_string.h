#ifndef S21_STRING_H
#define S21_STRING_H

#define s21_NULL ((void *)0)
#define s21_INF 1.0 / 0.0
#define s21_NINF -1.0 / 0.0

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

typedef long unsigned s21_size_t;
typedef unsigned int u_int32_t;
typedef int wchar_t;
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strchr(const char *str, int c);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

typedef struct {
  int space;
  int precision;
  int exp_pow;
  int g_pow;
  unsigned int h : 1;
  unsigned int l : 1;
  unsigned int L : 1;
  unsigned int plus : 1;
  unsigned int minus : 1;
  unsigned int invisible_plus : 1;
  unsigned int zero : 1;
  unsigned int zerozero : 1;
  unsigned int zerochar : 1;
  unsigned int sharp : 1;
  unsigned int ftoa_g : 1;
  char which_int;
  char which_float;

} Flags;

typedef enum { int_d_i, int_x, int_X, int_o } Tints;

int s21_sprintf(char *str, const char *format, ...);
int s21_checkSpec(char c);
int s21_strHandler(const char *format, Flags *flags, va_list *args);
int s21_getSpace(const char *format, int *space);

int s21_flagParse(char c, Flags *flags);
char *s21_cHandler(char *val, int *buff, char c, va_list *args, Flags *flags);
void s21_changeSpace(int *space, int value_length);
int s21_addSpace(char *str, Flags flags);
char *s21_getFromChar(va_list *args, Flags *flags, char *str_value, char c);
char *s21_getFromInt(va_list *args, Flags *flags, char *str_value, int *buff);
char *checkNanInf(long double num, char *str_value, int *flag_ord_num);
char *s21_getFromFlt(va_list *args, Flags *flags, char *str, int *count);
char *s21_getFromStr(va_list *args, Flags *flags, char *str, int *count);
void s21_flagN(va_list *args, int count);

int s21_recordToStr(char *str, char *value, Flags *flags);

int s21_isInt(char value);
int s21_itoa(char *str, long long int num, Flags *flags);
char *s21_itoaPreFlags(char *str, long long int *num, int *i, Flags *flags);
int s21_ftoa(char *str, long double num, Flags *flags);
int s21_ftoaIntPartExp(long double *num);
char *s21_ftoaRecIntPart(char *str, long double num, int *i, Flags *flags);
char *s21_ftoaDecPart(char *str, long double num, int *i, Flags *flags);
char *s21_ftoaLastDec(char *str, int *i, Flags *flags);
int s21_specG(char *str, long double num, Flags *flags);
char *s21_ftoaRewriteG(char *str, Flags *flags);
char *s21_rewriteSpecF(char *str, Flags *flags);

int s21_intLength(long long int value, char c);
char *s21_reallocStr(char *str, int *buff, int new_buff);

typedef struct {
  s21_size_t opt_wide;
  unsigned int opt_astx : 1;
  unsigned int opt_short : 1;
  unsigned int opt_long : 1;
  unsigned int opt_dlong : 1;
  unsigned int option_on : 1;
  char which_int;
  char str_or_ptr;

  unsigned int is_char : 1;
  unsigned int is_count : 1;
  unsigned int is_int : 1;
  unsigned int is_float : 1;
  unsigned int is_str : 1;
  unsigned int spec_on : 1;
} Tsscanf;

typedef struct {
  char *str;
  s21_size_t lstr;

  char *frm;
  s21_size_t lfrm;
} Tptrs;

int s21_sscanf(const char *str, const char *format, ...);
int s21_readSpecPtrChange(char *frm, Tsscanf *sscanfs, s21_size_t *idx);
int s21_checkOpt(Tsscanf *sscanfs, char *wide, char c, int *rec);
int s21_checkRest(Tptrs *toks);
s21_size_t s21_recordInt(Tsscanf sscanfs, Tptrs *toks, va_list args);
s21_size_t s21_recordChar(Tsscanf sscanfs, Tptrs *toks, va_list args);
s21_size_t s21_recordFloat(Tsscanf sscanfs, Tptrs *toks, va_list args);
s21_size_t s21_recordStr(Tsscanf sscanfs, Tptrs *toks, va_list args);

void s21_recSum(s21_size_t sum, Tsscanf sscanfs, va_list args);

long long int s21_atoiPlus(char *str, char which_int, s21_size_t *idx);
long double s21_atofPlus(char *str, s21_size_t *idx);

s21_size_t s21_leftTrim(char *str);
char *s21_getZeroArr(int len);
void s21_freeStr(char *str);

#endif
