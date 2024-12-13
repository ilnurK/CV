/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "tests.check" instead.
 */

#include <check.h>

#line 1 "tests.check"
#include "s21_string.h"
#include <string.h>
#include <stdio.h>

START_TEST(one)
{
#line 6
  char str[] = "There is many a slip between the cup and the lip.";
  for (size_t i = 0; i <= strlen(str) + 10; i++) {
    ck_assert_ptr_eq(s21_memchr(str, 't', i), memchr(str, 't', i));
  }
  ck_assert_ptr_eq(s21_memchr("\n", '\0', 3), memchr("\n", '\0', 3));
  ck_assert_ptr_eq(s21_memchr("\0", '\0', 3), memchr("\0", '\0', 3));
  ck_assert_ptr_eq(s21_memchr("345678", '\0', 6), memchr("345678", '\0', 6));
  ck_assert_ptr_eq(s21_memchr("\n", '\\', 3), memchr("\n", '\\', 3));
  ck_assert_ptr_eq(s21_memchr("98765432", '4', 8), memchr("98765432", '4', 8));
  ck_assert_ptr_eq(s21_memchr("98765432", '4', 3), memchr("98765432", '4', 3));
  ck_assert_ptr_eq(s21_memchr("98765432", 'a', 8), memchr("98765432", 'a', 8));
  ck_assert_ptr_eq(s21_memchr("abc", 'd', 10), memchr("abc", 'd', 10));
  ck_assert_ptr_eq(s21_memchr("abc", 'a', 0), memchr("abc", 'a', 0));  

}
END_TEST

START_TEST(two)
{
#line 21
  char str1[] = "Two heads are better than one.";
  char str2[] = "Two heads are better than three.";
  ck_assert_int_eq(s21_memcmp(str1, str2, 10), memcmp(str1, str2, 10));
  ck_assert_int_eq(s21_memcmp(str1, str2, 30), memcmp(str1, str2, 30));
  ck_assert_int_eq(s21_memcmp(str1, "1234o567", 10), memcmp(str1, "1234o567", 10));
  ck_assert_int_eq(s21_memcmp("", "", 3), memcmp("", "", 3));
  ck_assert_int_eq(s21_memcmp("1234567", "1234567", 7), memcmp("1234567", "1234567", 7));

}
END_TEST

START_TEST(three)
{
#line 30
  char src[] = "No pain, no gain.";
  char src1[] = "!@#$%^&*I(O)_+=-±";
  for (s21_size_t i = 0; i <= strlen(src); i++) {
    char dest1[] = "Two heads are better than one.", dest2[] = "Two heads are better than one.";
    char dest3[100] = {0}, dest4[100] = {0};
    ck_assert_str_eq(s21_memcpy(dest1, src, i), memcpy(dest2, src, i));
    ck_assert_str_eq(s21_memcpy(dest3, src1, i), memcpy(dest4, src1, i));
  }
  ck_assert_str_eq(s21_memcpy("", "abc", 0), memcpy("", "abc", 0));


}
END_TEST

START_TEST(four)
{
#line 42
  char str1[] = "1234357890";
  char str2[] = "Hello";
  for (s21_size_t i = 0; i <= strlen(str1); i++) {
    ck_assert_str_eq(s21_memset(str1, '1', i), memset(str1, '1', i));
  }
  ck_assert_str_eq(s21_memset(str1, 'd', 10), memset(str1, 'd', 10));
  ck_assert_str_eq(s21_memset(str1, '/', 8), memset(str1, '/', 8));
  // ck_assert_str_eq(s21_memset(str1, '8', 0), memset(str1, '8', 0));
  ck_assert_str_eq(s21_memset(str1, '0', 2), memset(str1, '0', 2));
  ck_assert_str_eq(s21_memset(str2, 0, 3), memset(str2, 0, 3));
  ck_assert_str_eq(s21_memset(str2, ' ', 3), memset(str2, ' ', 3));

}
END_TEST

