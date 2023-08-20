# MATH_LIB

Реализация собственной версии математической библиотеки math.h.

## Contents

0. [Introduction](#introduction)
1. [Information](#information) 


## Introduction

![math](misc/rus/math.png)

В данном проекте разработана своя версия стандартной библиотеки math.h на языке программирования С.

## Information

### Обзор реализованных функций "math.h"

| No. | Function | Description |
| --- | -------- | ----------- |
| 1 | `int abs(int x)` | вычисляет абсолютное значение целого числа |
| 2 | `long double acos(double x)` | вычисляет арккосинус |
| 3 | `long double asin(double x)` | вычисляет арксинус |
| 4 | `long double atan(double x)` | вычисляет арктангенс |
| 5 | `long double ceil(double x)` | возвращает ближайшее целое число, не меньшее заданного значения |
| 6 | `long double cos(double x)` | вычисляет косинус |
| 7 | `long double exp(double x)` | возвращает значение e, возведенное в заданную степень |
| 8 | `long double fabs(double x)` | вычисляет абсолютное значение числа с плавающей точкой |
| 9 | `long double floor(double x)` | возвращает ближайшее целое число, не превышающее заданное значение |
| 10 | `long double fmod(double x, double y)` | остаток операции деления с плавающей точкой |
| 11 | `long double log(double x)` | вычисляет натуральный логарифм |
| 12 | `long double pow(double base, double exp)` | возводит число в заданную степень |
| 13 | `long double sin(double x)` | вычисляет синус |
| 14 | `long double sqrt(double x)` | вычисляет квадратный корень |
| 15 | `long double tan(double x)` | вычисляет тангенс |  


### Общая информация о проекте

- Библиотека разработана на языке С стандарта C11.
- Код библиотеки находится в папке src.
- Решение оформлено как статическая библиотека (с заголовочным файлом Smath.h)
- Полное покрытие unit-тестами функций библиотеки c помощью библиотеки Check
- В цели gcov_report формируется отчёт gcov в виде html страницы.
- Для сборки библиотеки и тестов предусмотрен Makefile (с целями all, clean, test, s21_math.a, gcov_report)  