#ifndef SRC_N_STRING_H_
#define SRC_N_STRING_H_

#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "n_strerror.h"

#define n_NULL ((void *)0)
typedef long unsigned n_size_t;

void *n_memchr(const void *str, int c, n_size_t n);
int n_memcmp(const void *str1, const void *str2, n_size_t n);
void *n_memcpy(void *dest, const void *src, n_size_t n);
void *n_memmove(void *dest, const void *src, n_size_t n);
void *n_memset(void *str, int c, n_size_t n);
n_size_t n_strlen(const char *str);
char *n_strcat(char *dest, const char *src);
char *n_strncat(char *dest, const char *src, n_size_t n);
char *n_strchr(const char *str, int c);
int n_strcmp(const char *str1, const char *str2);
int n_strncmp(const char *str1, const char *str2, n_size_t n);
char *n_strcpy(char *dest, const char *src);
char *n_strncpy(char *dest, const char *src, n_size_t n);
n_size_t n_strcspn(const char *str1, const char *str2);
char *n_strpbrk(const char *str1, const char *str2);
char *n_strrchr(const char *str, int c);
n_size_t n_strspn(const char *str1, const char *str2);
char *n_strstr(const char *haystack, const char *needle);
char *n_strtok(char *str, const char *delim);
char *n_strerror(int errnum);
void *n_to_upper(const char *str);
void *n_to_lower(const char *str);
void *n_insert(const char *src, const char *str, n_size_t start_index);
void *n_trim(const char *src, const char *trim_chars);

////////////////// n_sprintf////////////////

struct Sign {
  int size_of_tmp_str;
  int width;
  int dop_widht;
  int star;
  int accuracy_widht;
  int len;
  int flag_minus;
  int flag_plus;
  int flag_null;
  int flag_sharp;
  int flag_space;
  int spec_g;
  int spec_x;
};

struct Spec {
  int id;
  int u;
  int f;
  int c;
  int s;
  int o;
  int xX;
  int p;
  int n;
  int eE;
  int gG;
};

void n_reverseString(char *str, char *copy_string);
void n_itoa(long long int value, char *str, int base, int flag);
void n_ftoa(long double n, char *res, int afterpoint, int flag,
            struct Sign *note);
void n_ftoaNoSharp(char *res, int afterpoint, struct Sign *note);
long double n_rounding(long double n, struct Sign *note, int afterpoint);
int n_atoiSimple(char *str);

int n_sprintf(char *str, char *format, ...);

void n_switchWidhtSprintf(char *ch, struct Sign *note, va_list factor);
void n_switchAccuracySprintf(char *ch, struct Sign *note, va_list factor);
char *n_switchSpecSprintf(char *str, char *ch, va_list factor, int *i,
                          struct Sign *note, struct Spec *specifier);
void n_switchFlagSprintf(char *ch, struct Sign *note);
void n_switchLenSprintf(const char *ch, struct Sign *note);

char *n_sprintfId(char *str, va_list factor, struct Sign *note);
char *n_sprintfU(char *str, va_list factor, struct Sign *note);
char *n_sprintfF(char *str, va_list factor, struct Sign *note);
char *n_sprintfC(char *str, va_list factor);
char *n_sprintfS(char *str, va_list factor);
char *n_sprintfO(char *str, va_list factor, struct Sign *note);
char *n_sprintfXx(char *str, va_list factor, struct Sign *note, const char *ch);
char *n_sprintfP(char *str, va_list factor);
void n_sprintfN(char *str, va_list factor);
char *n_sprintfEe(char *str, va_list factor, const char *ch, struct Sign *note);
char *n_sprintfGg(char *str, va_list factor, const char *ch, struct Sign *note);
char *n_sprintfGgAsF(char *str, char *str_for_g, struct Sign *note,
                     long double g, int flag_g);

char *n_sprintfEeCalcul(long double e, char *str, char *str_for_e,
                        struct Sign *note, int flag_e, int *i);
