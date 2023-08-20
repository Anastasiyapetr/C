#include "n_grep.h"

int main(int argc, char **argv) {
  int flags = 1;
  regex_t regex;
  int e = 0, i = 0, v = 0, c = 0, l = 0, n = 0, h = 0, s = 0, f = 0, o = 0;
  char patterns[BUFFER] = {'\0'},
       file_patterns[SIZE_ARRAY][SIZE_ARRAY] = {'\0'},
       file_name[SIZE_ARRAY][SIZE_ARRAY] = {'\0'};

  int index_file_name = 0, index_file_pat = 0;

  flags =
      parsing(argc, argv, patterns, file_patterns, &index_file_pat, file_name,
              &index_file_name, &e, &i, &v, &c, &l, &n, &h, &s, &f, &o);

  if (flags && strlen(patterns) != 0) {
    flags = reg(patterns, i, &regex);
  } else {
    flags = 0;
  }
  if (flags) {
    open_file(file_name, index_file_name, &regex, v, c, l, n, h, s, o);
    if (index_file_name == 0) {
      flags = 0;
    }
    regfree(&regex);
  }

  if (!flags) {
    exit(EXIT_FAILURE);
  }
  return 0;
}

int parsing(int argc, char **argv, char *patterns,
            char file_patterns[][SIZE_ARRAY], int *index_file_pat,
            char file_name[][SIZE_ARRAY], int *index_file_name, int *e, int *i,
            int *v, int *c, int *l, int *n, int *h, int *s, int *f, int *o) {
  int rez = 0, flag = 1, option_index = 0;

  const struct option long_options[] = {{NULL, 0, NULL, 0}};

  while ((rez = getopt_long(argc, argv, "e:f:ivclnhso", long_options,
                            &option_index)) != -1) {
    if (rez == 'e') {
      *e = 1;
      if (strlen(patterns) + strlen(optarg) + 2 <= BUFFER) {
        strcat(patterns, optarg);
        strcat(patterns, "|");
      } else {
        fprintf(stderr, "maximum number of patterns reached\n");
      }
    } else if (rez == 'f') {
      if (*index_file_name <= SIZE_ARRAY) {
        strcat(file_patterns[*index_file_pat], optarg);
        *index_file_pat = *index_file_pat + 1;
        *f = 1;
      } else {
        fprintf(stderr, "maximum number of files reached\n");
      }
    } else if (rez == 'i') {
      *i = 1;
    } else if (rez == 'v') {
      *v = 1;
    } else if (rez == 'c') {
      *c = 1;
    } else if (rez == 'l') {
      *l = 1;
    } else if (rez == 'n') {
      *n = 1;
    } else if (rez == 'o') {
      *o = 1;
    } else if (rez == 's') {
      *s = 1;
    } else if (rez == 'h') {
      *h = 1;
    } else {
      flag = 0;
      fprintf(stderr, "grep: invalid max count\n");
    }
  }
  if (f && flag) {
    flag = flag_f(patterns, file_patterns, index_file_pat);
  }
  if (flag) {
    if (*e == 0 && *f == 0 && optind < argc) {
      strcpy(patterns, argv[optind++]);
    } else {
      if (strlen(patterns) > 1) {
        patterns[strlen(patterns) - 1] = '\0';
      }
    }
    while (optind < argc) {
      if (*index_file_name <= SIZE_ARRAY) {
        strcat(file_name[*index_file_name], argv[optind++]);
        *index_file_name = *index_file_name + 1;
      } else {
        fprintf(stderr, "maximum number of files reached\n");
      }
    }
  }
  return flag;
}

