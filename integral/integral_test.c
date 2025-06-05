#include "integral.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double linear(double x) { return x; }
static double quadratic(double x) { return x * x; }
static double trigonometric(double x) { return sin(x); }
static double exponential(double x) { return exp(x); }

static void test_linear_function(void) {
  double result = calculate_integral(0, 1, 100000, linear);
  if (fabs(result - 0.5) >= 1e-8) {
    fprintf(stderr, "Linear test failed: expected 0.5, got %.15f\n", result);
    exit(EXIT_FAILURE);
  }
}

static void test_quadratic_function(void) {
  double result = calculate_integral(0, 1, 100000, quadratic);
  if (fabs(result - 1.0 / 3.0) >= 1e-8) {
    fprintf(stderr, "Quadratic test failed: expected 0.333..., got %.15f\n",
            result);
    exit(EXIT_FAILURE);
  }
}

static void test_trigonometric_function(void) {
  const double pi = 3.14159265358979323846;
  const int n = 10000000;
  double result = calculate_integral(0, pi, n, trigonometric);
  double error = fabs(result - 2.0);

  if (error >= 5e-6) {
    fprintf(stderr,
            "Trigonometric test failed:\n"
            "Expected: 2.0\n"
            "Got:      %.15f\n"
            "Error:    %.15f\n",
            result, error);
    exit(EXIT_FAILURE);
  }
}

static void test_exponential_function(void) {
  double e = 2.71828182845904523536;
  double result = calculate_integral(0, 1, 100000, exponential);
  if (fabs(result - (e - 1)) >= 1e-8) {
    fprintf(stderr, "Exponential test failed: expected ~1.718..., got %.15f\n",
            result);
    exit(EXIT_FAILURE);
  }
}

static void test_zero_length_interval(void) {
  double result = calculate_integral(0, 0, 1000, linear);
  if (fabs(result) >= DBL_EPSILON) {
    fprintf(stderr, "Zero interval test failed: expected 0.0, got %.15f\n",
            result);
    exit(EXIT_FAILURE);
  }
}

static void test_negative_interval(void) {
  double result = calculate_integral(-1, 1, 100000, linear);
  if (fabs(result) >= 1e-10) {
    fprintf(stderr, "Negative interval test failed: expected 0.0, got %.15f\n",
            result);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  test_linear_function();
  test_quadratic_function();
  test_trigonometric_function();
  test_exponential_function();
  test_zero_length_interval();
  test_negative_interval();

  printf("All integration tests passed successfully!\n");
  return EXIT_SUCCESS;
}