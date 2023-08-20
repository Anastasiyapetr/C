#include "decimal.h"

int getbit(decimal value, int n) {
  int num = n % 32;
  int x = 0;
  if (n >= 0 && n <= 31) {
    value.bits[0] >>= num;
    value.bits[0] <<= 31;
    x = value.bits[0];
  } else if (n >= 32 && n <= 63) {
    value.bits[1] >>= num;
    value.bits[1] <<= 31;
    x = value.bits[1];
  } else if (n >= 64 && n <= 95) {
    value.bits[2] >>= num;
    value.bits[2] <<= 31;
    x = value.bits[2];
  }
  return x == 0 ? 0 : 1;
}

int getbitLongDecimal(long_decimal value, int n) {
  int num = n % 32, index = n / 32, x = 0;
  unsigned int mask = 1u;
  mask = mask << num;
  x = value.bits[index] & mask;
  return x == 0 ? 0 : 1;
}

void setbitLongDecimal(long_decimal *value, int n, int num) {
  unsigned int mask = 1u << n % 32;
  if (!num) {
    value->bits[n / 32] = value->bits[n / 32] & (~mask);
  } else {
    value->bits[n / 32] = value->bits[n / 32] | (mask);
  }
}

void setbit(decimal *value, int n, int num) {
  unsigned int mask = 1u;
  if (!num) {
    if (n >= 0 && n <= 31) {
      value->bits[0] = value->bits[0] & (~(mask << n));
    } else if (n >= 32 && n <= 63) {
      value->bits[1] = value->bits[1] & (~(mask << (n - 32)));
    } else if (n >= 64 && n <= 95) {
      value->bits[2] = value->bits[2] & (~(mask << (n - 64)));
    }
  } else {
    if (n >= 0 && n <= 31) {
      value->bits[0] = value->bits[0] | (mask << n);
    } else if (n >= 32 && n <= 63) {
      value->bits[1] = value->bits[1] | (mask << (n - 32));
    } else if (n >= 64 && n <= 95) {
      value->bits[2] = value->bits[2] | (mask << (n - 64));
    }
  }
}

int getSign(decimal value) {
  int x = 0;
  x = value.bits[3] >> 31;
  x = x & 1;
  return x == 0 ? 0 : 1;
}

void changeSign(decimal *value) {
  value->bits[3] = value->bits[3] ^ (1u << 31);
}

void changeScale(decimal *value, int new_scale) {
  int sign = getSign(*value);
  value->bits[3] = *((unsigned int *)&new_scale);
  value->bits[3] <<= 16;
  if (sign) {
    changeSign(value);
  }
}

void setZeroBits(decimal *value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}

void setZeroBitsLongDecimal(long_decimal *value) {
  for (int i = 0; i < 6; i++) {
    value->bits[i] = 0;
  }
}

int getScale(decimal value) {
  int x = value.bits[3] >> 16;
  x = x & 0x1F;
  return x;
}

int decimal_is_zero(decimal value) {
  int result = 1;
  for (int i = 0; i < 3; i++) {
    if (value.bits[i] != 0) {
      result = 0;
    }
  }
  return result;
}

int checkCorrectNumber(decimal value) {
  int result = 0, scale = getScale(value);
  int mask_1 = 0xFFFF0000, fbits_1 = value.bits[3] << 16;
  int mask_2 = 0x3FF, fbits_2 = value.bits[3] >> 21;
  for (int i = 0; i < 3; i++) {
    long long tmp = value.bits[i];
    if (tmp > MAX_UINT) {
      result = 1;
    }
  }
  if (last1Bit(value) > 95) {
    result = 1;
  }
  if (value.bits[3] > MAX_SCALE_FACTOR) {
    result = 1;
  }
  if (((fbits_1 & mask_1) != 0) || ((fbits_2 & mask_2) != 0)) {
    result = 1;
  }
  if (scale > 28) {
    result = 1;
  }
  return result;
}