START_TEST(five)
{
#line 55
  char src[6] = "abc";
  char src1[] = "";
  char dest[10] = "7";
  char dest1[10] = "7";
  char dest2[10] = "";
  char dest3[10] = "";
  ck_assert_str_eq(s21_strncat(dest, src1, 1), strncat(dest1, src1, 1));
  ck_assert_str_eq(s21_strncat(dest, src, 2), strncat(dest1, src, 2));
  ck_assert_str_eq(s21_strncat(dest, src, 6), strncat(dest1, src, 6));
  ck_assert_str_eq(s21_strncat(dest2, src1, 6), strncat(dest3, src1, 6));

}
END_TEST

START_TEST(six)
{
#line 67
  char str1[] = "Every dog has his day.";
  char str2[] = "";
  ck_assert_pstr_eq(s21_strchr(str1, 'h'), strchr(str1, 'h'));
  ck_assert_pstr_eq(s21_strchr(str1, '0'), strchr(str1, '0'));
  ck_assert_pstr_eq(s21_strchr(str1, '.'), strchr(str1, '.'));
  ck_assert_pstr_eq(s21_strchr(str1, 'E'), strchr(str1, 'E'));
  ck_assert_pstr_eq(s21_strchr(str2, '?'), strchr(str2, '?'));
  ck_assert_pstr_eq(s21_strchr(str2, '\0'), strchr(str2, '\0'));

}
END_TEST

START_TEST(seven)
{
#line 77
  char str1[] = "Deeds, not words.";
  char str2[] = "Deeds, not words";
  char str3[] = "1234567890123456";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5), strncmp(str1, str2, 5));
  ck_assert_int_eq(s21_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
  ck_assert_int_eq(s21_strncmp(str1, str2, 17), strncmp(str1, str2, 17));
  ck_assert_int_eq(s21_strncmp(str2, str3, 16), strncmp(str2, str3, 16));
  ck_assert_int_eq(s21_strncmp("", str2, 8), strncmp("", str2, 8));
  ck_assert_int_eq(s21_strncmp(str1, "", 3), strncmp(str1, "", 3));
  ck_assert_int_eq(s21_strncmp("", "", 1), strncmp("", "", 1));

}
END_TEST

START_TEST(eight)
{
#line 89
  char dest1[100] = "Where there's a will,";
  char dest2[100] = "Where there's a will,";
  char src1[] = " there's a way.";
  for (size_t i = 0; i <= strlen(src1); i++) {
    ck_assert_pstr_eq(strncpy(dest1, src1, i), s21_strncpy(dest2, src1, i));
  }
  char dest3[50] = "Where there's a will, there's a way.";
  char dest4[50] = "Where there's a will, there's a way.";
  char src2[] = "\0";
  ck_assert_pstr_eq(strncpy(dest3, src2, 1), s21_strncpy(dest4, src2, 1));
  char dest5[50] = "";
  char dest6[50] = "";
  char src3[] = "Where there's a will, there's a way.";
  ck_assert_pstr_eq(strncpy(dest5, src3, strlen(src3)), s21_strncpy(dest6, src3, strlen(src3)));
  char dest7[50] = "";
  char dest8[50] = "";
  char src4[] = "Where there's a will, there's a way.";
  ck_assert_pstr_eq(strncpy(dest7, src4, strlen(src4) + 10), s21_strncpy(dest8, src4, strlen(src4) + 10));
  char dest9[50] = "012345";
  char dest10[50] = "012345";
  char src5[] = "-+=&^%$#@!&*()_";
  ck_assert_pstr_eq(strncpy(dest9, src5, strlen(src5)), s21_strncpy(dest10, src5, strlen(src5)));

}
END_TEST

START_TEST(nine)
{
#line 113
  char str1[] = "He laughs best who laughs last.";
  char str2[] = "laughs";
  char str3[] = "83948574";
  char str4[] = "574";
  char str5[] = "839";
  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
  ck_assert_int_eq(strcspn(str1, str1), s21_strcspn(str1, str1));
  ck_assert_int_eq(strcspn("", str2), s21_strcspn("", str2));
  ck_assert_int_eq(strcspn(str1, ""), s21_strcspn(str1, ""));
  ck_assert_int_eq(strcspn("", ""), s21_strcspn("", ""));
  ck_assert_int_eq(strcspn(str3, str4), s21_strcspn(str3, str4));
  ck_assert_int_eq(strcspn(str4, str3), s21_strcspn(str4, str3));
  ck_assert_int_eq(strcspn(str1, str4), s21_strcspn(str1, str4));
  ck_assert_int_eq(strcspn(str3, str5), s21_strcspn(str3, str5));
  ck_assert_int_eq(strcspn(str3, str3), s21_strcspn(str3, str3));

}
END_TEST

