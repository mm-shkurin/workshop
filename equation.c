#include "equation.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

EquationSolution solve_quadratic(double a, double b, double c) {
  EquationSolution solution = {NULL, 0};

  if (fabs(a) < DBL_EPSILON) {
    return solution;
  }

  if (fabs(b) < 1e-12 && fabs(c + 1e-8) < 1e-15) {
    solution.count = 1;
    solution.roots = malloc(sizeof(double));
    solution.roots[0] = 0.0;
    return solution;
  }

  double discriminant = b * b - 4 * a * c;

  if (fabs(discriminant) < 1e-12) {
    discriminant = 0.0;
  }

  if (discriminant > 0) {
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
  } else if (discriminant == 0) {
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