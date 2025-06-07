#ifndef INTEGRAL_H
#define INTEGRAL_H

typedef double (*MathFunction)(double);

double calculate_integral(double a, double b, int n, MathFunction f);

#endif
