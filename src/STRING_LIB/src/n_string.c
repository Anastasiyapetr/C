#include "n_string.h"

#define RADIX 10
#define MAX_LEN_MESSAGE 2050
#define MIN_LEN_MESSAGE 50

void *n_memchr(const void *str, int c, n_size_t n) {
  unsigned char *sym = n_NULL;
  unsigned char *src = (unsigned char *)str;
  for (n_size_t i = 0; i < n; i++) {
    if (*src == c) {
      sym = src;
      i = n;
    }
    src++;
  }
  return sym;
}

int n_memcmp(const void *str1, const void *str2, n_size_t n) {
  int res = 0;
  n_size_t i = 0;
  unsigned char *src1 = (unsigned char *)str1;
  unsigned char *src2 = (unsigned char *)str2;
  while (i++ < n) {
    if (*src1 != *src2) {
      res = *src1 - *src2;
      i = n;
    }
    src1++;
    src2++;
  }
  return res;
}

void *n_memcpy(void *dest, const void *src, n_size_t n) {
  unsigned char *KUDA = (unsigned char *)dest;
  unsigned char *OTKUDA = (unsigned char *)src;
  n_size_t len = n;
  if (KUDA < OTKUDA)
    while (len--) {
      *KUDA++ = *OTKUDA++;
    }
  else
    while (len--) {
      *(KUDA + len) = *(OTKUDA + len);
    }
  return dest;
}

void *n_memmove(void *dest, const void *src, n_size_t n) {
  unsigned char *KUDA = (unsigned char *)dest;
  unsigned char *OTKUDA = (unsigned char *)src;
  n_size_t len = n, i = 0;
  unsigned char tmp[n];
  while (i < n) {
    tmp[i] = *OTKUDA;
    OTKUDA++;
    i++;
  }
  i = 0;
  while (len--)
    *(KUDA++) = tmp[i++];
  return dest;
}

void *n_memset(void *str, int c, n_size_t n) {
  unsigned char *tmp = (unsigned char *)str;
  while (n--)
    *(tmp++) = c;
  return str;
}

n_size_t n_strlen(const char *str) {
  n_size_t i = 0;
  while (*(str++) != '\0')
    i++;
  return i;
}

char *n_strcat(char *dest, const char *src) {
  n_size_t i = n_strlen(dest);
  while (*src != '\0')
    dest[i++] = *(src++);
  dest[i] = '\0';
  return dest;
}

char *n_strncat(char *dest, const char *src, n_size_t n) {
  n_size_t i = n_strlen(dest);
  while (*src != '\0' && n--)
    dest[i++] = *(src++);
  dest[i] = '\0';
  return dest;
}

char *n_strchr(const char *str, int c) {
  char *a = n_NULL;
  int flag = 0;
  while (!flag) {
    if (*str == c % 128) {
      a = (char *)str;
      flag = 1;
    }
    if (*str == '\0')
      flag = 1;
    str++;
  }
  return a;
}

int n_strcmp(const char *str1, const char *str2) {
  int res = 0;
  while (res == 0 && (*str1 != '\0' || *str2 != '\0')) {
    unsigned char c1 = *str1;
    unsigned char c2 = *str2;
    res = c1 - c2;
    str1++;
    str2++;
  }
  return res;
}

int n_strncmp(const char *str1, const char *str2, n_size_t n) {
  int res = 0;
  while (res == 0 && (*str1 != '\0' || *str2 != '\0') && n--)
    res = *str1++ - *str2++;
  return res;
}

char *n_strcpy(char *dest, const char *src) {
  char *tmp = dest;
  if (*src == '\0')
    *dest = *src;
  while (*src != '\0') {
    *dest++ = *src++;
    *dest = '\0';
  }
  return tmp;
}

char *n_strncpy(char *dest, const char *src, n_size_t n) {
  char *tmp = dest;
  while (n--)
    *dest++ = *src++;
  return tmp;
}

n_size_t n_strcspn(const char *str1, const char *str2) {
  n_size_t len = 0;
  int flag = 0;
  const char *tmp = str2;
  while (*str1 != '\0' && !flag) {
    str2 = tmp;
    while (*str2 != '\0' && !flag) {
      if (*str1 == *str2)
        flag = 1;
      str2++;
    }
    if (flag == 0)
      len++;
    str1++;
  }
  return len;
}

char *n_strpbrk(const char *str1, const char *str2) {
  int flag = 0;
  const char *tmp = str2;
  while (*str1 != '\0' && !flag) {
    str2 = tmp;
    while (*str2 != '\0' && !flag) {
      if (*str1 == *str2)
        flag = 1;
      str2++;
    }
    if (!flag)
      str1++;
  }
  char *d = (char *)str1;
  return flag == 1 ? d : n_NULL;
}

char *n_strrchr(const char *str, int c) {
  int flag = 0;
  char *str2 = (char *)str;
  const char *tmp = str2;
  tmp--;
  while (*str2 != '\0')
    str2++;
  while (str2 != tmp && !flag) {
    if (*str2 == c % 128)
      flag = 1;
    if (!flag)
      str2--;
  }
  return flag == 1 ? str2 : n_NULL;
}

n_size_t n_strspn(const char *str1, const char *str2) {
  n_size_t i = 0;
  while (str1[i]) {
    if (!n_strchr(str2, str1[i]))
      break;
    i++;
  }
  return (i);
}

char *n_strstr(const char *haystack, const char *needle) {
  const char *hs = haystack;
  const char *ndl = needle;
  char *result = n_NULL;
  int flag = 0;
  int stop = 0;
  int len_hay = n_strlen(haystack);
  int len_need = n_strlen(needle);
  if (len_hay < len_need) {
    flag = 1;
    stop = 1;
  }
  if (len_need == 0) {
    stop = 1;
    flag = 1;
    result = (char *)haystack;
  }
  while (*haystack != '\0' && !flag) {
    while (*hs != '\0' && *ndl != '\0' && !flag) {
      if (*hs != *ndl)
        flag = 1;
      else {
        ndl++;
        hs++;
      }
    }
    if (flag) {
      flag = 0;
      hs = ++haystack;
      ndl = needle;
    } else if (*ndl == '\0') {
      flag = 1;
    } else {
      flag = 1;
      stop = 1;
    }
  }
  if (flag && !stop)
    result = (char *)haystack;
  return result;
}

char *n_strtok(char *str, const char *delim) {
  char *result = n_NULL;
  static char *next;
  if (str) {
    next = str;
    while (*next &&
           n_strchr(delim, *next)) { // первый проход по строке, дабы отсечь
                                     // начало строки, если оно совпадет с delim
      next++;
    }
    // str = next; // первоначальная строка видоизменится после первого прохода,
    // если будут совпадения
  }
  if (*next) {
    result = next;
    while (*next && !n_strchr(delim, *next))
      ++next;
    while (*next && n_strchr(delim, *next))
      *next++ = '\0';
  }
  return result;
}

