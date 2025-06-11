#include "equation.h"
#include <math.h>
#include <stdlib.h>

EquationSolution solve_quadratic(double a, double b, double c, double eps) {
  EquationSolution solution = {NULL, 0};

  if (fabs(a) < eps) {
    return solution;
  }

  if (fabs(b) < eps && fabs(c) < eps) {
    solution.count = 1;
    solution.roots = malloc(sizeof(double));
    solution.roots[0] = 0.0;
    return solution;
  }

  double discriminant = b * b - 4 * a * c;

  if (fabs(discriminant) < eps) {
    discriminant = 0.0;
  }

  if (discriminant > eps) {
    solution.count = 2;
    solution.roots = malloc(2 * sizeof(double));

    double sqrt_discr = sqrt(discriminant);
    if (b >= 0) {
      solution.roots[0] = (-b - sqrt_discr) / (2 * a);
      solution.roots[1] = (2 * c) / (-b - sqrt_discr);
    } else {
      solution.roots[0] = (2 * c) / (-b + sqrt_discr);
      solution.roots[1] = (-b + sqrt_discr) / (2 * a);
    }

    if (solution.roots[0] > solution.roots[1]) {
      double temp = solution.roots[0];
      solution.roots[0] = solution.roots[1];
      solution.roots[1] = temp;
    }
  } else if (fabs(discriminant) < eps) {
    solution.count = 1;
    solution.roots = malloc(sizeof(double));
    solution.roots[0] = -b / (2 * a);
  }

  return solution;
}

void free_solution(EquationSolution *solution) {
  if (solution->roots != NULL) {
    free(solution->roots);
    solution->roots = NULL;
  }
  solution->count = 0;
}
