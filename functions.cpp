#include <stdexcept>
#include <limits>
#include <cstdint>

#include "functions.h"

int largest(int a, int b, int c) {
  int m = a;
  if (b > m) m = b;
  if (c > m) m = c;
  return m;
}

bool sum_is_even(int a, int b) {
  int ap = a % 2;
  if (ap < 0) ap += 2;
  int bp = b % 2;
  if (bp < 0) bp += 2;
  return ap == bp;
}

int boxes_needed(int apples) {
  if (apples <= 0) return 0;
  int q = apples / 20;
  int r = apples % 20;
  return q + (r != 0);
}

bool smarter_section(int A_correct, int A_total, int B_correct, int B_total) {
  if (A_total <= 0 || B_total <= 0) {
    throw std::invalid_argument("totals must be positive");
  }
  if (A_correct < 0 || B_correct < 0) {
    throw std::invalid_argument("correct must be non-negative");
  }
  if (A_correct > A_total || B_correct > B_total) {
    throw std::invalid_argument("correct cannot exceed total");
  }

  int64_t left = static_cast<int64_t>(A_correct) * static_cast<int64_t>(B_total);
  int64_t right = static_cast<int64_t>(B_correct) * static_cast<int64_t>(A_total);
  return left > right;
}

bool good_dinner(int pizzas, bool is_weekend) {
  if (pizzas < 10) return false;
  if (is_weekend) return true;
  return pizzas <= 20;
}

int32_t sum_between(int32_t low, int32_t high) {
  if (low > high) {
    throw std::invalid_argument("low and high are out of order");
  }

  int64_t n = static_cast<int64_t>(high) - static_cast<int64_t>(low) + 1;
  int64_t endpoints = static_cast<int64_t>(low) + static_cast<int64_t>(high);

  int64_t sum;
  if ((n % 2) == 0) {
    sum = (n / 2) * endpoints;
  } else {
    sum = n * (endpoints / 2);
  }

  if (sum < static_cast<int64_t>(std::numeric_limits<int32_t>::min()) ||
      sum > static_cast<int64_t>(std::numeric_limits<int32_t>::max())) {
    throw std::overflow_error("sum overflows int32_t");
  }

  return static_cast<int32_t>(sum);
}

int64_t product(int64_t a, int64_t b) {
  int64_t max = std::numeric_limits<int64_t>::max();
  int64_t min = std::numeric_limits<int64_t>::min();

  if (a == 0 || b == 0) return 0;

  if (a == -1) {
    if (b == min) throw std::overflow_error("product overflows int64_t");
    return -b;
  }
  if (b == -1) {
    if (a == min) throw std::overflow_error("product overflows int64_t");
    return -a;
  }

  if (a > 0) {
    if (b > 0) {
      if (a > max / b) throw std::overflow_error("product overflows int64_t");
    } else {
      if (b < min / a) throw std::overflow_error("product overflows int64_t");
    }
  } else {
    if (b > 0) {
      if (a < min / b) throw std::overflow_error("product overflows int64_t");
    } else {
      if (a < max / b) throw std::overflow_error("product overflows int64_t");
    }
  }

  return a * b;
}