char *n_strerror(int errnum) {
  char *result = n_NULL;
  char *p = malloc(RADIX + 1);
  static char message[MAX_LEN_MESSAGE];
  for (int i = 0; i < MAX_LEN_MESSAGE; i++)
    message[i] = '\0';
  if ((errnum < 0 || errnum > 133) && OPERATINGSYSTEM) { // linux
    n_strcat(message, ARRAY_ERROR[134]);
    n_itoa(errnum, p, RADIX, 1); // перемещаем номер ошибки в строку, RADIX -
                                 // 10 - чная система счисления номера ошибки
    if (errnum < 0)
      n_strcat(message, "-");
    n_strcat(message, p);
    result = (char *)message;
  } else if ((errnum < 0 || errnum > 106) && !OPERATINGSYSTEM) { // MACos
    n_strcat(message, ARRAY_ERROR[107]);
    n_itoa(errnum, p, RADIX, 1);
    if (errnum < 0)
      n_strcat(message, "-");
    n_strcat(message, p);
    result = (char *)message;
  } else {
    result = ARRAY_ERROR[errnum];
  }
  free(p);

  return result;
}

void *n_to_upper(const char *str) {
  char *tmp = n_NULL;
  if (str != n_NULL) {
    char *copy = calloc(n_strlen(str) + 1, sizeof(char));
    tmp = copy;
    while (*str != '\0') {
      if (*str <= 122 && *str >= 97)
        *copy++ = *str++ - 32;
      else
        *copy++ = *str++;
    }
    *copy = '\0';
  }
  return tmp;
}

void *n_to_lower(const char *str) {
  char *tmp = n_NULL;
  if (str != n_NULL) {
    char *copy = malloc(sizeof(char) * n_strlen(str) + 1);
    tmp = copy;
    while (*str != '\0') {
      if (*str <= 90 && *str >= 65)
        *copy++ = *str++ + 32;
      else
        *copy++ = *str++;
    }
    *copy = '\0';
  }
  return tmp;
}

void *n_insert(const char *src, const char *str, n_size_t start_index) {
  char *tmp = n_NULL;
  if (src != n_NULL && *src != '\0') {
    int len = 0;
    int ss = 0;
    if (str == n_NULL) {
      len = n_strlen(src) + 1;
    } else {
      ss = n_strlen(str);
      len = ss + n_strlen(src) + 1;
    }
    int s = start_index;
    if (s >= 0 && start_index <= n_strlen(src) && src != n_NULL) {
      char *copy = calloc(len, sizeof(char));
      tmp = copy;
      n_size_t i = start_index;
      n_size_t k = start_index;
      while (src[start_index] != '\0') {
        copy[start_index + ss] = src[start_index];
        start_index++;
      }
      if (str != n_NULL)
        while (*str != '\0')
          copy[i++] = *str++;
      for (n_size_t f = 0; f < k; f++)
        copy[f] = src[f];
    } else
      tmp = n_NULL;
  }
  return tmp;
}

void *n_trim(const char *src, const char *trim_chars) {
  char *copy = calloc(n_strlen(src) + 1, sizeof(char));
  char *d = (char *)copy;
  int nachecku = 0, close_cycle_trim = 0, done = 0, cdvig = 0;
  n_strcpy(copy, src);
  char default_chars[7] = " \t\n\v\r\f\0";
  if (trim_chars == n_NULL || n_strlen(trim_chars) == 0)
    trim_chars = default_chars;
  for (int i = 0; src[i] != '\0' && !done; i++) {
    for (int j = 0; trim_chars[j] != '\0' && !close_cycle_trim; j++) {
      if (src[i] == trim_chars[j]) {
        for (int k = i; src[k] != '\0'; k++)
          copy[k - cdvig] = src[k + 1];
        cdvig++;
        nachecku = 1;
        close_cycle_trim = 1;
      } else if (nachecku && trim_chars[j + 1] == '\0')
        done = 1;
      if (!nachecku && trim_chars[j + 1] == '\0')
        done = 1;
    }
    close_cycle_trim = 0;
  }
  nachecku = 0;
  done = 0;
  for (int i = n_strlen(src) - cdvig - 1; i != -1 && !done; i--) {
    for (int j = 0; trim_chars[j] != '\0' && !close_cycle_trim; j++) {
      if (copy[i] == trim_chars[j]) {
        for (int k = i; copy[k] != '\0'; k++)
          copy[k] = copy[k + 1];
        nachecku = 1;
        close_cycle_trim = 1;
      } else if (nachecku && trim_chars[j + 1] == '\0')
        done = 1;
      if (!nachecku && trim_chars[j + 1] == '\0')
        done = 1;
    }
    close_cycle_trim = 0;
  }
  return d;
}

///////////////////////////////////////////// n_sprintf
///////////////////////////////////////////////////////////////

int n_sprintf(char *str, char *format, ...) {
  int flag_spec = 0;
  struct Spec specifier = {0};
  struct Sign note = {0};
  note.accuracy_widht = note.width = -1;
  va_list factor;
  va_start(factor, format);
  int i = 0;
  for (char *ch = format; *ch; ch++) {
    if (*ch != '%') {
      str[i++] = *ch;
    } else {
      ch++;
      while ((is_flag(*ch) || is_widht(*ch) || is_spec(*ch) || *ch == '.' ||
              is_len(*ch)) &&
             !flag_spec) {
        if (is_flag(*ch) && note.width == -1)
          n_switchFlagSprintf(ch, &note);
        else if (is_widht(*ch) && note.width == -1)
          n_switchWidhtSprintf(ch, &note, factor);
        else if (*ch == '.') {
          note.accuracy_widht = -2;
          if (is_widht(*++ch))
            n_switchAccuracySprintf(ch, &note, factor);
          else
            ch--;
        } else if (is_len(*ch))
          n_switchLenSprintf(ch, &note);
        else if (is_spec(*ch)) {
          flag_spec = 1;
          str[i] = '\0';
          n_switchSpecSprintf(str, ch, factor, &i, &note, &specifier);
        }
        ch++;
      }
      if (flag_spec == 0)
        str[i++] = '%';
      flag_spec = 0;
      ch--;
    }
  }
  va_end(factor);
  str[i] = '\0';
  return (int)n_strlen(str);
}

char *n_switchSpecSprintf(char *str, char *ch, va_list factor, int *i,
                          struct Sign *note, struct Spec *specifier) {
  char *tmp_str = calloc(MAX_LEN_MESSAGE, sizeof(char));
  char *tmp_tmp_str = tmp_str;
  switch (*ch) {
  case 'i':
  case 'd':
    n_sprintfId(tmp_str, factor, note);
    specifier->id++;
    break;
  case 'u':
    n_sprintfU(tmp_str, factor, note);
    specifier->u++;
    break;
  case 'f':
    n_sprintfF(tmp_str, factor, note);
    specifier->f++;
    break;
  case 'c':
    n_sprintfC(tmp_str, factor);
    specifier->c++;
    break;
  case 's':
    n_sprintfS(tmp_str, factor);
    specifier->s++;
    break;
  case 'o':
    n_sprintfO(tmp_str, factor, note);
    specifier->o++;
    break;
  case 'X':
  case 'x':
    n_sprintfXx(tmp_str, factor, note, ch);
    specifier->xX++;
    break;
  case 'p':
    n_sprintfP(tmp_str, factor);
    specifier->p++;
    break;
  case 'n':
    n_sprintfN(str, factor);
    specifier->n++;
    break;
  case 'E':
  case 'e':
    n_sprintfEe(tmp_str, factor, ch, note);
    specifier->eE++;
    break;
  case 'G':
  case 'g':
    n_sprintfGg(tmp_str, factor, ch, note);
    specifier->gG++;
    break;
  default:
    *tmp_str++ = *ch;
  }
  n_sprintfFormatic(note, specifier, tmp_str);
  n_sprintfCompound(str, tmp_tmp_str, note, specifier);
  *i = n_strlen(str);
  tmp_str = tmp_tmp_str;
  free(tmp_str);
  return str;
}

