#include "Smath.h"

long double s_factorial(long double x) {
  if (x == 0)
    x = 1;
  else if (x == 1)
    x = 1;
  else
    x = x * s_factorial(x - 1);
  return x;
}

int s_abs(int x) { return x > 0 ? x : -x; }

long double s_fabs(double x) { return x > 0 ? x : -x; }

long double s_floor(double x) {
  long double result = 0.0;
  if (x == 0 || x == -0 || S_isnan(x) || x == S_INF_MIN || x == S_INF_MAX) {
    result = x;
  } else {
    long double cel = (long long int)x;
    if (x > 0 || cel == x) {
      result = cel;
    } else if (x < 0 && cel != x) {
      result = cel - 1.0;
    }
  }
  return result;
}

long double s_ceil(double x) {
  long double result = 0.0;
  if (x == 0 || x == -0 || S_isnan(x) || x == S_INF_MIN || x == S_INF_MAX) {
    result = x;
  } else {
    long double cel = (long long int)x;
    if (x > 0 && cel != x) {
      result = cel + 1.0;
    } else {
      result = cel;
    }
  }
  return result;
}

long double s_pow(double base, double exp) {
  long double result = 0.0, tmp = base;
  long long int cel_exp = (long long int)exp;
  if (base == 1 || exp == 0) {
    result = 1.0;
  } else if (S_isnan(base) || S_isnan(exp)) {
    result = S_NAN;
  } else if ((s_fabs(base) < 1 && exp == S_INF_MIN) ||
             (s_fabs(base) > 1 && exp == S_INF_MAX)) {
    result = S_INF_MAX;
  } else if ((s_fabs(base) > 1 && exp == S_INF_MIN) ||
             (s_fabs(base) < 1 && (exp == S_INF_MAX || exp == S_INF_MIN))) {
    result = 0;
  } else if (base == S_INF_MIN) {
    if (cel_exp == exp && exp < 0 && cel_exp % 2) result = -0;
    if (exp < 0 && cel_exp != exp) result = 0;
    if (cel_exp == exp && exp > 0 && cel_exp % 2) result = S_INF_MIN;
    if (exp > 0 && cel_exp != exp) result = S_INF_MAX;
  } else if (base == S_INF_MAX) {
    if (exp == S_INF_MIN || exp < 0) result = 0;
    if (exp == S_INF_MAX || exp > 0) result = S_INF_MAX;
  } else if (base == 0 || base == -0) {
    if ((base == 0) && (cel_exp == exp && exp > 0)) result = 0;
    if ((base == -0) && (cel_exp == exp && exp > 0 && cel_exp % 2)) result = -0;
    if ((base == 0) && (cel_exp == exp && exp < 0 && cel_exp % 2))
      result = S_INF_MAX;
    if ((base == -0) && (cel_exp == exp && exp < 0 && cel_exp % 2))
      result = S_INF_MIN;
    if (exp < 0 && cel_exp != exp) result = S_INF_MAX;
  } else if (base == -1 && (exp == S_INF_MAX || exp == S_INF_MIN)) {
    result = 1;
  } else if (base < 0 && cel_exp != exp) {
    result = S_NAN;
  } else {
    if (tmp < 0) {
      tmp = -tmp;
      result = s_exp(exp * s_log(tmp));
      if (s_fmod(exp, 2) != 0) {
        result = -result;
      }
    } else {
      result = s_exp(exp * s_log(base));
    }
  }
  return result;
}

long double s_sqrt(double x) {
  long double result = 0.0;
  if (x < 0.0 || x == S_INF_MIN) {
    result = S_NAN;
  } else if (x == S_INF_MAX) {
    result = S_INF_MAX;
  } else if (x > 0.0) {
    long double left = 0.0;
    long double right = x > 1 ? x : 1;
    long double mid = (left + right) / 2;
    while (mid - left > S_EPS) {
      if (mid * mid > x) {
        right = mid;
      } else {
        left = mid;
      }
      mid = (left + right) / 2;
    }
    result = mid;
  } else {
    result = x;
  }
  return result;
}

long double s_fmod(double x, double y) {
  long double result = 0.0;
  if (S_isnan(x) || S_isnan(y) || y == 0 || y == -0 || x == S_INF_MAX ||
      x == S_INF_MIN) {
    result = S_NAN;
  } else if ((y == S_INF_MAX || y == S_INF_MIN) &&
             (x != S_INF_MAX && x != S_INF_MIN)) {
    result = x;
  } else if (x != 0 || x != -0) {
    long long int div = x / y;
    result = x - div * y;
  }
  return result;
}

