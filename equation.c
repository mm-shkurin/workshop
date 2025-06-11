#include "equation.h"
#include <math.h>
#include <stdlib.h>

EquationSolution solve_quadratic(double a, double b, double c, double eps) {
  EquationSolution solution = {NULL, 0};

  if (fabs(a) < eps) {
    return solution;
  }

  double discriminant = b * b - 4 * a * c;

  if (fabs(discriminant) < eps) {
    discriminant = 0.0;
  }

  if (discriminant < -eps) {
    return solution;
  } else if (discriminant > eps) {
    solution.count = 2;
    solution.roots = malloc(2 * sizeof(double));

    if (b > eps) {
      double q = -0.5 * (b + sqrt(discriminant));
      solution.roots[0] = q / a;
      solution.roots[1] = c / q;
    } else if (b < -eps) {
      double q = -0.5 * (b - sqrt(discriminant));
      solution.roots[0] = c / q;
      solution.roots[1] = q / a;
    } else {
      solution.roots[0] = -sqrt(-c / a);
      solution.roots[1] = sqrt(-c / a);
    }

    if (solution.roots[0] > solution.roots[1]) {
      double temp = solution.roots[0];
      solution.roots[0] = solution.roots[1];
      solution.roots[1] = temp;
    }
  } else {
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