char *n_sprintfId(char *str, va_list factor, struct Sign *note) {
  long int digit = 0;
  if (note->len == 108)
    digit = va_arg(factor, long int);
  else if (note->len == 104)
    digit = (short int)va_arg(factor, int);
  else
    digit = va_arg(factor, int);
  char *str_for_id = calloc(MAX_LEN_MESSAGE, sizeof(char));
  char *tmp = str_for_id;
  n_itoa(digit, str_for_id, 10, 0);
  if (digit < 0)
    *str++ = '-';
  if (note->flag_plus) {
    if (digit >= 0)
      *str++ = '+';
  } else if (note->flag_space) {
    if (digit >= 0)
      *str++ = ' ';
  }
  while (*str_for_id != '\0')
    *str++ = *str_for_id++;
  str_for_id = tmp;
  free(str_for_id);
  return str;
}

char *n_sprintfU(char *str, va_list factor, struct Sign *note) {
  unsigned long int digit_u = 0;
  if (note->len == 108)
    digit_u = va_arg(factor, unsigned long int);
  else if (note->len == 104)
    digit_u = (short unsigned int)va_arg(factor, unsigned int);
  else
    digit_u = va_arg(factor, unsigned int);
  char *str_for_u = calloc(MAX_LEN_MESSAGE, sizeof(char));
  char *tmp = str_for_u;
  n_itoa(digit_u, str_for_u, 10, 0);
  while (*str_for_u != '\0')
    *str++ = *str_for_u++;
  str_for_u = tmp;
  free(str_for_u);
  return str;
}

char *n_sprintfF(char *str, va_list factor, struct Sign *note) {
  long double f = 0;
  if (note->len == 76)
    f = va_arg(factor, long double);
  else
    f = va_arg(factor, double);
  char *str_for_f = calloc(MAX_LEN_MESSAGE, sizeof(char));
  char *tmp = str_for_f;
  if (note->accuracy_widht == -1)
    note->accuracy_widht = 6;
  else if (note->accuracy_widht == -2)
    note->accuracy_widht = 0;
  if (f < 0)
    *str++ = '-';
  if (note->flag_plus) {
    if (f >= 0)
      *str++ = '+';
  } else if (note->flag_space) {
    if (f >= 0)
      *str++ = ' ';
  }
  if (f < 0)
    f *= -1;
  f = n_rounding(f, note, note->accuracy_widht);
  n_ftoa(f, str_for_f, note->accuracy_widht, 0, note);
  while (*str_for_f != '\0')
    *str++ = *str_for_f++;
  if (note->flag_sharp && !note->accuracy_widht) {
    while (str[n_strlen(str) - 1] == '0')
      str[n_strlen(str) - 1] = '\0';
  }
  str_for_f = tmp;
  free(str_for_f);
  return str;
}

char *n_sprintfC(char *str, va_list factor) {
  int cimbol = va_arg(factor, int);
  *str++ = cimbol;
  return str;
}

char *n_sprintfS(char *str, va_list factor) {
  char *string = va_arg(factor, char *);
  while (*string != '\0')
    *str++ = *string++;
  return str;
}

char *n_sprintfO(char *str, va_list factor, struct Sign *note) {
  unsigned long int digit_octal = 0;
  if (note->len == 108)
    digit_octal = va_arg(factor, unsigned long int);
  else if (note->len == 104)
    digit_octal = (short unsigned int)va_arg(factor, unsigned int);
  else
    digit_octal = va_arg(factor, unsigned int);
  char *str_for_o = calloc(MAX_LEN_MESSAGE, sizeof(char));
  char *tmp = str_for_o;
  n_itoa(digit_octal, str_for_o, 8, 0);
  if (note->flag_sharp && digit_octal != 0)
    *str++ = '0';
  while (*str_for_o != '\0')
    *str++ = *str_for_o++;
  str_for_o = tmp;
  free(str_for_o);
  return str;
}

char *n_sprintfXx(char *str, va_list factor, struct Sign *note,
                  const char *ch) {
  note->spec_x = 2;
  int flag_hex = 0;
  if (*ch == 'X') {
    flag_hex = 1;
    note->spec_x = 1;
  }
  unsigned long int digit_hex = 0;
  if (note->len == 108)
    digit_hex = va_arg(factor, unsigned long int);
  else if (note->len == 104)
    digit_hex = (short unsigned int)va_arg(factor, unsigned int);
  else
    digit_hex = va_arg(factor, unsigned int);
  char *str_for_xX = calloc(MAX_LEN_MESSAGE, sizeof(char));
  char *tmp = str_for_xX;
  n_itoa(digit_hex, str_for_xX, 16, flag_hex);
  if (note->flag_sharp && digit_hex != 0) {
    *str++ = '0';
    if (flag_hex)
      *str++ = 'X';
    else
      *str++ = 'x';
  } else if (digit_hex == 0) {
    note->flag_sharp--;
  }
  while (*str_for_xX != '\0')
    *str++ = *str_for_xX++;
  str_for_xX = tmp;
  free(str_for_xX);
  return str;
}

char *n_sprintfP(char *str, va_list factor) {
  void *ptr_p = va_arg(factor, void *);
  long long int lli_ptr = (long long int)ptr_p;
  char *str_for_p = calloc(MAX_LEN_MESSAGE, sizeof(char));
  char *tmp = str_for_p;
  n_itoa(lli_ptr, str_for_p, 16, 0);
  *str++ = '0';
  *str++ = 'x';
  while (*str_for_p != '\0')
    *str++ = *str_for_p++;
  str_for_p = tmp;
  free(str_for_p);
  return str;
}

void n_sprintfN(char *str, va_list factor) {
  int *ptr_n = va_arg(factor, int *);
  *ptr_n = n_strlen(str);
}

char *n_sprintfEe(char *str, va_list factor, const char *ch,
                  struct Sign *note) {
  int flag_e = 0;
  if (*ch == 'E')
    flag_e = 1;
  long double e = 0;
  if (note->len == 76)
    e = va_arg(factor, long double);
  else
    e = va_arg(factor, double);
  int i = 0;
  char *str_for_e = calloc(MAX_LEN_MESSAGE, sizeof(char));
  char *tmp = str_for_e;
  if (note->accuracy_widht == -1)
    note->accuracy_widht = 6;
  else if (note->accuracy_widht == -2)
    note->accuracy_widht = 0;
  n_sprintfEeCalcul(e, str, str_for_e, note, flag_e, &i);
  str_for_e = tmp;
  free(str_for_e);
  return str;
}

char *n_sprintfGg(char *str, va_list factor, const char *ch,
                  struct Sign *note) {
  note->spec_g++;
  int flag_g = 0;
  if (*ch == 'G')
    flag_g = 1;
  long double g = 0;
  if (note->len == 76)
    g = va_arg(factor, long double);
  else
    g = va_arg(factor, double);
  int i = 0;
  char *str_for_g = calloc(MAX_LEN_MESSAGE, sizeof(char));
  char *tmp = str_for_g;
  if (note->accuracy_widht == -1) {
    note->accuracy_widht = 6;
    note->spec_g += 100;
  } else if (note->accuracy_widht == -2) {
    note->accuracy_widht = 0;
  }
  if (note->accuracy_widht != 0 && note->spec_g < 100)
    note->accuracy_widht--;
  n_sprintfEeCalcul(g, str, str_for_g, note, flag_g, &i);
  if (-4 <= i && i < note->accuracy_widht + 1) {
    n_sprintfGgAsF(str, str_for_g, note, g, flag_g);
  }
  if (note->accuracy_widht <= 0) {
    while (str[n_strlen(str) - 1] == '0' || str[n_strlen(str) - 1] == '-' ||
           str[n_strlen(str) - 1] == '+' || str[n_strlen(str) - 1] == 'e' ||
           str[n_strlen(str) - 1] == 'E') {
      str[n_strlen(str) - 1] = '\0';
    }
  }
  str_for_g = tmp;
  free(str_for_g);
  return str;
}