// 1 - VALUE_1 < VALUE_2; 0 - VALUE_1 > VALUE_2; -1 - VALUE_1 = VALUE_2
int compareDecimal(decimal value_1, decimal value_2) {
  int flag = 1, eq = 1, check = 0;
  long_decimal result = {{0, 0, 0, 0, 0, 0}};
  EqualScale(value_1, value_2, &result);
  int scale_1 = getScale(value_1), scale_2 = getScale(value_2);
  int znak = getSign(value_1);
  if (scale_1 > scale_2) {
    long_decimal value_one = {{0, 0, 0, 0, 0, 0}};
    for (int i = 0; i <= 2; i++) {
      value_one.bits[i] = value_1.bits[i];
    }
    for (int i = 5; i >= 0 && !check; i--) {
      if ((value_one.bits[i] > result.bits[i] && !znak) ||
          (value_one.bits[i] < result.bits[i] && znak)) {
        flag = 0;
        check = 1;
      } else if ((result.bits[i] > value_one.bits[i] && !znak) ||
                 (result.bits[i] < value_one.bits[i] && znak)) {
        flag = 1;
        check = 1;
      }
    }
    for (int i = 5; i >= 0; i--) {
      if (value_one.bits[i] != result.bits[i]) {
        eq = 0;
      }
    }
  } else {
    long_decimal value_two = {{0, 0, 0, 0, 0, 0}};
    for (int i = 0; i <= 2; i++) {
      value_two.bits[i] = value_2.bits[i];
    }
    for (int i = 5; i >= 0 && !check; i--) {
      if ((result.bits[i] > value_two.bits[i] && !znak) ||
          (value_two.bits[i] > result.bits[i] && znak)) {
        flag = 0;
        check = 1;
      } else if ((value_two.bits[i] > result.bits[i] && !znak) ||
                 (value_two.bits[i] < result.bits[i] && znak)) {
        flag = 1;
        check = 1;
      }
    }
    for (int i = 5; i >= 0; i--) {
      if (value_two.bits[i] != result.bits[i]) {
        eq = 0;
      }
    }
  }
  if (eq) flag = -1;
  return flag;
}

void EqualScale(decimal value_1, decimal value_2, long_decimal *result) {
  setZeroBitsLongDecimal(result);
  long_decimal value_one = {{0, 0, 0, 0, 0, 0}},
               value_two = {{0, 0, 0, 0, 0, 0}};
  for (int i = 0; i <= 2; i++) {
    value_one.bits[i] = value_1.bits[i];
    value_two.bits[i] = value_2.bits[i];
  }
  int scale_1 = getScale(value_1), scale_2 = getScale(value_2);
  if (scale_1 > scale_2) {
    addLongDecimal(value_two, *result, result);
    while (scale_1 != scale_2) {
      int count = 9;
      while (count > 0) {
        addLongDecimal(value_two, *result, result);
        count--;
      }
      scale_2++;
      for (int i = 0; i < 5; i++) {
        value_two.bits[i] = result->bits[i];
      }
    }
  } else {
    addLongDecimal(value_one, *result, result);
    while (scale_1 != scale_2) {
      int count = 9;
      while (count > 0) {
        addLongDecimal(value_one, *result, result);
        count--;
      }
      scale_1++;
      for (int i = 0; i < 5; i++) {
        value_one.bits[i] = result->bits[i];
      }
    }
  }
}

void addLongDecimal(long_decimal value_1, long_decimal value_2,
                    long_decimal *result) {
  memset(result, 0, 6 * 4);
  int tmp = 0;
  for (int i = 0; i < 192; i++) {
    int x = getbitLongDecimal(value_1, i) + getbitLongDecimal(value_2, i) + tmp;
    switch (x) {
      case 0:
        setbitLongDecimal(result, i, 0);
        tmp = 0;
        break;
      case 1:
        setbitLongDecimal(result, i, 1);
        tmp = 0;
        break;
      case 2:
        setbitLongDecimal(result, i, 0);
        tmp = 1;
        break;
      case 3:
        setbitLongDecimal(result, i, 1);
        tmp = 1;
        break;
    }
  }
}
////////////////////////////Comparison Operators////////////////////////

int is_less(decimal value_1, decimal value_2) {
  int result = 1, check_value_1 = checkCorrectNumber(value_1),
      check_value_2 = checkCorrectNumber(value_2);
  int znak_1 = getSign(value_1), znak_2 = getSign(value_2);
  int scale_1 = getScale(value_1), scale_2 = getScale(value_2);
  int zero_1 = decimal_is_zero(value_1), zero_2 = decimal_is_zero(value_2);
  if (check_value_1 || check_value_2) {
    result = 0;
  } else {
    if (znak_1 < znak_2) {
      result = 0;
    } else if (znak_1 > znak_2) {
      result = 1;
    } else {
      if (zero_1 && !zero_2) {
        result = 1;
      } else if (!zero_1 && zero_2) {
        result = 0;
      } else if (scale_1 != scale_2) {
        if (compareDecimal(value_1, value_2) != 1) {
          result = 0;
        } else {
          result = 1;
        }
      } else {
        if ((value_1.bits[2] > value_2.bits[2] && !znak_1) ||
            (value_1.bits[2] < value_2.bits[2] && znak_1)) {
          result = 0;
        } else if ((value_1.bits[2] == value_2.bits[2]) &&
                   ((value_1.bits[1] > value_2.bits[1] && !znak_1) ||
                    (value_1.bits[1] < value_2.bits[1] && znak_1))) {
          result = 0;
        } else if ((value_1.bits[2] == value_2.bits[2] &&
                    value_1.bits[1] == value_2.bits[1]) &&
                   ((value_1.bits[0] > value_2.bits[0] && !znak_1) ||
                    (value_1.bits[0] < value_2.bits[0] && znak_1))) {
          result = 0;
        } else if (value_1.bits[2] == value_2.bits[2] &&
                   value_1.bits[1] == value_2.bits[1] &&
                   value_1.bits[0] == value_2.bits[0]) {
          result = 0;
        }
      }
    }
  }
  return result;
}

