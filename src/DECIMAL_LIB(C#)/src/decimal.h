#ifndef SRC_DECIMAL_H
#define SRC_DECIMAL_H

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEGREE 95
#define MIN_DEGREE 97
#define MAX_SCALE 28
#define MAX_SCALE_FACTOR 2149318656
#define MAX_UINT 4294967295

typedef struct {
  unsigned int bits[4];
} decimal;

typedef struct {
  unsigned int bits[6];
} long_decimal;

int getbit(decimal value,
           int n);  // определяет 0 или 1 в конкретном бите числа
void setbit(decimal *value, int n,
            int num);  // устанавливает 0 или 1 в указанный бит
int getScale(decimal value);      // находит степень 10-ки
int getSign(decimal value);       // находим знак в decimal
void changeSign(decimal *value);  // меняем знак в decimal
void changeScale(decimal *value,
                 int new_scale);  // меняем scale в decimal
int decimal_is_zero(decimal value);  // Проверить является ли decimal 0;
int checkCorrectNumber(
    decimal value);  // Проверить корректность передаваемого Decimal
void setZeroBits(decimal *value);  // Заполнить decimal нулями
int compareDecimal(
    decimal value_1,
    decimal value_2);  // Сравнение decimal с использованием long decimal

int add(decimal value_1, decimal value_2, decimal *result);
int sub(decimal value_1, decimal value_2, decimal *result);
int mul(decimal value_1, decimal value_2, decimal *result);
int s_div(decimal value_1, decimal value_2, decimal *result);
int mod(decimal value_1, decimal value_2, decimal *result);

int is_less(decimal, decimal);
int is_less_or_equal(decimal, decimal);
int is_greater(decimal, decimal);
int is_greater_or_equal(decimal, decimal);
int is_equal(decimal, decimal);
int is_not_equal(decimal, decimal);

int from_int_to_decimal(int src,
                        decimal *dst);  // Конвертирует int в decimal
int from_decimal_to_int(decimal src,
                        int *dst);  // Конвертирует decimal в int

int from_float_to_decimal(float src,
                          decimal *dst);  // Конвертирует float в decimal
void findSignificantFigures(float src, int *mantissa,
                            int *exp);  // Определяем значимые цифры во float
int from_decimal_to_float(decimal src,
                          float *dst);  // Конвертирует decimal во float

int s_floor(decimal value,
            decimal *result);  // Округляет указанное Decimal число до
                               // ближайшего целого числа в сторону
                               // отрицательной бесконечности.
int s_round(decimal value,
            decimal *result);  // Округляет Decimal до ближайшего целого числа.
int truncate(decimal value,
             decimal *result);  // Возвращает целые цифры указанного
                                // Decimal числа; любые дробные цифры
                                // отбрасываются, включая конечные нули.
int negate(decimal value,
           decimal *result);  // Умножение decimal на -1

void EqualScale(
    decimal value_1, decimal value_2,
    long_decimal *result);  // Приведение к единому scale через long decimal
void addLongDecimal(
    long_decimal value_1, long_decimal value_2,
    long_decimal *result);  // Сложение long decimal (фактически работает
                            // для умножения decimal на 10)
void setbitLongDecimal(long_decimal *value, int n,
                       int num);  // Устанавливает bit в long decimal
int getbitLongDecimal(long_decimal value,
                      int n);  // Определяет bit в long decimal
void setZeroBitsLongDecimal(
    long_decimal *value);  // Заполняет long decimal нулями

int leftShift(decimal *value, int n);
void rightShift(decimal *value, int n);
int bringOneScale(decimal *value, int new_scale);  // Приведение scalов
int last1Bit(decimal value);
void castOneScale(long_decimal *v1, long_decimal *v2, decimal *result,
                  int scale1, int scale2);
void bankRounding(long_decimal *res_tmp, int *scale_res);
void switchForMinus(decimal *result, int x, int i, int *tmp);
void divTen(decimal value_1,
            decimal *result);  // Функция деления на 10 decimal
int mod_int(decimal value,
            int integer);  // Остаток от деления decimal на целое число
void leftShiftLongDecimal(long_decimal *value, int n);
void subLongDecimal(long_decimal value_1, long_decimal value_2,
                    long_decimal *result);
void mulLongDecimal(long_decimal value_1, long_decimal value_2,
                    long_decimal *result);
int lastDigitForRound(long_decimal value);
void divTenLongDecimal(long_decimal value, long_decimal *result);
void representsBitsLD(long_decimal value);
int is_eqLongDecimal(long_decimal v1, long_decimal v2);
int is_greaterLongDecimal(long_decimal v1, long_decimal v2);

#endif  // SRC_DECIMAL_H