char *n_sprintfGgAsF(char *str, char *str_for_g, struct Sign *note,
                     long double g, int flag_g) {
  if (g < 0)
    *str++ = '-';
  if (note->flag_plus) {
    if (g >= 0)
      *str++ = '+';
  } else if (note->flag_space) {
    if (g >= 0)
      *str++ = ' ';
  }
  if (g < 0)
    g *= -1;
  if (g < 1)
    note->accuracy_widht++;
  n_memset(str, '\0', n_strlen(str));
  n_memset(str_for_g, '\0', n_strlen(str_for_g));
  g = n_rounding(g, note, note->accuracy_widht);
  n_ftoa(g, str_for_g, note->accuracy_widht, flag_g, note);
  while (*str_for_g != '\0') {
    *str++ = *str_for_g++;
  }
  return str;
}

char *n_sprintfEeCalcul(long double e, char *str, char *str_for_e,
                        struct Sign *note, int flag_e, int *i) {
  if (e < 0)
    *str++ = '-';
  if (note->flag_plus) {
    if (e >= 0)
      *str++ = '+';
  } else if (note->flag_space) {
    if (e >= 0)
      *str++ = ' ';
  }
  if (e < 0)
    e = e * (-1);
  if (e > 10) {
    for (; e >= 1; (*i)++)
      e /= (long double)10;
    e = e * 10;
    (*i)--;
  }
  if (e >= 1 || e == 0)
    n_sprintfSpecEMore(e, str, str_for_e, note, flag_e, i);
  else
    n_sprintfSpecELess(e, str, str_for_e, note, flag_e, i);
  return str_for_e;
}

char *n_sprintfSpecEMore(long double e, char *str, char *str_for_e,
                         struct Sign *note, int flag_e, int *i) {
  e = n_rounding(e, note, note->accuracy_widht);
  for (; e >= 1; (*i)++)
    e /= 10;
  e = e * 10;
  n_ftoa(e, str_for_e, note->accuracy_widht, flag_e, note);
  while (*str_for_e != '\0')
    *str++ = *str_for_e++;
  if (note->flag_sharp && note->accuracy_widht < 1 &&
      str[n_strlen(str) - 1] == '0') {
    while (str[n_strlen(str) - 1] == '0')
      str[n_strlen(str) - 1] = '\0';
    str--;
  }
  if (flag_e == 0 || flag_e == 100)
    *str++ = 'e';
  else
    *str++ = 'E';
  *str++ = '+';
  *str++ = *i / 10 + 48;
  if (*i != 0)
    *i = *i - 1;
  *str++ = *i % 10 + 48;
  return str_for_e;
}

char *n_sprintfSpecELess(long double e, char *str, char *str_for_e,
                         struct Sign *note, int flag_e, int *i) {
  for (; e < 1; (*i)++)
    e *= 10;
  e = n_rounding(e, note, note->accuracy_widht);
  n_ftoa(e, str_for_e, note->accuracy_widht, flag_e, note);
  while (*str_for_e != '\0')
    *str++ = *str_for_e++;
  if (note->flag_sharp && note->accuracy_widht < 1 &&
      str[n_strlen(str) - 1] == '0') {
    while (str[n_strlen(str) - 1] == '0')
      str[n_strlen(str) - 1] = '\0';
    str--;
  }
  if (flag_e == 0 || flag_e == 100)
    *str++ = 'e';
  else
    *str++ = 'E';
  if (*i == 0)
    *str++ = '+';
  else
    *str++ = '-';
  *str++ = *i / 10 + 48;
  *str++ = *i % 10 + 48;
  *i = *i * (-1);
  return str_for_e;
}

int is_digit(char ch) {
  int res = -1;
  if (ch >= '0' && ch <= '9')
    res = ch - 48;
  return res;
}

int is_flag(char ch) {
  int res = 0;
  if (ch == '+' || ch == '-' || ch == '0' || ch == '#' || ch == ' ')
    res = 1;
  return res;
}

int is_widht(char ch) {
  int res = 0;
  if (is_digit(ch) >= 0 || ch == '*')
    res = 1;
  return res;
}

int is_spec(char ch) {
  int res = 0;
  if (ch == 'i' || ch == 'd' || ch == 'f' || ch == 'c' || ch == 's' ||
      ch == 'o' || ch == 'X' || ch == 'x' || ch == 'p' || ch == 'n' ||
      ch == 'E' || ch == 'e' || ch == 'u' || ch == 'G' || ch == 'g' ||
      ch == '%')
    res = 1;
  return res;
}

int is_len(char ch) {
  int res = 0;
  if (ch == 'l' || ch == 'L' || ch == 'h')
    res = 1;
  return res;
}

void n_switchFlagSprintf(char *ch, struct Sign *note) {
  switch (*ch) {
  case '+':
    note->flag_plus++;
    break;
  case '-':
    note->flag_minus++;
    break;
  case '0':
    note->flag_null++;
    break;
  case '#':
    note->flag_sharp++;
    break;
  case ' ':
    note->flag_space++;
    break;
  }
}

void n_switchWidhtSprintf(char *ch, struct Sign *note, va_list factor) {
  if (is_digit(*ch) >= 0) {
    char *str_for_digit_width = calloc(MIN_LEN_MESSAGE, sizeof(char));
    for (int y = 0; is_digit(*ch) >= 0; y++)
      str_for_digit_width[y] = *ch++;
    note->width = n_atoiSimple(str_for_digit_width);
    free(str_for_digit_width);
  } else if (*ch == '*') {
    int digit = va_arg(factor, int);
    note->width = digit;
  }
}

void n_switchAccuracySprintf(char *ch, struct Sign *note, va_list factor) {
  if (is_digit(*ch) >= 0) {
    char *str_for_digit_width = calloc(MIN_LEN_MESSAGE, sizeof(char));
    for (int y = 0; is_digit(*ch) >= 0; y++) {
      str_for_digit_width[y] = *ch++;
    }
    note->accuracy_widht = n_atoiSimple(str_for_digit_width);
    free(str_for_digit_width);
  } else if (*ch == '*') {
    int digit = va_arg(factor, int);
    note->accuracy_widht = digit;
  }
}

void n_switchLenSprintf(const char *ch, struct Sign *note) { note->len = *ch; }

char *n_sprintfCompound(char *str, char *tmp_tmp_str, struct Sign *note,
                        struct Spec *specifier) {
  int x = note->width - note->size_of_tmp_str;
  char *str_x = calloc(MAX_LEN_MESSAGE, sizeof(char));
  char *str_y = calloc(MAX_LEN_MESSAGE, sizeof(char));
  if (x > 0)
    n_sprintfStrX(str_x, note, x);
  if (note->width != -1 && specifier->s && note->flag_null)
    tmp_tmp_str[note->width] = '\0';
  if (note->dop_widht > 0)
    n_sprintfStrY(str_y, str_x, tmp_tmp_str, note, specifier);
  n_sprintfTmpTmpStr(str_x, tmp_tmp_str, note, specifier);
  n_strcat(str, tmp_tmp_str);
  free(str_x);
  free(str_y);
  n_memset(specifier, 0, 11 * 4);
  n_memset(note, 0, 13 * 4);
  note->accuracy_widht = note->width = -1;
  return str;
}