START_TEST(ten)
{
#line 130
  for (int i = 0; i < 135; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
  ck_assert_str_eq(strerror(-1), s21_strerror(-1));

}
END_TEST

START_TEST(eleven)
{
#line 136
  ck_assert_int_eq(s21_strlen("Hello there"), strlen("Hello there"));
  ck_assert_int_eq(s21_strlen(""), strlen(""));
  ck_assert_int_eq(s21_strlen("\n"), strlen("\n"));
  ck_assert_int_eq(s21_strlen("\0"), strlen("\0"));
  ck_assert_int_eq(s21_strlen("Still waters\0 run deep"), strlen("Still waters\0 run deep"));

}
END_TEST

START_TEST(twelve)
{
#line 143
  ck_assert_pstr_eq(s21_strpbrk("Hello there", "there"), strpbrk("Hello there", "there"));
  ck_assert_pstr_eq(s21_strpbrk("\n", "\n"), strpbrk("\n", "\n"));
  ck_assert_pstr_eq(s21_strpbrk("\0", "\0"), strpbrk("\0", "\0"));
  ck_assert_pstr_eq(s21_strpbrk("dg", "askdljglag"), strpbrk("dg", "askdljglag"));
  ck_assert_pstr_eq(s21_strpbrk("", "kljhgf"), strpbrk("", "kljhgf"));

}
END_TEST

START_TEST(thirteen)
{
#line 150
  char str[] = "Time and tide wait for no man";
  ck_assert_pstr_eq(s21_strrchr(str, 'a'), strrchr(str, 'a'));
  ck_assert_pstr_eq(s21_strrchr("\n", '\n'), strrchr("\n", '\n'));
  ck_assert_pstr_eq(s21_strrchr("\0", '\0'), strrchr("\0", '\0'));
  ck_assert_pstr_eq(s21_strrchr("ddddddddgd", 'g'), strrchr("ddddddddgd", 'g'));
  ck_assert_pstr_eq(s21_strrchr(str, 'g'), strrchr(str, 'g'));

}
END_TEST

START_TEST(fourteen)
{
#line 158
  char str[] = "If 'ifs' and 'ans' were pots and pans";
  ck_assert_pstr_eq(s21_strstr(str, "Galya, u nas otmena!"), strstr(str, "Galya, u nas otmena!"));
  ck_assert_pstr_eq(s21_strstr(str, str), strstr(str, str));
  ck_assert_pstr_eq(s21_strstr("", str), strstr("", str));
  ck_assert_pstr_eq(s21_strstr(str, ""), strstr(str, ""));
  ck_assert_pstr_eq(s21_strstr(str, "and pans"), strstr(str, "and pans"));
  ck_assert_pstr_eq(s21_strstr(str, "and"), strstr(str, "and"));
  ck_assert_pstr_eq(s21_strstr("8976543", "654"), strstr("8976543", "654"));

}
END_TEST

START_TEST(fifteen)
{
#line 168
  char str1[] = "Many a good .cow has a bad calf";
  char str2[] = "Many a good .cow has a bad calf";
  char *token1, *token2;
  token1 = s21_strtok(str1, " .a");
  token2 = strtok(str2, " .a");
  ck_assert_pstr_eq(token1, token2);
  while (token1 != NULL && token2 != NULL) {
    token1 = s21_strtok(NULL, " .a");
    token2 = strtok(NULL, " .a");
    ck_assert_pstr_eq(token1, token2);
  }
  // ck_assert_pstr_eq(s21_strtok("", ""), strtok("", ""));
  char str3[] = "Hope for the best but prepare for the worst";
  char str4[] = "Hope for the best but prepare for the worst";
  ck_assert_pstr_eq(strtok(str3, "\0"), s21_strtok(str4, "\0"));
  char str5[] = "\0No pain, no gain";
  char str6[] = "\0No pain, no gain";
  ck_assert_pstr_eq(strtok(str5, "\0"), s21_strtok(str6, "\0"));
  char *str7 = s21_NULL;
  char *str8 = s21_NULL;
  ck_assert_pstr_eq(strtok(str7, ""), s21_strtok(str8, ""));
  ck_assert_str_eq(s21_strtok("t", "gdgsd"), strtok("t", "gdgsd"));
  ck_assert_pstr_eq(s21_strtok("", "a"), strtok("", "a"));
  // ck_assert_pstr_eq(s21_strtok("When pigs fly", "When pigs fly"), strtok("When pigs fly", "When pigs fly"));  

}
END_TEST

START_TEST(to_upper)
{
#line 194
  ck_assert_str_eq(s21_to_upper("hello School21"), "HELLO SCHOOL21");
  ck_assert_str_eq(s21_to_upper("HeLlO"), "HELLO");
  ck_assert_str_eq(s21_to_upper(""), "");
  ck_assert_str_eq(s21_to_upper("123123"), "123123");
  ck_assert_str_eq(s21_to_upper("HELLO"), "HELLO");
  ck_assert_str_eq(s21_to_upper("\n\t\\!@#$%^&*()_+=-§±~`|';:/.,"), "\n\t\\!@#$%^&*()_+=-§±~`|';:/.,");
  ck_assert_pstr_eq(s21_to_upper(s21_NULL), s21_NULL);

}
END_TEST

START_TEST(to_lower)
{
#line 203
  ck_assert_str_eq(s21_to_lower("hello School21"), "hello school21");
  ck_assert_str_eq(s21_to_lower("HeLlO"), "hello");
  ck_assert_str_eq(s21_to_lower(""), "");
  ck_assert_str_eq(s21_to_lower("123456"), "123456");
  ck_assert_str_eq(s21_to_lower("hello"), "hello");
  ck_assert_str_eq(s21_to_upper("\n\t\\!@#$%^&*()_+=-§±~`|';:/.,"), "\n\t\\!@#$%^&*()_+=-§±~`|';:/.,");
  ck_assert_pstr_eq(s21_to_upper(s21_NULL), s21_NULL);

}
END_TEST

START_TEST(insert)
{
#line 212
  char src[100] = "You can lead a horse to water,";
  char str[] = " but you can’t make him drink it.";
  ck_assert_pstr_eq(s21_insert(src, str, 30), "You can lead a horse to water, but you can’t make him drink it.");
  ck_assert_pstr_eq(s21_insert(src, str, 0), " but you can’t make him drink it.You can lead a horse to water,");
  ck_assert_pstr_eq(s21_insert(src, str, 8), "You can  but you can’t make him drink it.lead a horse to water,");
  ck_assert_pstr_eq(s21_insert("", str, 0), " but you can’t make him drink it.");
  ck_assert_pstr_eq(s21_insert(src, "", 0), "You can lead a horse to water,");
  ck_assert_pstr_eq(s21_insert(src, str, 70), s21_NULL);
  ck_assert_pstr_eq(s21_insert(src, NULL, 7), s21_NULL);
  ck_assert_pstr_eq(s21_insert("123456", "0987", 2), "1209873456");
  ck_assert_pstr_eq(s21_insert("!@#$%^&*()", "?><~", 7), "!@#$%^&?><~*()");

}
END_TEST

START_TEST(trim)
{
#line 225
  char str[] = "-!Nothing is impossible-= to a willing heart!-=";
  char str1[] = "Nothing is impossible-= to a willing heart";
  ck_assert_pstr_eq(s21_trim(str, "-!="), str1);
  //ck_assert_pstr_eq(s21_trim("", ""), "");
  //ck_assert_pstr_eq(s21_trim(s21_NULL, ""), s21_NULL);
  ck_assert_pstr_eq(s21_trim(str, "cdf7"), str);
  //ck_assert_pstr_eq(s21_trim(str, s21_NULL), str);
  ck_assert_pstr_eq(s21_trim(str, ""), str);

}
END_TEST

START_TEST(sprintf_c)
{
#line 235
  for (int i = -256; i <= 256; i++) {
    char str1[1000];
    char str2[1000];
    char *str3 = "%c abc %123c DEF %5c 123 %-8c ,:! %19c";
    ck_assert_int_eq(sprintf(str1, str3, i, i, i, i, i),
                    s21_sprintf(str2, str3, i, i, i, i, i));
    ck_assert_pstr_eq(str1, str2);
  }
  // char str1[100];
  // char str2[100];
  // char *str3 = "%04c=% 3c";
  // ck_assert_int_eq(sprintf(str1, str3, 'a', '7'),
  //                  s21_sprintf(str2, str3, 'a', '7'));
  // ck_assert_pstr_eq(str1, str2);

}
END_TEST

START_TEST(sprintf_d)
{
#line 251
  for (int i = -4096; i <= 4096; i++) {
    char str1[1000];
    char str2[1000];
    char *str3 = "%d abc %5d DEF %-10d %.7d %2.5d %-34.12d %.d %-.d %-.5d %0d %0.0d %8.0d %0.5d";
    ck_assert_int_eq(sprintf(str1, str3, i, i, i, i, i, i, i, i, i, i , i, i, i),
                    s21_sprintf(str2, str3, i, i, i, i, i, i, i, i, i, i, i, i, i));
    ck_assert_pstr_eq(str1, str2);
    char *str4 = "%+14.5d %+.d %+d %+.2d %+.6d %+.0d %+13.0d %+0d !%+0.0d! %+8.0d %+0.5d";
    ck_assert_int_eq(sprintf(str1, str4, i, i, i, i, i, i, i, i, i, i , i, i, i),
                    s21_sprintf(str2, str4, i, i, i, i, i, i, i, i, i, i, i, i, i));
    ck_assert_pstr_eq(str1, str2);
    char *str5 = "%2.21d %0.32d %-5.28d %+-.30d %-+7.40d %*d %.*d %*.*d";
    ck_assert_int_eq(sprintf(str1, str5, i, i, i, i, i, 25, i, 32, i, -7, 1, i),
                    s21_sprintf(str2, str5, i, i, i, i, i, 25, i, 32, i, -7, 1, i));
    ck_assert_pstr_eq(str1, str2);
  }

}
END_TEST

START_TEST(sprintf_u)
{
#line 269
  for (unsigned int u = 0; u <= 4096; u++) {
    char str1[1000];
    char str2[1000];
    char *str3 = "%u abc %5u DEF %-10u %.7u %2.5u %-34.12u %.u %-.u %-.5u %0u %0.0u %8.0u %0.5u";
    ck_assert_int_eq(sprintf(str1, str3, u, u, u, u, u, u, u, u, u, u, u, u, u),
                    s21_sprintf(str2, str3, u, u, u, u, u, u, u, u, u, u, u, u, u));
    ck_assert_pstr_eq(str1, str2);
    char *str4 = "%2.21u %0.32u %-5.28u %+-.30u %-+7.40u %*u %.*u %*.*u";
    ck_assert_int_eq(sprintf(str1, str4, u, u, u, u, u, 25, u, 32, u, -7, 1, u),
                    s21_sprintf(str2, str4, u, u, u, u, u, 25, u, 32, u, -7, 1, u));
    ck_assert_pstr_eq(str1, str2);
  }

}
END_TEST

START_TEST(sprintf_i)
{
#line 283
  int i = -012;
  long int li = 5463728190354261;
  for (int x = 0; x < 2; x++) {
    char str1[1000];
    char str2[1000];
    char *str3 = "%li abc %5hi DEF %-10i %.7i %2.5i %-34.12i %.i %-.i %-.5i %0i %0.0i %8.0i %0.5i";
    ck_assert_int_eq(sprintf(str1, str3, li, i, i, i, i, i, i, i, i, i, i, i, i),
                    s21_sprintf(str2, str3, li, i, i, i, i, i, i, i, i, i, i, i, i));
    ck_assert_pstr_eq(str1, str2);
    i = 05432;
    li *= -1;
  }

}
END_TEST

START_TEST(sprintf_G_g)
{
#line 297
  char strG1[1000];
  char strG2[1000];
  double G = 87654.435678, G1 = 10, G2 = 0.001, G3 = 0.000001;
  char *strG3 = "%G %+2G %-6G %30.5G %G %G %G";
  ck_assert_int_eq(sprintf(strG1, strG3, G, G, G, G, G1, G2, G3), s21_sprintf(strG2, strG3, G, G, G, G, G1, G2, G3));
  ck_assert_pstr_eq(strG1, strG2);
  char strg1[100];
  char strg2[100];
  double g = -345678.756;
  char *strg3 = "%g %+2g %-6g %30.5g %g %g %g";
  ck_assert_int_eq(sprintf(strg1, strg3, g, g, g, g, G1, G2, G3), s21_sprintf(strg2, strg3, g, g, g, g, G1, G2, G3));
  ck_assert_pstr_eq(strg1, strg2);

}
END_TEST

START_TEST(percent)
{
#line 311
  char str1[100];
  char str2[100];
  ck_assert_int_eq(sprintf(str1, "%%test%% test%%%% test%%"), s21_sprintf(str2, "%%test%% test%%%% test%%"));
  ck_assert_pstr_eq(str1, str2);

}
END_TEST

START_TEST(sprintf_s)
{
#line 317
  char str1[100];
  char str2[100];
  char *str3 = "A penny %s earned";
  char *str4 = "saved is a penny";
  ck_assert_int_eq(sprintf(str1, str3, str4), s21_sprintf(str2, str3, str4));
  ck_assert_pstr_eq(str1, str2);
  char *str5 = "We %s know the %s of water till the %s is dry";
  ck_assert_int_eq(sprintf(str1, str5, "never", "value", "well"), s21_sprintf(str2, str5, "never", "value", "well"));
  ck_assert_pstr_eq(str1, str2);
  char *str6 = "We %10s know the %-7s of water till the %1s is dry";
  ck_assert_int_eq(sprintf(str1, str6, "never", "value", "well"), s21_sprintf(str2, str6, "never", "value", "well"));
  ck_assert_pstr_eq(str1, str2);
  char *str7 = "We %1.5s know the %-10.12s of water till the %.2s is %-.6s";
  ck_assert_int_eq(sprintf(str1, str7, "never", "value", "well", "dry"), s21_sprintf(str2, str7, "never", "value", "well", "dry"));
  ck_assert_pstr_eq(str1, str2);

}
END_TEST

START_TEST(sprintf_f)
{
#line 334
  float x = 73.489, y = -2.133;
  char str1[1000];
  char str2[1000];
  char *str3 = "%f, abc%2f def %17fghi %-7f %-2.8f 13459%-.15f %.1f %14.5f %.f %f %.2f %.7f %.0f %13.0f %0f %0.0f %0.12f %-.7f %-6f";
  ck_assert_int_eq(sprintf(str1, str3, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x),
                   s21_sprintf(str2, str3, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x));
  ck_assert_pstr_eq(str1, str2);
  char *str4 = "%+f, abc%+2f def %+17fghi %+-7f %-+2.8f 13459%+-.15f %+.1f %+14.5f %+.f %+f %+.2f %+.7f %+.0f %+13.0f %+0f %+0.0f %+0.12f %+-.7f %-+6f";
  ck_assert_int_eq(sprintf(str1, str4, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x),
                   s21_sprintf(str2, str4, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x));
  ck_assert_pstr_eq(str1, str2);
  ck_assert_int_eq(sprintf(str1, str3, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y),
                   s21_sprintf(str2, str3, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y, y));
  ck_assert_pstr_eq(str1, str2);

}
END_TEST

START_TEST(sscanf21)
{
#line 350
  char src_scanf[100] = "999991111135912x6";
  long int num;
  ck_assert_int_eq(s21_sscanf(src_scanf, "%ld", &num), sscanf(src_scanf, "%ld", &num));
  char src_scanf1[100] = "999991111135912x6";
  int num1;
  ck_assert_int_eq(s21_sscanf(src_scanf1, "%3d", &num1), sscanf(src_scanf1, "%3d", &num1));
  char src_scanf2[100] = "9912x6";
  short int num2;
  ck_assert_int_eq(s21_sscanf(src_scanf2, "%hd", &num2), sscanf(src_scanf2, "%hd", &num2));
  char src_scanf3[100] = "999991111135912x6";
  ck_assert_int_eq(s21_sscanf(src_scanf3, "%99d", &num1), sscanf(src_scanf3, "%99d", &num1));
  char src_scanf4[100] = "99999111 1135912x6";
  long int num3;
  ck_assert_int_eq(s21_sscanf(src_scanf4, "%ld %ld", &num, &num3), sscanf(src_scanf4, "%ld %ld", &num, &num3));
  ck_assert_int_eq(s21_sscanf("", "%ld", &num), sscanf("", "%ld", &num));
  ck_assert_int_eq(s21_sscanf("", "%ld %ld", &num, &num3), sscanf("", "%ld %ld", &num, &num3));
  char specs[] = "%ldabc dd %c %s";
  char c;
  char str[100];
  char src_scanf5[100] = "12abc dd \' yahoo";
  ck_assert_int_eq(s21_sscanf(src_scanf5, specs, &num, &c, str), sscanf(src_scanf5, specs, &num, &c, str));
  char src_scanf6[100] = "12 \' yahoo";
  char specs2[] = "%ldddd %c %s";
  ck_assert_int_eq(s21_sscanf(src_scanf6, specs2, &num, &c, str), sscanf(src_scanf6, specs, &num, &c, str));
  char src_scanf7[100] = "-0x2f16vb dd \' yahoo";
  char specs3[] = "%ldvb dd %c %s";
  ck_assert_int_eq(s21_sscanf(src_scanf7, specs3, &num, &c, str), sscanf(src_scanf7, specs3, &num, &c, str));
  char src_scanf8[100] = "-00001234567890vb dd \' yahoo";
  char specs4[] = "%70ldvb dd %c %s";
  ck_assert_int_eq(s21_sscanf(src_scanf8, specs4, &num, &c, str), sscanf(src_scanf8, specs4, &num, &c, str));
  char src_scanf9[100] = "-123.4567890vb dd \' yahoo";
  char specs5[] = "%070lfvb dd %c %s";
  double num4;
  ck_assert_int_eq(s21_sscanf(src_scanf9, specs5, &num4, &c, str), sscanf(src_scanf9, specs5, &num4, &c, str));
  
}
END_TEST

START_TEST(sscanf_n)
{
#line 386
  char str[] = "123 The early bird catches the worm";
  int n1, n2, d1, d2;
  ck_assert_int_eq(sscanf(str, "%d%n", &d1, &n1), s21_sscanf(str, "%d%n", &d2, &n2));
  ck_assert_int_eq(n1, n2);
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, one);
    tcase_add_test(tc1_1, two);
    tcase_add_test(tc1_1, three);
    tcase_add_test(tc1_1, four);
    tcase_add_test(tc1_1, five);
    tcase_add_test(tc1_1, six);
    tcase_add_test(tc1_1, seven);
    tcase_add_test(tc1_1, eight);
    tcase_add_test(tc1_1, nine);
    tcase_add_test(tc1_1, ten);
    tcase_add_test(tc1_1, eleven);
    tcase_add_test(tc1_1, twelve);
    tcase_add_test(tc1_1, thirteen);
    tcase_add_test(tc1_1, fourteen);
    tcase_add_test(tc1_1, fifteen);
    tcase_add_test(tc1_1, to_upper);
    tcase_add_test(tc1_1, to_lower);
    tcase_add_test(tc1_1, insert);
    tcase_add_test(tc1_1, trim);
    tcase_add_test(tc1_1, sprintf_c);
    tcase_add_test(tc1_1, sprintf_d);
    tcase_add_test(tc1_1, sprintf_u);
    tcase_add_test(tc1_1, sprintf_i);
    tcase_add_test(tc1_1, sprintf_G_g);
    tcase_add_test(tc1_1, percent);
    tcase_add_test(tc1_1, sprintf_s);
    tcase_add_test(tc1_1, sprintf_f);
    tcase_add_test(tc1_1, sscanf21);
    tcase_add_test(tc1_1, sscanf_n);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