int is_less_or_equal(decimal value_1, decimal value_2) {
  int result = 1, check_value_1 = checkCorrectNumber(value_1),
      check_value_2 = checkCorrectNumber(value_2);
  if (check_value_1 || check_value_2) {
    result = 0;
  } else {
    result = (is_less(value_1, value_2) || is_equal(value_1, value_2));
  }
  return result;
}

int is_equal(decimal value_1, decimal value_2) {
  int result = 1, check_value_1 = checkCorrectNumber(value_1),
      check_value_2 = checkCorrectNumber(value_2);
  if (check_value_1 || check_value_2) {
    result = 0;
  } else {
    int znak_1 = getSign(value_1), znak_2 = getSign(value_2);
    int scale_1 = getScale(value_1), scale_2 = getScale(value_2);
    if (znak_1 != znak_2) {
      result = 0;
    }
    if (scale_1 != scale_2) {
      if (compareDecimal(value_1, value_2) != -1) {
        result = 0;
      }
    } else {
      for (int i = 0; i < 3; i++) {
        if (value_1.bits[i] != value_2.bits[i]) {
          result = 0;
        }
      }
    }
  }
  return result;
}

int is_greater(decimal value_1, decimal value_2) {
  int result = 1, check_value_1 = checkCorrectNumber(value_1),
      check_value_2 = checkCorrectNumber(value_2);
  if (check_value_1 || check_value_2) {
    result = 0;
  } else {
    result = !(is_less(value_1, value_2) || is_equal(value_1, value_2));
  }
  return result;
}

int is_greater_or_equal(decimal value_1, decimal value_2) {
  int result = 1, check_value_1 = checkCorrectNumber(value_1),
      check_value_2 = checkCorrectNumber(value_2);
  if (check_value_1 || check_value_2) {
    result = 0;
  } else {
    result = (is_greater(value_1, value_2) || is_equal(value_1, value_2));
  }
  return result;
}

int is_not_equal(decimal value_1, decimal value_2) {
  int result = 1, check_value_1 = checkCorrectNumber(value_1),
      check_value_2 = checkCorrectNumber(value_2);
  if (check_value_1 || check_value_2) {
    result = 0;
  } else {
    int znak_1 = getSign(value_1), znak_2 = getSign(value_2);
    int scale_1 = getScale(value_1), scale_2 = getScale(value_2);
    if (scale_1 != scale_2) {
      if (compareDecimal(value_1, value_2) == -1) {
        result = 0;
      }
    } else {
      if (value_1.bits[0] == value_2.bits[0] &&
          value_1.bits[1] == value_2.bits[1] &&
          value_1.bits[2] == value_2.bits[2] && znak_1 == znak_2) {
        result = 0;
      }
    }
  }
  return result;
}
/////////////////////Convertors and parsers/////////////////////////////

void findSignificantFigures(float src, int *mantissa, int *exp) {
  int znak = src < 0 ? 1 : 0;
  if (znak) src = -src;

  char str_1[100] = {'\0'}, str_2[100] = {'\0'};

  sprintf(str_1, "%.6e", src);

  size_t len = strlen(str_1);
  int j = 0;
  for (size_t i = 0; i < len; i++) {
    if (str_1[i] == 'e') {
      str_2[j] = '\0';
      break;
    }
    if (str_1[i] != '.') {
      str_2[j] = str_1[i];
      j++;
    }
  }
  int tmp_2 = 0;
  sscanf(str_2, "%d", mantissa);
  sscanf(str_1, "%d.%de%d", &tmp_2, &tmp_2, exp);
}