char *n_sprintfStrX(char *str, struct Sign *note, int x) {
  for (int i = 0; i < x; i++) {
    if (note->flag_null)
      str[i] = '0';
    else
      str[i] = ' ';
    if (i + 1 == x)
      str[i + 1] = '\0';
  }
  return str;
}

char *n_sprintfStrY(char *str, char *str_x, char *tmp_tmp_str,
                    struct Sign *note, struct Spec *specifier) {
  for (int i = 0; i < note->dop_widht; i++) {
    str[i] = ' ';
    if (i + 1 == note->dop_widht)
      str[i + 1] = '\0';
  }
  if (note->star || (specifier->s && !note->flag_minus)) {
    n_strcat(str, str_x);
    n_memset(str_x, 0, n_strlen(str_x));
    n_strcat(str, tmp_tmp_str);
    n_strcpy(tmp_tmp_str, str);
  } else {
    n_strcat(tmp_tmp_str, str);
  }
  return tmp_tmp_str;
}

char *n_sprintfTmpTmpStr(char *str_x, char *tmp_tmp_str, struct Sign *note,
                         struct Spec *specifier) {
  if ((note->flag_minus && !note->flag_null) ||
      (note->star && note->dop_widht)) {
    n_strcat(tmp_tmp_str, str_x);
  } else if (note->flag_null) {
    char *sign_str = calloc(MAX_LEN_MESSAGE, sizeof(char));
    if (tmp_tmp_str[0] == '+')
      n_strcat(sign_str, "+");
    else if (tmp_tmp_str[0] == '-')
      n_strcat(sign_str, "-");
    else if (tmp_tmp_str[0] == ' ')
      n_strcat(sign_str, " ");
    else if (tmp_tmp_str[0] == '0' && specifier->o && note->flag_sharp)
      n_strcat(sign_str, "0");
    else if (tmp_tmp_str[0] == '0' && specifier->xX && note->spec_x == 2 &&
             note->flag_sharp)
      n_strcat(sign_str, "0x");
    else if (tmp_tmp_str[0] == '0' && specifier->xX && note->spec_x == 1 &&
             note->flag_sharp)
      n_strcat(sign_str, "0X");
    else if (tmp_tmp_str[0] == '0' && specifier->p)
      n_strcat(sign_str, "0x");
    n_strcat(sign_str, str_x);
    if (*tmp_tmp_str == '+' || *tmp_tmp_str == ' ' || *tmp_tmp_str == '-' ||
        (*tmp_tmp_str == '0' && specifier->o))
      n_strcat(sign_str, tmp_tmp_str + 1);
    else if (tmp_tmp_str[0] == '0' &&
             (tmp_tmp_str[1] == 'x' || tmp_tmp_str[1] == 'X'))
      n_strcat(sign_str, tmp_tmp_str + 2);
    else
      n_strcat(sign_str, tmp_tmp_str);
    n_strcpy(tmp_tmp_str, sign_str);
    free(sign_str);
  } else {
    n_strcat(str_x, tmp_tmp_str);
    n_strcpy(tmp_tmp_str, str_x);
  }
  return tmp_tmp_str;
}

void n_sprintfFormatic(struct Sign *note, struct Spec *specifier,
                       char *tmp_str) {
  int i = n_strlen(tmp_str);
  note->size_of_tmp_str = i;
  if (note->flag_null && note->flag_minus)
    note->flag_null--;
  if (note->flag_minus && note->flag_space)
    note->flag_space--;
  if (note->flag_sharp && specifier->xX)
    i -= 2;
  if (note->flag_sharp && specifier->o)
    i -= 1;
  if (note->accuracy_widht >= 0 && !specifier->f && !specifier->eE &&
      !specifier->gG && !specifier->c) {
    if (note->accuracy_widht == 0 && tmp_str[0] == '0' && i == 1)
      tmp_str[0] = '\0';
    if (note->width > note->accuracy_widht && !note->flag_minus)
      note->star++;
    if (!note->spec_x || note->accuracy_widht > i) {
      note->dop_widht = note->width - note->accuracy_widht;
      if (note->dop_widht + i > note->width && !specifier->s &&
          tmp_str[0] != '\0')
        note->dop_widht = note->width - i;
      note->width = note->accuracy_widht;
      note->flag_null = 10;
    }
  }
  if ((tmp_str[0] == '-' || tmp_str[0] == '+' || tmp_str[0] == ' ') &&
      note->flag_null == 10)
    note->width++;
  if (note->flag_sharp > 0 && note->flag_null && specifier->xX)
    note->width += 2;
  if (note->flag_null && specifier->p)
    note->width += 2;
  if (specifier->n) {
    n_memset(specifier, 0, 11 * 4);
    n_memset(note, 0, 13 * 4);
    note->accuracy_widht = note->width = -1;
  }
}

void n_itoa(long long int value, char *str, int base, int flag) {
  const char NUM[] = "0123456789ABCDEF";
  const char num[] = "0123456789abcdef";
  char *copy_string = str;
  if (value < 0) {
    value *= -1;
  }
  do {
    if (flag == 1) {
      *copy_string++ = NUM[value % base];
    } else {
      *copy_string++ = num[value % base];
    }
  } while (value /= base);
  *copy_string = '\0';
  n_reverseString(str, copy_string - 1);
}

void n_ftoa(long double n, char *res, int afterpoint, int flag,
            struct Sign *note) {
  if (note->spec_g && n < 1 && afterpoint <= 0)
    afterpoint = 5;
  unsigned long long int ip = (unsigned long long int)n;
  n_itoa(ip, res, 10, flag);
  int i = n_strlen(res);
  res[i] = '.';
  if (note->spec_g && note->accuracy_widht > 7)
    afterpoint = note->accuracy_widht + 2 - n_strlen(res);
  else if (note->spec_g >= 100 && ip == 0)
    afterpoint = 8;
  else if (note->spec_g >= 100)
    afterpoint = 7;
  long double fpart = n - (long double)ip;
  int flag_zero = 0;
  if (fpart <= 0.1) {
    fpart = fpart + 0.1;
    flag_zero = 1;
  }
  if (note->spec_g >= 100)
    fpart = n_rounding(fpart, note, afterpoint - (int)n_strlen(res));
  fpart = fpart * pow(10, afterpoint);
  if (afterpoint == 6)
    fpart -= 0.000001;
  n_itoa(fpart, res + i + 1, 10, flag);
  if (flag_zero)
    res[i + 1] = '0';
  n_ftoaNoSharp(res, afterpoint, note);
}

void n_ftoaNoSharp(char *res, int afterpoint, struct Sign *note) {
  if (note->spec_g >= 100 && (int)n_strlen(res) > afterpoint) {
    while ((int)n_strlen(res) != afterpoint)
      res[n_strlen(res) - 1] = '\0';
  }
  if (note->spec_g && (!note->flag_sharp || note->accuracy_widht == 0)) {
    while (res[n_strlen(res) - 1] == '0')
      res[n_strlen(res) - 1] = '\0';
  }
  if (!afterpoint && !note->flag_sharp) {
    while (res[n_strlen(res) - 1] == '0')
      res[n_strlen(res) - 1] = '\0';
  }
  if (!note->flag_sharp) {
    if (res[n_strlen(res) - 1] == '.')
      res[n_strlen(res) - 1] = '\0';
  }
}

