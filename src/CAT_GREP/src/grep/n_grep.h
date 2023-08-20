#ifndef SRC_GREP_N_GREP_H_
#define SRC_GREP_N_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE_LEN 500
#define SIZE_ARRAY 200
#define BUFFER 2048
#define _GNU_SOURCE

int parsing(int argc, char **argv, char *patterns,
            char file_patterns[][SIZE_ARRAY], int *index_file_pat,
            char file_name[][SIZE_ARRAY], int *index_file_name, int *e, int *i,
            int *v, int *c, int *l, int *n, int *h, int *s, int *f, int *o);

int reg(char *patterns, int i, regex_t *regex);
void open_file(char file_name[][SIZE_ARRAY], int index_file_name,
               regex_t *regex, int v, int c, int l, int n, int h, int s, int o);
int use_flags(regex_t *regex, char *str, int *count_c, int v);
int flag_f(char patterns[], char file_patterns[][SIZE_ARRAY],
           int *index_file_pat);
int flag_o(regex_t *regex, char file_name[], int index_file_name, char *str,
           int *count_c, int l, int c, int n, int v, int h, int count_str);

#endif  // SRC_GREP_N_GREP_H_