int from_float_to_decimal(float src, decimal *dst) {
  int flag = 0;
  if (dst != NULL) {
    setZeroBits(dst);
  } else {
    flag = 1;
  }
  if (!flag) {
    if ((src != src) || (src == INFINITY) || (src == -INFINITY) ||
        (fabsf(src) > 7.922816e28) || (fabsf(src) < 1e-28)) {
      if (fabsf(src) != 0) {
        flag = 1;
      }
      if (src == -INFINITY) {
        changeSign(dst);
      }
    } else {
      int znak = src < 0 ? 1 : 0;

      int mantissa = 0, exp = 0;
      findSignificantFigures(src, &mantissa, &exp);

      if (exp < -6) {
        mantissa = 0, exp = 6;
        dst->bits[0] = abs(mantissa);
        changeScale(dst, exp);
        if (znak) changeSign(dst);
      } else {
        dst->bits[0] = abs(mantissa);
        exp = 6 - exp;
        if (exp < 0) exp = 0;
        if (znak) changeSign(dst);
        changeScale(dst, exp);
      }
    }
  }
  return flag;
}

int from_decimal_to_float(decimal src, float *dst) {
  int flag = 0;
  double tmp = 0.0;
  if (dst == NULL || checkCorrectNumber(src)) {
    flag = 1;
  } else {
    int znak = getSign(src);
    int scale = getScale(src);

    for (int i = 0; i < 96; i++) {
      tmp *= 2;
      if (getbit(src, 95 - i)) {
        tmp++;
      }
    }
    while (scale != 0) {
      tmp /= 10;
      scale--;
    }
    if (znak) tmp *= -1;
    *dst = tmp;
  }
  return flag;
}

int from_int_to_decimal(int src, decimal *dst) {
  int flag = 0;
  if (dst == NULL) {
    flag = 1;
  } else {
    setZeroBits(dst);
    int znak = src < 0 ? 1 : 0;
    if (znak) {
      unsigned int tmp = 0;
      tmp = src;
      tmp = -tmp;
      dst->bits[0] = tmp;
    } else {
      dst->bits[0] = src;
    }
    if (znak) {
      changeSign(dst);
    }
  }
  return flag;
}

int from_decimal_to_int(decimal src, int *dst) {
  int flag = 0;
  if (checkCorrectNumber(src) || dst == NULL) {
    flag = 1;
  } else {
    int znak = getSign(src);
    decimal tmp = {{0, 0, 0, 0}};
    if ((!znak && last1Bit(src) > 30) || (znak && src.bits[0] > 2147483648)) {
      flag = 1;
    } else {
      *dst = 0;
      truncate(src, &tmp);
      *dst = tmp.bits[0];
      if (znak) {
        *dst *= -1;
      }
    }
  }
  return flag;
}

//////////////////////Functions for arithmetic/////////////////////////////////
int leftShift(decimal *value, int n) {  //сдвиг влево
  int res = 0;
  while (n--) {
    int bit_0_bits = getbit(*value, 31);
    int bit_1_bits = getbit(*value, 63);
    int bit_95 = getbit(*value, 95);
    if (bit_95 == 1) res = 1;
    value->bits[0] <<= 1;
    value->bits[1] <<= 1;
    value->bits[2] <<= 1;
    setbit(value, 32, bit_0_bits);
    setbit(value, 64, bit_1_bits);
  }
  return res;
}

void leftShiftLongDecimal(long_decimal *value, int n) {
  while (n--) {
    int bit_0_bits = getbitLongDecimal(*value, 31);
    int bit_1_bits = getbitLongDecimal(*value, 63);
    int bit_2_bits = getbitLongDecimal(*value, 95);
    int bit_3_bits = getbitLongDecimal(*value, 127);
    int bit_4_bits = getbitLongDecimal(*value, 159);
    value->bits[0] <<= 1;
    value->bits[1] <<= 1;
    value->bits[2] <<= 1;
    value->bits[3] <<= 1;
    value->bits[4] <<= 1;
    value->bits[5] <<= 1;
    setbitLongDecimal(value, 32, bit_0_bits);
    setbitLongDecimal(value, 64, bit_1_bits);
    setbitLongDecimal(value, 96, bit_2_bits);
    setbitLongDecimal(value, 128, bit_3_bits);
    setbitLongDecimal(value, 160, bit_4_bits);
  }
}