long double n_rounding(long double n, struct Sign *note, int afterpoint) {
  int y = n;
  n = n - y;
  if (note->spec_g && afterpoint == 5)
    afterpoint = 6;
  long long int d = n * pow(10, afterpoint + 1);
  d = d % 10;
  if (d >= 5)
    n = n + (1.0 / pow(10, afterpoint));
  n = n + y;
  return n;
}

int n_atoiSimple(char *str) {
  int result = 0, x = 1;
  int stop = 0, start = 0, znak = 0, step_znak = 0;
  char *p = str;
  const char num[] = "0123456789";
  while (p[start] == ' ') {
    start++;
    p++;
  }
  if (p[0] == '-' || p[0] == '+') {
    if (p[0] == '-')
      znak = 1;
    p++;
    start++;
    step_znak = 1;
  }
  for (; p[stop] >= num[0] && p[stop] <= num[9]; stop++)
    ;
  if (stop <= 0) {
    while (*p != '\0')
      p++;
  }
  if (step_znak)
    stop += 1;
  for (; stop >= start; stop--) {
    for (int i = 0; i < 10; i++) {
      if (str[stop] == num[i]) {
        result += i * x;
        x *= 10;
      }
    }
  }
  if (znak)
    result *= -1;
  return result;
}

void n_reverseString(char *str, char *copy_string) {
  while (copy_string > str) {
    char ch = *copy_string;
    *copy_string = *str;
    *str = ch;
    copy_string--;
    str++;
  }
}

//////////////////////////////////////////// n_sscanf
//////////////////////////////////////////////////////

int n_sscanf(const char *str, const char *format, ...) {
  int flag = 0, result = 0, spec = 0;
  va_list factor;
  va_start(factor, format);
  char *parsing = (char *)str, *c = (char *)format;
  while (*c != '\0' && !flag) {
    struct Flags formatic = {0};
    struct lenght len = {0};
    int width = -1, ignore = 0, space = 0;
    flag = n_parsingFormat(&c, &width, &ignore, &formatic, &len, &space);
    if (!formatic.c)
      n_skipSpace(&parsing);
    if (formatic.n && !flag) {
      n_formaticN(factor, parsing, str, ignore);
    }
    if (result != -1 && *parsing != '\0') {
      n_parsingChooseFunc(&formatic, &len, &result, &flag, &parsing, &ignore,
                          &c, &width, &space, factor);
    }
    if (*parsing == '\0') {
      while (*c != '\0') {
        if (*c == '%' && *(c + 1) == 'n') {
          n_formaticN(factor, parsing, str, 0);
        } else if (*c == '%' && *(c + 1) == '*' && *(c + 2) == 'n') {
          n_formaticN(factor, parsing, str, 1);
        }
        c++;
      }
    }
    if (ignore)
      n_nullFormatic(&formatic);
    if ((formatic.d || formatic.i || formatic.u || formatic.x || formatic.o ||
         formatic.c || formatic.s || formatic.f || formatic.p)) {
      spec = 1;
    }
  }
  if (*parsing == '\0' && result == 0 && spec)
    result = -1;
  else if (*parsing == '\0' && *c != '\0' && result == 0)
    result = -1;
  va_end(factor);
  return result;
}

void n_formaticN(va_list factor, const char *parsing, const char *str,
                 int ignore) {
  if (!ignore) {
    int *n = va_arg(factor, int *);
    *n = parsing - str;
  }
}

void n_parsingChooseFunc(struct Flags *formatic, struct lenght *len,
                         int *result, int *flag, char **parsing, int *ignore,
                         char **c, int *width, int *space, va_list factor) {
  if (formatic->d || formatic->i || formatic->u || formatic->x || formatic->o) {
    *result += +n_formaticInt(formatic, len, parsing, factor, *width, *ignore);

    if (*result == 0) {
      formatic->d = 0, formatic->i = 0, formatic->u = 0, formatic->x = 0,
      formatic->o = 0;
    }
  } else if (formatic->c) {
    *result += n_formaticChar(parsing, factor, *width, *ignore, *space);
  } else if (formatic->s) {
    *result += n_formaticString(parsing, factor, *width, *ignore);
  } else if (formatic->f) {
    *result += n_formaticFloat(parsing, factor, len, width, *ignore);
    if (!*result)
      formatic->f = 0;
  } else if (formatic->p) {
    *result += n_formaticPtr(parsing, factor, *width, *ignore);
    if (*result == 0) {
      formatic->p = 0;
    }
  } else if (formatic->proc) {
    if (*(*parsing) == '%') {
      *parsing = *parsing + 1;
    } else {
      *flag = 1;
    }
  } else if (*(*parsing) == *(*c)) {
    while (*(*parsing) == *(*c)) {
      *parsing = *parsing + 1;
      *c = *c + 1;
    }
    *flag = 0;
  } else if (!formatic->n) {
    *flag = 1;
  }
}

int n_parsingFormat(char **c, int *width, int *ignore, struct Flags *formatic,
                    struct lenght *len, int *space) {
  char *width_string = malloc(sizeof(char) * MAX_LEN_MESSAGE);
  int flag = 0;
  while (*(*c) == ' ' || *(*c) == '\t' || *(*c) == '\n') {
    *space = 1;
    *c = *c + 1;
  }
  if (*(*c) == '%') {
    if (*(*c + 1) == '%') {
      formatic->proc = 1;
      *c = *c + 2;
      if (*(*c) != ' ' && *(*c) != '\n' && *(*c) != '\t' && *(*c) != '%' &&
          *(*c) != '\0')
        flag = 1;
    }
    if (formatic->proc != 1 && !flag)
      *c = *c + 1;
  } else if (*(*c) != '\0') {
    flag = 1;
  }
  if (!flag) {
    int index_width = 0, count = 0, exit = 1;
    n_parsingFormatNoFlag(c, width, ignore, formatic, len, width_string,
                          index_width, &flag, exit, count);
  }
  free(width_string);
  return flag;
}

void n_parsingFormatNoFlag(char **c, int *width, int *ignore,
                           struct Flags *formatic, struct lenght *len,
                           char *width_string, int index_width, int *flag,
                           int exit, int count) {
  while ((*(*c) != ' ' && *(*c) != '\0' && *(*c) != '%' && *(*c) != '\t' &&
          *(*c) != '\n') &&
         (exit != 0)) {
    if (*(*c) == '*') {
      *ignore = 1;
      *c = *c + 1;
    }
    if (*(*c) >= '0' && *(*c) <= '9') {
      while (*(*c) >= '0' && *(*c) <= '9') {
        width_string[index_width++] = *(*c);
        *c = *c + 1;
        count++;
      }
    }
    if (count != 0) {
      width_string[index_width] = '\0';
      *width = n_atoi(width_string, &width_string, 10, -1, NULL);
      width_string -= count;
      if (*width == 0)
        *width = -1;
    }
    if (*(*c) == 'l' || *(*c) == 'L' || *(*c) == 'h')
      n_findLen(c, len);
    exit = n_parsingFlags(c, formatic);
    if (exit != 0) {
      *flag = 1;
      exit = 0;
    }
  }
}

