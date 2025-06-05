#ifndef EQUATION_H
#define EQUATION_H

typedef struct {
  double *roots;
  int count;
} EquationSolution;

EquationSolution solve_quadratic(double a, double b, double c);
void free_solution(EquationSolution *solution);

#endif