void subLongDecimal(long_decimal value_1, long_decimal value_2,
                    long_decimal *result) {
  memset(result, 0, 6 * 4);
  int tmp = 0;
  for (int i = 0; i < 192; i++) {
    int x = getbitLongDecimal(value_1, i) - getbitLongDecimal(value_2, i) - tmp;
    switch (x) {
      case 0:
        setbitLongDecimal(result, i, x);
        tmp = 0;
        break;
      case 1:
        setbitLongDecimal(result, i, x);
        tmp = 0;
        break;
      case -1:
        setbitLongDecimal(result, i, x);
        tmp = 1;
        break;
    }
  }
}

void mulLongDecimal(long_decimal value_1, long_decimal value_2,
                    long_decimal *result) {
  memset(result, 0, 24);
  long_decimal res_tmp = {{0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 192; i++) {
    for (int j = 0; j < 192; j++) {
      int x = getbitLongDecimal(value_1, i) * getbitLongDecimal(value_2, j);
      setbitLongDecimal(&res_tmp, j, x);
    }
    leftShiftLongDecimal(&res_tmp, i);
    addLongDecimal(*result, res_tmp, result);
  }
}

void rightShiftLongDecimal(long_decimal *value, int n) {
  if (n < 0) n *= -1;
  while (n--) {
    int bit_1_bits = getbitLongDecimal(*value, 32);
    int bit_2_bits = getbitLongDecimal(*value, 64);
    int bit_3_bits = getbitLongDecimal(*value, 96);
    int bit_4_bits = getbitLongDecimal(*value, 128);
    int bit_5_bits = getbitLongDecimal(*value, 160);
    value->bits[0] >>= 1;
    value->bits[1] >>= 1;
    value->bits[2] >>= 1;
    value->bits[3] >>= 1;
    value->bits[4] >>= 1;
    value->bits[5] >>= 1;
    setbitLongDecimal(value, 31, bit_1_bits);
    setbitLongDecimal(value, 63, bit_2_bits);
    setbitLongDecimal(value, 95, bit_3_bits);
    setbitLongDecimal(value, 127, bit_4_bits);
    setbitLongDecimal(value, 159, bit_5_bits);
  }
}

int last1Bit(decimal value) {
  int last = 95;
  for (; last >= 0 && !(getbit(value, last)); last--)
    ;
  return last;
}

int last1BitLongDecimal(long_decimal value) {
  int last = 191;
  for (; last >= 0 && !(getbitLongDecimal(value, last)); last--)
    ;
  return last;
}

void castOneScale(long_decimal *v1, long_decimal *v2, decimal *result,
                  int scale1, int scale2) {
  if (scale1 > scale2) {
    changeScale(result, scale1);
    long_decimal tmp = {{pow(10, scale1 - scale2), 0, 0, 0, 0, 0}};
    mulLongDecimal(*v2, tmp, v2);
  } else if (scale1 < scale2) {
    changeScale(result, scale2);
    long_decimal tmp = {{pow(10, scale2 - scale1), 0, 0, 0, 0, 0}};
    mulLongDecimal(*v1, tmp, v1);
  } else {
    changeScale(result, scale1);
  }
}

void bankRounding(long_decimal *res_tmp, int *scale_res) {
  int last_digit = 0;
  while ((*scale_res &&
          (res_tmp->bits[5] || res_tmp->bits[4] || res_tmp->bits[3])) ||
         *scale_res > 28) {
    last_digit = lastDigitForRound(*res_tmp);
    divTenLongDecimal(*res_tmp, res_tmp);
    *scale_res = *scale_res - 1;
  }
  if (last_digit > 5) {
    long_decimal tmp_one = {{1, 0, 0, 0, 0, 0}};
    addLongDecimal(*res_tmp, tmp_one, res_tmp);
  } else if (last_digit == 5) {
    int last_digit_now = lastDigitForRound(*res_tmp);
    if (last_digit_now % 2 != 0) {
      long_decimal tmp_one = {{1, 0, 0, 0, 0, 0}};
      addLongDecimal(*res_tmp, tmp_one, res_tmp);
    }
  }
}

int lastDigitForRound(long_decimal value) {
  unsigned long long buf = 0;
  unsigned mod = 0;
  for (int i = 5; i >= 0; i--) {
    mod = (buf + value.bits[i]) % 10;
    buf = mod;
    buf = buf << 32;
  }
  return mod;
}

void divTenLongDecimal(long_decimal value, long_decimal *result) {
  unsigned long long buf = 0ull;
  unsigned long long div_buf = 0ull;
  unsigned mod = 0;
  for (int i = 5; i >= 0; i--) {
    mod = (buf + value.bits[i]) % 10;
    div_buf = ((buf + value.bits[i]) / 10);
    result->bits[i] = (unsigned)div_buf;
    buf = mod;
    buf = buf << 32;
  }
}

int is_greaterLongDecimal(long_decimal v1, long_decimal v2) {
  int result = 0;
  int flag = 0;
  for (int i = 5; i >= 0; i--) {
    if (v1.bits[i] > v2.bits[i] && !flag) {
      flag = 1;
      result = 1;
    } else if (v1.bits[i] < v2.bits[i] && !flag) {
      flag = 1;
      result = 0;
    }
  }
  return result;  // 1 - в1 больше в2, 0 меньше или равно
}

int is_eqLongDecimal(long_decimal v1, long_decimal v2) {
  int result = 1;
  int flag = 0;
  for (int i = 5; i >= 0 && flag == 0; i--) {
    if (v1.bits[i] != v2.bits[i]) {
      flag++;
    }
  }
  if (flag != 0) result = 0;
  return result;  // 1 - в1 == в2, 0 не равны
}

int longDecimalIsNotZero(long_decimal value) {
  int result = 1;
  for (int i = 0; i < 6 && result == 1; i++) {
    if (value.bits[i] != 0) {
      result = 0;
    }
  }
  return result;  // 0 - не равно 0, 1 - равно
}

///////////////////////////////////////Arithmetic/////////////////////////////////////////////////

int add(decimal value_1, decimal value_2, decimal *result) {
  memset(result, 0, 16);
  int res = 0;
  int sign1 = getSign(value_1), sign2 = getSign(value_2);
  int scale1 = getScale(value_1), scale2 = getScale(value_2);
  long_decimal v1 = {{0}};
  long_decimal v2 = {{0}};
  long_decimal res_tmp = {{0}};
  for (int i = 0; i < 3; i++) {
    v1.bits[i] = value_1.bits[i];
    v2.bits[i] = value_2.bits[i];
  }
  castOneScale(&v1, &v2, result, scale1, scale2);
  if (sign1 + sign2 == 1) {
    if (sign1 == 1) {
      changeSign(&value_1);
      if (is_less(value_1, value_2)) {
        subLongDecimal(v2, v1, &res_tmp);
      } else {
        subLongDecimal(v1, v2, &res_tmp);
        changeSign(result);
      }
    } else {
      changeSign(&value_2);
      if (is_less(value_1, value_2)) {
        subLongDecimal(v2, v1, &res_tmp);
        changeSign(result);
      } else {
        subLongDecimal(v1, v2, &res_tmp);
      }
    }
  } else {
    if (sign1 + sign2 == 2) changeSign(result);
    addLongDecimal(v1, v2, &res_tmp);
  }
  int scale_res = getScale(*result);
  if (res_tmp.bits[5] || res_tmp.bits[4] || res_tmp.bits[3])
    bankRounding(&res_tmp, &scale_res);
  if (!(res_tmp.bits[5] || res_tmp.bits[4] || res_tmp.bits[3])) {
    for (int i = 0; i < 3; i++) {
      result->bits[i] = res_tmp.bits[i];
    }
    changeScale(result, scale_res);
  } else {
    res = 1;
    if (sign1 + sign2 == 2) res = 2;
  }
  return res;
}

int sub(decimal value_1, decimal value_2, decimal *result) {
  memset(result, 0, 16);
  negate(value_2, &value_2);
  return add(value_1, value_2, result);
}

int mul(decimal value_1, decimal value_2, decimal *result) {
  memset(result, 0, 16);
  int res = 0;
  int sign = getSign(value_1) + getSign(value_2);
  if (sign == 2) sign = 0;
  long_decimal v1 = {{0}};
  long_decimal v2 = {{0}};
  long_decimal res_tmp = {{0}};
  for (int i = 0; i < 3; i++) {
    v1.bits[i] = value_1.bits[i];
    v2.bits[i] = value_2.bits[i];
  }
  mulLongDecimal(v1, v2, &res_tmp);
  int scale_res = getScale(value_1) + getScale(value_2);
  if (res_tmp.bits[5] || res_tmp.bits[4] || res_tmp.bits[3])
    bankRounding(&res_tmp, &scale_res);
  if (!(res_tmp.bits[5] || res_tmp.bits[4] || res_tmp.bits[3])) {
    for (int i = 0; i < 3; i++) {
      result->bits[i] = res_tmp.bits[i];
    }
    changeScale(result, scale_res);
    if (sign == 1) changeSign(result);
  } else {
    res = 1;
    if (sign == 1) res = 2;
  }
  if (result->bits[0] == 0 && result->bits[1] == 0 && result->bits[2] == 0)
    result->bits[3] = 0;
  return res;
}

int s_div(decimal value_1, decimal value_2, decimal *result) {
  memset(result, 0, 16);
  int res = 0;
  if (decimal_is_zero(value_2)) {
    res = 3;
  } else if (decimal_is_zero(value_1)) {
    memset(result, 0, 16);
  } else {
    int sign = getSign(value_1) + getSign(value_2);
    if (sign == 2) sign = 0;
    int scale2 = getScale(value_2);
    long_decimal v1 = {{0}};
    long_decimal v2 = {{0}};
    long_decimal res_tmp = {{0}};
    for (int i = 0; i < 3; i++) {
      v1.bits[i] = value_1.bits[i];
      v2.bits[i] = value_2.bits[i];
    }
    long_decimal tmp_ten = {{10, 0, 0, 0, 0, 0}};
    long_decimal tmp_storage = {{0, 0, 0, 0, 0, 0}};
    int scale_res = getScale(value_1);
    ;
    while (is_greaterLongDecimal(v1, v2) == 0 && scale_res < 29) {
      mulLongDecimal(v1, tmp_ten, &v1);
      scale_res++;
    }
    int last_bit_v1 = last1BitLongDecimal(v1);
    int last_bit_v2 = last1BitLongDecimal(v2);
    int sdvig = last_bit_v1 - last_bit_v2;
    leftShiftLongDecimal(&v2, sdvig);
    while ((longDecimalIsNotZero(v1) == 0 ||
            last1BitLongDecimal(v2) >= last_bit_v2) &&
           res_tmp.bits[5] == 0) {
      if (is_greaterLongDecimal(v1, v2) ||
          is_eqLongDecimal(v1, v2)) {  // if v1 > v2 || v1 == v2
        setbitLongDecimal(&res_tmp, 0, 1);
        leftShiftLongDecimal(&res_tmp, 1);
        subLongDecimal(v1, v2, &v1);
        rightShiftLongDecimal(&v2, 1);
      } else if (last1BitLongDecimal(v2) == last_bit_v2 &&
                 longDecimalIsNotZero(v1) == 0) {
        mulLongDecimal(v1, tmp_ten, &v1);
        sdvig = last1BitLongDecimal(v1) - last1BitLongDecimal(v2);
        if (sdvig > 0) {
          leftShiftLongDecimal(&v2, sdvig);
          addLongDecimal(tmp_storage, res_tmp, &tmp_storage);
          mulLongDecimal(tmp_storage, tmp_ten, &tmp_storage);
          memset(res_tmp.bits, 0, 24);
        }
        scale_res++;
      } else if (longDecimalIsNotZero(v1) &&
                 last1BitLongDecimal(v2) >= last_bit_v2 &&
                 getbitLongDecimal(res_tmp, 1) == 1) {
        leftShiftLongDecimal(&res_tmp, 1);
        rightShiftLongDecimal(&v2, 1);
      } else {
        setbitLongDecimal(&res_tmp, 0, 0);
        leftShiftLongDecimal(&res_tmp, 1);
        rightShiftLongDecimal(&v2, 1);
      }
    }
    rightShiftLongDecimal(&res_tmp, 1);
    addLongDecimal(tmp_storage, res_tmp, &res_tmp);
    while (scale2--) mulLongDecimal(res_tmp, tmp_ten, &res_tmp);
    if (res_tmp.bits[5] || res_tmp.bits[4] || res_tmp.bits[3])
      bankRounding(&res_tmp, &scale_res);
    if (!(res_tmp.bits[5] || res_tmp.bits[4] || res_tmp.bits[3])) {
      for (int i = 0; i < 3; i++) {
        result->bits[i] = res_tmp.bits[i];
      }
      changeScale(result, scale_res);
      if (sign == 1) changeSign(result);
    } else {
      res = 1;
      if (sign == 1) res = 2;
    }
  }
  if (result->bits[0] == 0 && result->bits[1] == 0 && result->bits[2] == 0)
    result->bits[3] = 0;
  return res;
}

int mod(decimal value_1, decimal value_2, decimal *result) {
  memset(result, 0, 16);
  int res = 0;
  int sign1 = getSign(value_1), sign2 = getSign(value_2);
  if (sign1 == 1) changeSign(&value_1);
  if (sign2 == 1) changeSign(&value_2);
  decimal tmp_v1 = {
      {value_1.bits[0], value_1.bits[1], value_1.bits[2], value_1.bits[3]}};
  decimal tmp_v2 = {
      {value_2.bits[0], value_2.bits[1], value_2.bits[2], value_2.bits[3]}};
  res = s_div(value_1, value_2, result);
  truncate(*result, result);
  mul(*result, tmp_v2, &tmp_v2);
  memset(result, 0, 16);
  sub(tmp_v1, tmp_v2, result);
  if (sign1 == 1) changeSign(result);
  if (result->bits[0] == 0 && result->bits[1] == 0 && result->bits[2] == 0)
    result->bits[3] = 0;
  return res;
}

////////////////////////Another functions///////////////////////////////////
int s_floor(decimal value, decimal *result) {
  int flag = 0, check_dec = checkCorrectNumber(value);
  if (result == NULL || check_dec) {
    flag = 1;
  } else {
    int scale = getScale(value);
    int sign = getSign(value);
    if (scale > 0) {
      int is_int = 0;
      decimal tmp = {{0, 0, 0, 0}};
      decimal zero_1 = {{0, 0, 0, 0}};
      decimal zero_2 = {{0, 0, 0, 2147483648}};
      truncate(value, &tmp);
      sub(value, tmp, &tmp);
      if (is_equal(tmp, zero_1) || is_equal(tmp, zero_2)) {
        is_int = 1;
      }
      truncate(value, result);
      if (sign && !is_int) {
        decimal one = {{1, 0, 0, 2147483648}};
        add(*result, one, result);
      }
    } else {
      for (int i = 0; i < 4; i++) {
        result->bits[i] = value.bits[i];
      }
    }
  }
  return flag;
}

int s_round(decimal value, decimal *result) {
  int flag = 0;
  int scale = getScale(value);
  int sign = getSign(value);
  if (scale > 0) {
    if (sign) changeSign(&value);
    decimal tmp = {{0, 0, 0, 0}};
    decimal one = {{1, 0, 0, 0}};
    for (int i = 0; i < 3; i++) tmp.bits[i] = value.bits[i];

    for (; scale > 1; scale--) {
      divTen(tmp, &tmp);
    }

    int frac = mod_int(tmp, 10);
    truncate(value, result);

    if (frac >= 5) {
      flag = add(*result, one, result);
    }
    if (sign) changeSign(result);
    changeScale(result, 0);
  } else {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
  }
  return flag;
}

int truncate(decimal value, decimal *result) {
  int flag = 0, check_dec = checkCorrectNumber(value);
  if (result == NULL || check_dec) {
    flag = 1;
  } else {
    setZeroBits(result);
    for (int i = 0; i < 3; i++) {
      result->bits[i] = value.bits[i];
    }
    int scale = getScale(value);
    int sign = getSign(value);
    if (scale > 0) {
      while (scale != 0) {
        divTen(*result, result);
        scale--;
      }
    }
    changeScale(result, 0);
    if (sign) changeSign(result);
  }
  return flag;
}

int mod_int(decimal value, int integer) {
  unsigned long long buf = 0ull, mod = 0ull;
  for (int i = 2; i >= 0; i--) {
    mod = (buf + value.bits[i]) % integer;
    buf = mod << 32;
  }
  return mod;
}

void divTen(decimal value_1, decimal *result) {
  decimal ten = {{10, 0, 0, 0}};
  decimal copy_value_1 = {{0, 0, 0, 0}};
  decimal zero = {{0, 0, 0, 0}};
  for (int i = 0; i < 3; i++) {
    copy_value_1.bits[i] = value_1.bits[i];
  }
  setZeroBits(result);
  if (!is_less(copy_value_1, ten)) {
    int bit_v1 = last1Bit(value_1);
    decimal tmp_1 = {{0, 0, 0, 0}}, tmp_2 = {{0, 0, 0, 0}};

    while (is_less(tmp_2, copy_value_1)) {
      int flag = 0;
      leftShift(result, 1);
      while (is_less(tmp_1, ten) && !flag) {
        int k = getbit(copy_value_1, bit_v1);
        leftShift(&tmp_1, 1);
        setbit(&tmp_1, 0, k);
        leftShift(&tmp_2, 1);
        setbit(&tmp_2, 0, k);
        bit_v1--;
        if (is_not_equal(*result, zero)) {
          flag = 1;
        }
      }

      if (is_less(tmp_1, ten)) {
        setbit(result, 0, 0);
      } else {
        setbit(result, 0, 1);
        sub(tmp_1, ten, &tmp_1);
      }
    }
  }
}

int negate(decimal value, decimal *result) {
  int flag = 0;
  int check_dec = checkCorrectNumber(value);
  if (result == NULL || check_dec) {
    flag = 1;
  } else {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
    changeSign(result);
  }
  return flag;
}
