#ifndef SRC_SMATH_H_
#define SRC_SMATH_H_

#define S_EPS 0.00000000001
#define S_EPSSR 0.000001
#define S_PI 3.14159265358979323846
#define S_E 2.71828182846
#define S_INF_MAX 1.0 / 0.00
#define S_INF_MIN -1.00 / 0.00
#define S_NAN 0.00 / 0.00
#define S_isnan(x) __builtin_isnan(x)

#include <stdio.h>

long double s_factorial(long double x);
int s_abs(int x);  // | вычисляет абсолютное значение числа |
long double s_fabs(
    double x);  // | вычисляет абсолютное значение числа с плавающей точкой |
long double s_floor(double x);  // | возвращает ближайшее целое число, не
                                //превышающее заданное значение |
long double s_ceil(double x);  // | возвращает ближайшее целое число, не
                               //меньшее заданного значения |
long double s_pow(double base,
                  double exp);  // | возводит число в заданную степень |
long double s_sqrt(double x);  // | вычисляет квадратный корень |
long double s_fmod(
    double x,
    double y);  // | остаток операции деления с плавающей точкой |

long double s_cos(double x);   // | вычисляет косинус |
long double s_acos(double x);  // | вычисляет арккосинус |
long double s_exp(
    double x);  // | возвращает значение e, возведенное в заданную степень |
long double s_log(double x);  // | вычисляет натуральный логарифм |

long double s_sin(double x);   // | вычисляет синус |
long double s_asin(double x);  // | вычисляет арксинус |
long double s_tan(double x);   // | вычисляет тангенс |
long double s_atan(double x);  // | вычисляет арктангенс |

#endif  // SRC_SMATH_H_
