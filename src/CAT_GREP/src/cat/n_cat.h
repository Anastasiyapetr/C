#ifndef SRC_CAT_N_CAT_H_
#define SRC_CAT_N_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE

int read_flags(int argc, char **argv, int *b, int *e, int *v, int *n, int *s,
               int *t, int *E, int *T);
int open_file(int *b, int *e, int *v, int *n, int *s, int *t, int *E, int *T,
              char *file_name, int *count_str);
void flag_bn(int b, int n, char c, int *count_str);
void flag_v(char c, int t);
int flag_s(int start, char c, int *count_s);

#endif  // SRC_N_S21_CAT_H_