long double s_exp(double x) {
  long double result = 0.0;
  if (S_isnan(x) || x == S_INF_MAX) {
    result = x;
  } else if (x == 0 || x == -0) {
    result = 1;
  } else if (x == S_INF_MIN) {
    result = 0;
  } else {
    long double step = 1, sum = 1, n = 1;
    int flag = 0;
    while (s_fabs((double)step) > 0.000000000001 && !flag) {
      step *= x / n;
      sum += step;
      n++;
      if (sum == S_INF_MAX) {
        sum = S_INF_MAX;
        flag = 1;
      }
    }
    result = sum;
  }
  return result;
}

long double s_log(double x) {
  int i = 0;
  double res = 0;
  double step = 0;
  if (x > 0.0 && x != S_INF_MAX) {
    for (; x >= S_E; x = x / S_E, i++) continue;
    for (int n = 0; n < 100; n++) {
      step = res;
      res = step + 2 * (x - s_exp(step)) / (x + s_exp(step));
    }
  } else if (x == 0) {
    res = S_INF_MIN;
  } else if (x < 0) {
    res = S_NAN;
  } else if (x == S_INF_MAX) {
    res = S_INF_MAX;
  }
  if (S_isnan(x)) res = S_NAN;
  return (res + i);
}

long double s_sin(double x) {
  long double sum = S_NAN;
  int n = 1;
  long double step = 0;
  if (x != S_INF_MAX && x != S_INF_MIN) {
    x = s_fmod(x, 2 * S_PI);
    sum = x;
    if (s_fabs(x) > 0.0000001) {
      do {
        step = (s_pow(-1, n) * s_pow(x, 1 + 2 * n)) / s_factorial(1 + 2 * n);
        sum += step;
        n++;
      } while (s_fabs((double)step) > 0.0000000001);
    }
  }
  return sum;
}

long double s_cos(double x) {
  double sum = S_NAN;
  int n = 0;
  long double step = 0;
  if (x != S_INF_MAX && x != S_INF_MIN && !S_isnan(x)) {
    sum = 0;
    x = s_fmod(x, 2 * S_PI);
    if (s_fabs(x) > 0.0000001) {
      do {
        step = (s_pow(-1, n) * s_pow(x, 2 * n)) / s_factorial(2 * n);
        sum += step;
        n++;
      } while (s_fabs((double)step) > 0.0000000001);
    } else if (x - 0.0000001 <= 0) {
      sum = 1;
    }
  }
  return sum;
}

long double s_atan(double x) {
  double sum = S_NAN;
  int n = 0;
  long double step = 0;
  if (x != S_INF_MAX && x != S_INF_MIN && !S_isnan(x)) {
    sum = 0;
    if (-1 < x && x < 1) {
      do {
        step = (s_pow(-1, n) * s_pow(x, 1 + 2 * n)) / (1 + 2 * n);
        sum += step;
        n++;
      } while (s_fabs((double)step) > 0.000001);
    } else if (x > 1 || x < -1) {
      do {
        step = (s_pow(-1, n) * s_pow(x, -1 - 2 * n)) / (1 + 2 * n);
        sum += step;
        n++;
      } while (s_fabs((double)step) > 0.000001);
      sum = S_PI * s_sqrt(x * x) / (2 * x) - sum;
    } else if (x == 1) {
      sum = S_PI / 4;
    } else if (x == -1) {
      sum = -S_PI / 4;
    }
  } else if (x == S_INF_MAX) {
    sum = S_PI / 2;
  } else if (x == S_INF_MIN) {
    sum = -S_PI / 2;
  }
  return sum;
}

long double s_asin(double x) {
  long double res = 0;
  if (-1 < x && x < 1 && x != 0) res = s_atan(x / s_sqrt(1 - x * x));
  if (x == -1) res = -S_PI / 2;
  if (x == 1) res = S_PI / 2;
  if (x > 1 || x < -1) res = S_NAN;
  if (S_isnan(x)) res = S_NAN;
  return res;
}

long double s_acos(double x) {
  long double res = 0;
  if (0 < x && x < 1) res = s_atan(s_sqrt(1 - x * x) / x);
  if (-1 < x && x < 0) res = S_PI + s_atan(s_sqrt(1 - x * x) / x);
  if (x == -1) res = S_PI;
  if (x > 1 || x < -1) res = S_NAN;
  if (x == 0) res = S_PI / 2;
  if (S_isnan(x)) res = S_NAN;
  return res;
}

long double s_tan(double x) { return s_sin(x) / s_cos(x); }