int flag_f(char patterns[], char file_patterns[][SIZE_ARRAY],
           int *index_file_pat) {
  int flag = 1;
  char str[BUFFER] = {'\0'};
  for (int i = 0; i < *index_file_pat; i++) {
    FILE *fp;
    if ((fp = fopen(file_patterns[i], "rb")) == NULL) {
      fprintf(stderr, "grep: no such file or directory\n");
      flag = 0;
    } else {
      while ((fgets(str, MAX_SIZE_LEN, fp)) != NULL) {
        if (str[strlen(str) - 1] == '\n') {
          str[strlen(str) - 1] = '\0';
        }
        if (strlen(patterns) + strlen(str) + 2 <= BUFFER) {
          strcat(patterns, str);
          strcat(patterns, "|");
        } else {
          fprintf(stderr, "maximum number of files reached\n");
        }
      }
      fclose(fp);
    }
  }
  return flag;
}

int reg(char *patterns, int i, regex_t *regex) {
  int flag = 1, reti = 0;
  if (i) {
    reti = regcomp(regex, patterns, REG_ICASE | REG_EXTENDED);
  } else {
    reti = regcomp(regex, patterns, REG_EXTENDED | REG_NEWLINE);
  }
  if (reti != 0) {
    perror("Could not compile regex\n");
    flag = 0;
  }
  return flag;
}

void open_file(char file_name[][SIZE_ARRAY], int index_file_name,
               regex_t *regex, int v, int c, int l, int n, int h, int s,
               int o) {
  char str[BUFFER] = {'\0'};
  for (int j = 0; j < index_file_name; j++) {
    FILE *fp;
    if ((fp = fopen(file_name[j], "rb")) == NULL) {
      if (!s) {
        perror("grep: No such file or directory\n");
      }
    } else {
      int count_c = 0, count_str = 0, block = 0;
      while ((fgets(str, MAX_SIZE_LEN, fp)) != NULL) {
        count_str++;
        if (str[strlen(str) - 1] != '\n') {
          strcat(str, "\n");
        }
        if (o) {
          block = flag_o(regex, file_name[j], index_file_name, str, &count_c, l,
                         c, n, v, h, count_str);
        } else {
          int print = 0;
          block = use_flags(regex, str, &count_c, v);

          if (!block && !l && !c && !print) {
            if (index_file_name > 1 && !h) {
              printf("%s:", file_name[j]);
            }
            if (n) {
              printf("%d:", count_str);
            }
            printf("%s", str);
            print = 1;
          }
        }
      }
      if (l && count_c != 0) {
        printf("%s\n", file_name[j]);
      }
      if (c && !l) {
        if (index_file_name > 1 && !h) {
          printf("%s:", file_name[j]);
        }
        printf("%d\n", count_c);
      }
      fclose(fp);
    }
  }
}

int use_flags(regex_t *regex, char *str, int *count_c, int v) {
  int block = 0, reti = 0;

  reti = regexec(regex, str, 0, NULL, 0);
  if ((v && reti == 0) || (!v && reti == REG_NOMATCH)) {
    block = 1;
  } else if ((v && reti == REG_NOMATCH) || (!v && reti == 0)) {
    block = 0;
    *count_c = *count_c + 1;
  }
  return block;
}

int flag_o(regex_t *regex, char file_name[], int index_file_name, char *str,
           int *count_c, int l, int c, int n, int v, int h, int count_str) {
  regmatch_t pmatch[1];
  regoff_t off = -1, len;
  char *s = str;
  int block = 1, flag = 0;

  while (1) {
    if ((regexec(regex, s, (sizeof(pmatch) / sizeof(pmatch[0])), pmatch, 0)) ==
        REG_NOMATCH) {
      if (v && off == -1) {
        flag = 1;
      }
      break;
    } else {
      off = pmatch[0].rm_so + (s - str);
      len = pmatch[0].rm_eo - pmatch[0].rm_so;
      if (!c && !l && !v) {
        if (index_file_name > 1 && !h) {
          printf("%s:", file_name);
        }
        if (n) {
          printf("%d:", count_str);
        }
        for (int j = (int)off; j < (int)off + (int)len; j++) {
          printf("%c", str[j]);
        }
        printf("\n");
      }
      s += pmatch[0].rm_eo;
      if (!v) {
        flag = 1;
      }
    }
  }

  if (flag) {
    *count_c = *count_c + 1;
  }
  return block;
}
