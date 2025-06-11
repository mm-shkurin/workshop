#include "equation.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

void test_no_roots() {
  EquationSolution s = solve_quadratic(0, 1, 1, 1e-12);
  assert(s.count == 0);
  free_solution(&s);
}

void test_two_roots() {
  EquationSolution s = solve_quadratic(1, 0, -1, 1e-12);
  assert(s.count == 2);
  assert(fabs(s.roots[0] - (-1.0)) < 1e-9);
  assert(fabs(s.roots[1] - 1.0) < 1e-9);
  free_solution(&s);
}

void test_one_root() {
  EquationSolution s = solve_quadratic(1, 0, 0, 1e-12);
  assert(s.count == 1);
  assert(fabs(s.roots[0] - 0.0) < 1e-9);
  free_solution(&s);
}

void test_no_real_roots() {
  EquationSolution s = solve_quadratic(1, 0, 1, 1e-12);
  assert(s.count == 0);
  free_solution(&s);
}

void test_small_c() {
  EquationSolution s = solve_quadratic(1, 0, -1e-7, 1e-12);
  assert(s.count == 2);
  assert(fabs(s.roots[0] - (-3e-4)) < 1e-4);
  assert(fabs(s.roots[1] - 3e-4) < 1e-4);
  free_solution(&s);
}

void test_large_b() {
  EquationSolution s = solve_quadratic(1, -1e10, -1, 1e-12);
  assert(s.count == 2);
  assert(fabs(s.roots[0] - (-1e-10)) < 1e-11);
  assert(fabs(s.roots[1] - 1e10) < 1e-11);
  free_solution(&s);
}

void test_very_small_c() {
  EquationSolution s = solve_quadratic(1, 0, -1e-8, 1e-12);
  assert(s.count == 2); // Изменили ожидание на 2 корня
  free_solution(&s);
}

int main() {
  test_no_roots();
  test_two_roots();
  test_one_root();
  test_no_real_roots();
  test_small_c();
  test_large_b();
  test_very_small_c();

  printf("All tests passed successfully!\n");
  return 0;
}
