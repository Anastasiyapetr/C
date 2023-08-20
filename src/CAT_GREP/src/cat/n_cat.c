#include "n_cat.h"

int main(int argc, char *argv[]) {
  int flags = 1, count_str = 1;
  int b = 0, e = 0, v = 0, n = 0, s = 0, t = 0, E = 0, T = 0;

  flags = read_flags(argc, argv, &b, &e, &v, &n, &s, &t, &E, &T);
  if (flags == 0) {
    perror("cat: illegal option\n");
  } else {
    for (int i = 1; argv[i] != NULL; i++) {
      if (argv[i][0] != '-') {
        flags = open_file(&b, &e, &v, &n, &s, &t, &E, &T, argv[i], &count_str);
      }
    }
  }

  if (!flags) {
    exit(EXIT_FAILURE);
  }
  return 0;
}

int read_flags(int argc, char **argv, int *b, int *e, int *v, int *n, int *s,
               int *t, int *E, int *T) {
  int rez = 0, flag = 1, option_index = 0;
  const struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'},
                                        {"number", 0, NULL, 'n'},
                                        {"squeeze-blank", 0, NULL, 's'},
                                        {NULL, 0, NULL, 0}};

  while ((rez = getopt_long(argc, argv, "bevnstvET", long_options,
                            &option_index)) != -1) {
    if (rez == 'b') {
      *b = 1;
    } else if (rez == 'e') {
      *e = 1;
    } else if (rez == 'v') {
      *v = 1;
    } else if (rez == 'n') {
      *n = 1;
    } else if (rez == 's') {
      *s = 1;
    } else if (rez == 't') {
      *t = 1;
    } else if (rez == 'E') {
      *E = 1;
    } else if (rez == 'T') {
      *T = 1;
    } else {
      flag = 0;
    }
  }
  return flag;
}

int open_file(int *b, int *e, int *v, int *n, int *s, int *t, int *E, int *T,
              char *file_name, int *count_str) {
  FILE *fp;
  int flag = 1, count_s = 0;
  fp = fopen(file_name, "rb");
  if (fp == NULL) {
    perror("cat: No such file or directory");
    flag = 0;
  } else {
    int start = 1, block = 0;
    char c;
    while ((c = fgetc(fp)) != EOF) {
      if (*s == 1) {
        block = flag_s(start, c, &count_s);
      }
      if (!block) {
        if ((*b || *n) && start) {
          flag_bn(*b, *n, c, count_str);
        }
        if (*t || *e) {
          *v = 1;
        }
        if ((*e || *E) && c == '\n') {
          printf("%c", '$');
        }
        if ((*t || *T) && c == '\t') {
          printf("%c%c", '^', 'I');
        }
        if (*v) {
          flag_v(c, *t);
        } else {
          printf("%c", c);
        }
      }
      if (c == '\n') {
        start = 1;
      } else {
        start = 0;
        count_s = 0;
      }
    }
    fclose(fp);
  }
  return flag;
}

void flag_bn(int b, int n, char c, int *count_str) {
  if ((b == 0 && n) || ((b == 1) && ((c != '\n') && c != '\0'))) {
    printf("%6d\t", *count_str);
    *count_str = *count_str + 1;
  }
}

void flag_v(char c, int t) {
  char symbol[32][3] = {"^@", "^A", "^B", "^C", "^D",  "^E", "^F", "^G",
                        "^H", "^I", "^J", "^K", "^L",  "^M", "^N", "^O",
                        "^P", "^Q", "^R", "^S", "^T",  "^U", "^V", "^W",
                        "^X", "^Y", "^Z", "^[", "^\\", "^]", "^^", "^_"};
  int i = c;
  if (i == 127) {
    printf("%c%c", '^', '?');
  } else if ((i >= 0 && i < 9) || (i >= 11 && i <= 31)) {
    printf("%c%c", symbol[i][0], symbol[i][1]);
  } else if ((!t) || (c != '\t')) {
    printf("%c", c);
  }
}

int flag_s(int start, char c, int *count_s) {
  int block = 0;
  if (start && c == '\n') {
    *count_s = *count_s + 1;
  }
  if (*count_s > 1 && c == '\n') {
    block = 1;
  } else {
    block = 0;
  }
  return block;
}
