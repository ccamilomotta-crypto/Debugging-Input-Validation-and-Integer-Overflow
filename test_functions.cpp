#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include <cstdint>

#include "functions.h"

#define report_unexpected_exception std::cout << "[FAIL] (" << __func__ << ":" << __LINE__ << ") caught an unexpected exception." << std::endl; throw;
#define report_mismatch(expression,expected,actual) std::cout << "[FAIL] (" << __func__ << ":" << __LINE__ << ") expected " << expression << " to be " << expected << ", got " << actual << std::endl;

#define expect_eq(A,X) {\
int64_t actual, expected;\
try { actual = (A); expected = (X); } catch (...) { report_unexpected_exception }\
if (!(actual == expected)) { report_mismatch(#A,expected,actual) } }

#define expect_true(A) {\
bool actual;\
try { actual = (A); } catch (...) { report_unexpected_exception }\
if (!actual) { report_mismatch(#A,"true","false") } }

#define expect_false(A) {\
bool actual;\
try { actual = (A); } catch (...) { report_unexpected_exception }\
if (actual) { report_mismatch(#A,"false","true") } }

#define expect_throw(A,X) {\
try { (void)(A); report_mismatch(#A,"\\b\\b\\bthrow " + std::string(#X),"nothing") }\
catch (const X&) { }\
catch (...) { report_unexpected_exception } }

void test_largest() {
  expect_eq(largest(1, 2, 3), 3);
  expect_eq(largest(3, 2, 1), 3);
  expect_eq(largest(-5, -2, -10), -2);
  expect_eq(largest(7, 7, 7), 7);
  expect_eq(largest(0, -1, -2), 0);
}

void test_sum_is_even() {
  expect_true(sum_is_even(3, 5));
  expect_false(sum_is_even(3, 4));
  expect_true(sum_is_even(-1, 1));
  expect_true(sum_is_even(-3, -5));
  expect_false(sum_is_even(std::numeric_limits<int>::max(), 0));
  expect_true(sum_is_even(std::numeric_limits<int>::max(), 1));
}

void test_boxes_needed() {
  expect_eq(boxes_needed(-13), 0);
  expect_eq(boxes_needed(0), 0);
  expect_eq(boxes_needed(1), 1);
  expect_eq(boxes_needed(13), 1);
  expect_eq(boxes_needed(20), 1);
  expect_eq(boxes_needed(21), 2);
  expect_eq(boxes_needed(40), 2);
  expect_eq(boxes_needed(41), 3);
}

void test_smarter_section() {
  expect_true(smarter_section(40, 50, 75, 100));
  expect_false(smarter_section(1, 2, 2, 4));
  expect_throw(smarter_section(-1, 10, 1, 10), std::invalid_argument);
  expect_throw(smarter_section(1, 0, 1, 10), std::invalid_argument);
  expect_throw(smarter_section(11, 10, 1, 10), std::invalid_argument);
  expect_throw(smarter_section(1, 10, 11, 10), std::invalid_argument);
}

void test_good_dinner() {
  expect_false(good_dinner(9, false));
  expect_true(good_dinner(10, false));
  expect_true(good_dinner(20, false));
  expect_false(good_dinner(21, false));
  expect_true(good_dinner(21, true));
  expect_false(good_dinner(-5, true));
}

void test_sum_between() {
  expect_eq(sum_between(1, 10), 55);
  expect_eq(sum_between(10, 10), 10);
  expect_eq(sum_between(-3, 3), 0);
  expect_throw(sum_between(10, 1), std::invalid_argument);

  expect_throw(sum_between(1, std::numeric_limits<int32_t>::max()), std::overflow_error);

  int32_t mn = std::numeric_limits<int32_t>::min();
  int32_t mx = std::numeric_limits<int32_t>::max();
  expect_eq(sum_between(mn, mx), mn);
}

void test_product() {
  expect_eq(product(2, 2), 4);
  expect_eq(product(-3, 5), -15);
  expect_eq(product(-3, -5), 15);
  expect_eq(product(0, 999), 0);

  expect_throw(product(std::numeric_limits<int64_t>::max(), 2), std::overflow_error);
  expect_throw(product(std::numeric_limits<int64_t>::min(), -1), std::overflow_error);
}

int main() {
  test_largest();
  test_sum_is_even();
  test_boxes_needed();
  test_smarter_section();
  test_good_dinner();
  test_sum_between();
  test_product();
  return 0;
}