char *n_sprintfSpecEMore(long double e, char *str, char *str_for_e,
                         struct Sign *note, int flag_e, int *i);
char *n_sprintfSpecELess(long double e, char *str, char *str_for_e,
                         struct Sign *note, int flag_e, int *i);

int is_digit(char ch);
int is_flag(char ch);
int is_widht(char ch);
int is_spec(char ch);
int is_len(char ch);

void n_sprintfFormatic(struct Sign *note, struct Spec *specifier,
                       char *tmp_str);
char *n_sprintfCompound(char *str, char *tmp_tmp_str, struct Sign *note,
                        struct Spec *specifier);
char *n_sprintfStrX(char *str, struct Sign *note, int x);
char *n_sprintfStrY(char *str, char *str_x, char *tmp_tmp_str,
                    struct Sign *note, struct Spec *specifier);
char *n_sprintfTmpTmpStr(char *str_x, char *tmp_tmp_str, struct Sign *note,
                         struct Spec *specifier);

///////////////////////////////// n_sscanf
//////////////////////////////////////////////
struct Flags {
  int c;
  int s;
  int d;
  int i;
  int o;
  int u;
  int x;
  int f;
  int p;
  int n;
  int proc;
};

struct lenght {
  int l;
  int ll;
  int L;
  int h;
};

int n_sscanf(const char *str, const char *format, ...);
void n_parsingChooseFunc(struct Flags *formatic, struct lenght *len,
                         int *result, int *flag, char **parsing, int *ignore,
                         char **c, int *width, int *space, va_list factor);
void n_nullFormatic(struct Flags *formatic);
void n_findLen(char **c, struct lenght *len);
int n_parsingFormat(
    char **c, int *width, int *ignore, struct Flags *formatic,
    struct lenght *len,
    int *space); // Идем проверять конструкцию на наличие длины ширины
void n_parsingFormatNoFlag(char **c, int *width, int *ignore,
                           struct Flags *formatic, struct lenght *len,
                           char *width_string, int index_width, int *flag,
                           int exit, int count);
int n_parsingFlags(char **c, struct Flags *formatic); // Чекаем спецификаторы
void n_skipSpace(
    char **parsing); // Функция для пропуска пробелов в константной строке
void n_formaticN(va_list factor, const char *parsing, const char *str,
                 int ignore);
int n_formaticInt(struct Flags *formatic, struct lenght *len, char **parsing,
                  va_list factor, int width, int ignore);
int n_formaticChar(char **parsing, va_list factor, int width, int ignore,
                   int space);
int n_formaticString(char **parsing, va_list factor, int width, int ignore);
int n_formaticPtr(char **parsing, va_list factor, int width, int ignore);
/* Далее идут функции для чисел с плавающей точкой*/
int n_formaticFloat(char **parsing, va_list factor, struct lenght *len,
                    int *width,
                    int ignore); // Управляющая функция для флоатов
void n_findPoint(
    const char *parsing, int *point,
    int *result); // Смотрит, есть ли точка в числе и фиксирует ее индекс
void n_findE(const char *parsing, int end,
             int *e); // Смотрит, есть ли е в числе, фиксирует первое
                      // вхождение, все что после е относится к степени е
int n_indexEndInteger(
    int e, int point,
    int end); // Определяем конец целой части, до точки или до е
int n_indexEndFractional(
    int e, int end,
    int point); // Определяем конец дробной части: до конца числа или до е
int n_findDegreeE(const char *parsing, int e, int point,
                  int result); // Находим степень числа е
double n_convertationPart(
    const char *parsing, int index, int point, int is_it_int, int *width,
    int *check); // Преобразуем целую и дробную часть из строки в дабл
double n_useE(int degree_e, long double integer, long double frac, int e,
              int point, int znak); // Домножаем на е, если она есть

long long int n_atoi(char *str, char **end, int base, int width, int *check);
int n_atoiBase(int *base, int *start, int *stop, int *count, const char *p,
               const char *num, const int *width);

#endif // SRC_N_STRING_H_
