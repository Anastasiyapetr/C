#include "RomanNumerals.h"

char *solution(int n) {
  char *result = calloc(100, sizeof(char));
  int array[100] = {0};
  int index = 0, count = 0;
  int tmp = n;
  if (n <= 0) {
    fprintf(stderr, "Value error\n");
  } else {
    while (tmp > 0) {
      count++;
      tmp /= 10;
    }
    int count_res = count - 1;
    while (n > 0) {
      array[--count] = n % 10;
      n /= 10;
    }
    for (int i = 0; i <= count_res; i++) {
      if (array[i] >= 1 && array[i] <= 3) {
        while (array[i] > 0) {
          if (i == 0 && count_res == 3) {
            result[index++] = 'M';
          } else if ((i == 1 && count_res == 3) || (i == 0 && count_res == 2)) {
            result[index++] = 'C';
          } else if ((i == 2 && count_res == 3) || (i == 1 && count_res == 2) ||
                     (i == 0 && count_res == 1)) {
            result[index++] = 'X';
          } else if ((i == 3 && count_res == 3) || (i == 2 && count_res == 2) ||
                     (i == 1 && count_res == 1) || (i == 0 && count_res == 0)) {
            result[index++] = 'I';
          }
          array[i]--;
        }
      } else if (array[i] >= 4 && array[i] <= 8) {
        if ((i == 1 && count_res == 3) || (i == 0 && count_res == 2)) {
          if (array[i] == 4)
            result[index++] = 'C';
          result[index++] = 'D';
          if (array[i] >= 6) {
            while (array[i] > 5) {
              result[index++] = 'C';
              array[i]--;
            }
          }
        } else if ((i == 2 && count_res == 3) || (i == 1 && count_res == 2) ||
                   (i == 0 && count_res == 1)) {
          if (array[i] == 4)
            result[index++] = 'X';
          result[index++] = 'L';
          if (array[i] >= 6) {
            while (array[i] > 5) {
              result[index++] = 'X';
              array[i]--;
            }
          }
        } else if ((i == 3 && count_res == 3) || (i == 2 && count_res == 2) ||
                   (i == 1 && count_res == 1) || (i == 0 && count_res == 0)) {
          if (array[i] == 4)
            result[index++] = 'I';
          result[index++] = 'V';
          if (array[i] >= 6) {
            while (array[i] > 5) {
              result[index++] = 'I';
              array[i]--;
            }
          }
        }
      } else if (array[i] == 9) {
        if ((i == 1 && count_res == 3) || (i == 0 && count_res == 2)) {
          result[index++] = 'C';
          result[index++] = 'M';
        } else if ((i == 2 && count_res == 3) || (i == 1 && count_res == 2) ||
                   (i == 0 && count_res == 1)) {
          result[index++] = 'X';
          result[index++] = 'C';
        } else if ((i == 3 && count_res == 3) || (i == 2 && count_res == 2) ||
                   (i == 1 && count_res == 1) || (i == 0 && count_res == 0)) {
          result[index++] = 'I';
          result[index++] = 'X';
        }
      }
    }
  }
  return result;
}