void n_findLen(char **c, struct lenght *len) {
  if (*(*c) == 'l') {
    if (*(*c + 1) == 'l') {
      len->ll = 1;
    } else {
      len->l = 1;
    }
  } else if (*(*c) == 'L') {
    len->L = 1;
  } else {
    len->h = 1;
  }
  if (len->ll) {
    *c = *c + 2;
  } else {
    *c = *c + 1;
  }
}

void n_nullFormatic(struct Flags *formatic) {
  formatic->c = 0;
  formatic->s = 0;
  formatic->d = 0;
  formatic->i = 0;
  formatic->o = 0;
  formatic->u = 0;
  formatic->x = 0;
  formatic->f = 0;
  formatic->p = 0;
  formatic->n = 0;
}

int n_parsingFlags(char **c, struct Flags *formatic) {
  int flag = 0;
  if (*(*c) == 'c') {
    formatic->c = 1;
  } else if (*(*c) == 's') {
    formatic->s = 1;
  } else if (*(*c) == 'd') {
    formatic->d = 1;
  } else if (*(*c) == 'i') {
    formatic->i = 1;
  } else if (*(*c) == 'o') {
    formatic->o = 1;
  } else if (*(*c) == 'u') {
    formatic->u = 1;
  } else if (*(*c) == 'x' || *(*c) == 'X') {
    formatic->x = 1;
  } else if (*(*c) == 'f' || *(*c) == 'g' || *(*c) == 'G' || *(*c) == 'e' ||
             *(*c) == 'E') {
    formatic->f = 1;
  } else if (*(*c) == 'p') {
    formatic->p = 1;
  } else if (*(*c) == 'n') {
    formatic->n = 1;
  } else {
    flag = 1;
  }
  if (!flag) {
    *c = *c + 1;
  }
  return flag;
}

void n_skipSpace(char **parsing) {
  int count_space = 0;
  for (char *c = *parsing;
       (*c == ' ' || *c == '\t' || *c == '\n') && (*c != '\0'); c++) {
    count_space++;
  }
  *parsing += count_space;
}

int n_formaticInt(struct Flags *formatic, struct lenght *len, char **parsing,
                  va_list factor, int width, int ignore) {
  long long int ll_integer = 0, *d_ll = NULL;
  long int l_integer = 0, *d_l = NULL;
  short int s_integer = 0, *d_h = NULL;
  int integer = 0, *d = NULL, result = 0, check = 0, digit = 0;
  if (formatic->d || formatic->u)
    digit = 10;
  else if (formatic->o)
    digit = 8;
  else if (formatic->x == 1)
    digit = 16;
  if (len->h) {
    if (formatic->d == 1 || formatic->i == 1)
      s_integer = (short int)n_atoi(*parsing, parsing, digit, width, &check);
    else
      s_integer =
          (unsigned short int)n_atoi(*parsing, parsing, digit, width, &check);
  } else if (len->l) {
    if (formatic->d == 1 || formatic->i == 1)
      l_integer = (long int)n_atoi(*parsing, parsing, digit, width, &check);
    else
      l_integer =
          (unsigned long int)n_atoi(*parsing, parsing, digit, width, &check);
  } else if (len->ll) {
    if (formatic->d == 1 || formatic->i == 1)
      ll_integer =
          (long long int)n_atoi(*parsing, parsing, digit, width, &check);
    else
      ll_integer = (unsigned long long int)n_atoi(*parsing, parsing, digit,
                                                  width, &check);
  } else {
    if (formatic->d == 1 || formatic->i == 1)
      integer = (int)n_atoi(*parsing, parsing, digit, width, &check);
    else
      integer = (unsigned int)n_atoi(*parsing, parsing, digit, width, &check);
  }
  if (!ignore) {
    if (len->h) {
      d_h = va_arg(factor, short int *);
      if (check == 0)
        *d_h = s_integer;
    } else if (len->l) {
      d_l = va_arg(factor, long int *);
      if (check == 0)
        *d_l = l_integer;
    } else if (len->ll) {
      d_ll = va_arg(factor, long long int *);
      if (check == 0)
        *d_ll = ll_integer;
    } else {
      d = va_arg(factor, int *);
      if (check == 0)
        *d = integer;
    }
    if (check == 0)
      result++;
  }
  return result;
}

int n_formaticChar(char **parsing, va_list factor, int width, int ignore,
                   int space) {
  int result = 0;
  if (space)
    n_skipSpace(parsing);
  if (!ignore && *(*parsing) != '\0' && width == -1) {
    int *ch = va_arg(factor, int *);
    *ch = (int)*(*parsing);
    result = 1;
    *parsing = *parsing + 1;
  } else if (!ignore && *(*parsing) != '\0' && width != -1) {
    char *ch = va_arg(factor, char *);
    while (width != 0 && *(*parsing) != '\0') {
      *ch = *(*parsing);
      ch++;
      *parsing = *parsing + 1;
      width--;
    }
    result = 1;
  } else if (ignore) {
    if (width == -1) {
      *parsing = *parsing + 1;
    } else {
      while (width != 0 && *(*parsing) != '\0') {
        *parsing = *parsing + 1;
        width--;
      }
    }
  }
  return result;
}

int n_formaticString(char **parsing, va_list factor, int width, int ignore) {
  int result = 0;
  if (!ignore) {
    char *ch = va_arg(factor, char *);
    if (width != -1) {
      while (*(*parsing) != ' ' && *(*parsing) != '\0' && *(*parsing) != '\n' &&
             *(*parsing) != '\t' && width != 0) {
        width--;
        *ch++ = *(*parsing);
        *parsing = *parsing + 1;
      }
    } else {
      while (*(*parsing) != ' ' && *(*parsing) != '\0' && *(*parsing) != '\n' &&
             *(*parsing) != '\t') {
        *ch++ = *(*parsing);
        *parsing = *parsing + 1;
      }
    }
    result = 1;
    *ch = '\0';
  } else {
    while (*(*parsing) != ' ' && *(*parsing) != '\0' && *(*parsing) != '\n' &&
           *(*parsing) != '\t')
      *parsing = *parsing + 1;
  }
  return result;
}

int n_formaticPtr(char **parsing, va_list factor, int width, int ignore) {
  int check = 0, result = 0;
  long long int ptr_number =
      (long long int)n_atoi(*parsing, parsing, 16, width, &check);
  if (!ignore) {
    void *ptr = va_arg(factor, void *);
    if (check == 0) {
      *((long long int *)ptr) = ptr_number;
      result = 1;
    }
  }
  return result;
}

int n_formaticFloat(char **parsing, va_list factor, struct lenght *len,
                    int *width, int ignore) {
  int step = 0, result = 0, check_int = 0, check_float = 0;
  int point = 0, e = 0, index_int = 0, degree_e = 0, index_frac = 0, znak = 0;
  long double integer = 0.0, frac = 0.0, number = 0.0;
  if (*(*parsing) == '-' || *(*parsing) == '+') {
    if (*(*parsing) == '-')
      znak = 1;
    *parsing = *parsing + 1;
    if (*width != -1)
      *width = *width - 1;
  }
  n_findPoint(*parsing, &point, &step);
  if (*width != -1 && *width < step)
    step = *width - 1;
  n_findE(*parsing, step, &e);
  if (e)
    degree_e = n_findDegreeE(*parsing, e, point, step);
  index_int = n_indexEndInteger(e, point, step);
  if (point)
    index_frac = n_indexEndFractional(e, step, point);
  integer =
      n_convertationPart(*parsing, index_int, point, 1, width, &check_int);
  if (point)
    frac =
        n_convertationPart(*parsing, index_frac, point, 0, width, &check_float);
  if (e) {
    number = n_useE(degree_e, integer, frac, e, point, znak);
  } else {
    if (check_int == 0)
      number += integer;
    if (check_float == 0)
      number += frac;
    if (znak)
      number *= (-1);
  }
  if (!ignore && !check_int) {
    if (len->L) {
      long double *f_l = va_arg(factor, long double *);
      *f_l = number;
    } else if (len->l) {
      double *f_double = va_arg(factor, double *);
      *f_double = (double)number;
    } else {
      float *f = va_arg(factor, float *);
      *f = (float)number;
    }
    result = 1;
  }
  if (*width != -1)
    *parsing += step + 1;
  else
    *parsing += step;
  return result;
}

