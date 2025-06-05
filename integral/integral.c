#include "integral.h"
#include <float.h>
#include <math.h>

double calculate_integral(double a, double b, int n, MathFunction f) {
  if (n <= 0 || isnan(a) || isnan(b)) {
    return NAN;
  }

  if (fabs(b - a) < DBL_EPSILON) {
    return 0.0;
  }

  int sign = 1;
  if (b < a) {
    double tmp = a;
    a = b;
    b = tmp;
    sign = -1;
  }

  double h = (b - a) / n;
  double sum = 0.0;

  double x = a;
  sum += 0.5 * f(x);

  for (int i = 1; i < n; i++) {
    x += h;
    sum += f(x);
  }

  x = b;
  sum += 0.5 * f(x);

  return sign * sum * h;
}