void n_findPoint(const char *parsing, int *point, int *result) {
  int index = *result;
  for (; (parsing[index] >= '0' && parsing[index] <= '9') ||
         (parsing[index] == '.' || parsing[index] == 'e' ||
          parsing[index] == 'E' ||
          ((parsing[index] == '+' || parsing[index] == '-') &&
           (parsing[index - 1] == 'e' || parsing[index - 1] == 'E')));
       index++) {
    if (parsing[index] == '.') {
      *point = index;
    }
  }
  *result = index;
}

void n_findE(const char *parsing, int end, int *e) {
  int is_it_e = 0, i = 0;
  for (; i < end; i++) {
    if (parsing[i] == 'e' || parsing[i] == 'E') {
      is_it_e = 1;
    }
  }
  if (is_it_e) {
    for (i = 0; parsing[i] != 'e' && parsing[i] != 'E'; i++) {
      ;
    }
    *e = i;
  }
}

int n_indexEndInteger(int e, int point, int end) {
  int index_e = 0;
  if (!e && !point)
    index_e = end;
  else if (e && (!point || e < point))
    index_e = e - 1;
  else
    index_e = point - 1;
  return index_e;
}

int n_indexEndFractional(int e, int end, int point) {
  int index_e = 0;
  if ((!e) || (e < point))
    index_e = end;
  else
    index_e = e;
  return index_e;
}

int n_findDegreeE(const char *parsing, int e, int point, int result) {
  int end = 0, flag = 0, number = 0, x = 1;
  if (parsing[e + 1] == '-' || parsing[e + 1] == '+') {
    if (parsing[e + 1] == '-') {
      flag = 1;
    }
    e++;
  }
  if (point && point > e) {
    end = point - 1;
  } else {
    int i = 0;
    for (i = e + 1; (parsing[i] >= '0' && parsing[i] <= '9') && i < result;
         i++) {
      ;
    }
    end = i - 1;
  }
  while (end > e) {
    number += (parsing[end] - 48.0) * x;
    x *= 10;
    end--;
  }
  if (flag)
    number *= (-1);
  return number;
}

double n_convertationPart(const char *parsing, int index, int point,
                          int is_it_int, int *width, int *check) {
  double number = 0.0, x = 1.0;
  int start = index, end = 0, znak = 0, count = 0;
  if (!is_it_int) {
    start = point + 1;
    end = index;
    x = 0.1;
  }
  if (is_it_int) {
    if (parsing[end] == '-') {
      znak = 1;
      end++;
    } else if (parsing[end] == '+') {
      end++;
    }
    if (*width != -1 && point && point > *width)
      start = *width - 1;
    for (; start >= end; start--) {
      if (parsing[start] >= '0' && parsing[start] <= '9') {
        number += (parsing[start] - 48.0) * x;
        x *= 10.0;
        count++;
      }
      if (*width != -1)
        *width = *width - 1;
    }
  } else {
    if (*width != -1 && *width != 0)
      end = *width - 1;
    for (; start < end; start++) {
      if (parsing[start] >= '0' && parsing[start] <= '9') {
        number += (parsing[start] - 48.0) * x;
        x *= 0.1;
        count++;
      }
    }
  }
  if (znak)
    number *= (-1.0);
  if (count == 0)
    *check = 1;
  return number;
}

double n_useE(int degree_e, long double integer, long double frac, int e,
              int point, int znak) {
  long double x = 10.0, number = 0.0;
  int flag = 0;
  if (degree_e < 0) {
    degree_e *= -1;
    flag = 1;
    x = 0.1;
  }
  if (point && e < point) {
    number = integer;
  } else {
    number = integer + frac;
  }
  if (znak) {
    number *= (-1);
  }
  while (degree_e > 0) {
    if (!flag) {
      number *= x;
    } else {
      number *= 0.1;
    }
    degree_e--;
  }
  return number;
}

long long int n_atoi(char *str, char **end, int base, int width, int *check) {
  long long int result = 0, x = 1;
  int stop = 0, start = 0, znak = 0, step_znak = 0, count = 0;
  char *p = str;
  const char num[] = "0123456789ABCDEF";
  while (p[start] == ' ') {
    start++;
    str++;
    p++;
  }
  if (p[0] == '-' || p[0] == '+') {
    if (p[0] == '-')
      znak = 1;
    p++;
    start++;
    if (width != -1)
      width--;
    step_znak = 1;
  }
  if (width == 0) {
    *check = 1;
    while (*p != '\0')
      p++;
    *end = p;
  } else {
    int step = 0;
    step = n_atoiBase(&base, &start, &stop, &count, p, num, &width);
    if (step == -1) {
      while (*p != '\0')
        p++;
      *end = p;
    } else {
      *end = p + step;
    }
  }
  if (step_znak)
    stop += 1;
  for (; stop >= start; stop--) {
    for (int i = 0; i <= base - 1; i++) {
      if (str[stop] == num[i] || (i > 9 && str[stop] == (num[i] + 32))) {
        result += i * x;
        if (base == 10)
          x *= 10;
        else if (base == 8)
          x *= 8;
        else
          x *= 16;
        count++;
      }
    }
  }
  if (znak)
    result *= -1;
  if (count == 0)
    *check = 1;

  return result;
}

int n_atoiBase(int *base, int *start, int *stop, int *count, const char *p,
               const char *num, const int *width) {
  int step = 0;
  if (*base == 0 && p[0] == '0' && (p[1] == 'x' || p[1] == 'X'))
    *base = 16;
  else if (*base == 0 && p[0] == '0')
    *base = 8;
  else if (*base == 0)
    *base = 10;
  if (*base == 16 && p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
    *start = *start + 2;
    *stop = *stop + 2;
    *count = *count + 2;
  } else if (*base == 8 && p[0] == '0') {
    *start = *start + 1;
    *stop = *stop + 1;
    *count = *count + 1;
  }
  if (*base == 10 || *base == 8) {
    for (; p[*stop] >= num[0] && p[*stop] <= num[*base - 1]; *stop = *stop + 1)
      ;
  } else {
    for (; (p[*stop] >= '0' && p[*stop] <= '9') ||
           (p[*stop] >= 'A' && p[*stop] <= 'F') ||
           (p[*stop] >= 'a' && p[*stop] <= 'f');
         *stop = *stop + 1) {
      ;
    }
  }
  if (*width != -1)
    if (*width < *stop)
      *stop = *width - 1;
  if (*stop <= 0 && (*width - 1) != 0) {
    step = -1;
  } else {
    if ((*width != -1) && (*stop == *width - 1))
      step = *stop + 1;
    else
      step = *stop;
  }
  return step;
}
