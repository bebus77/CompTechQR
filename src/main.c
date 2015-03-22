#include <stdio.h>
#include <stdlib.h>

#include "matlib.h"
#include "eigenQR.h"

static void test_qr_decomposition(matrix* u);
static void test_qr_iterations(matrix* u);

static void
test_qr_decomposition(matrix* u)
{
  /* Allocate q and r. */
  matrix* q = new_matrix(u->m, u->n);
  matrix* r = new_matrix(u->m, u->n);

  /* Perform qr decomposition. */
  qr_decomposition(u, q, r);

  /* Print the matrices. */
  printf("U:\n");
  print_matrix_data(stdout, u);
  printf("Q:\n");
  print_matrix_data(stdout, q);
  printf("R:\n");
  print_matrix_data(stdout, r);

  /* Free memory occupied by q and r. */
  destroy_matrix(q);
  destroy_matrix(r);
}

static void
test_qr_iterations(matrix* a)
{
  /* Allocate Ak */
  matrix* a_k = new_matrix(a->m, a->n);

  /* Perform qr iterations. */
  qr_iterations(a, a_k);

  /* Print the matrices. */
  printf("A:\n");
  print_matrix_data(stdout, a);
  printf("Ak:\n");
  print_matrix_data(stdout, a_k);

  /* Free memory used by Ak. */
  destroy_matrix(a_k);
}

/**
 * Input format: 
 * The first line has m and n indicating number of rows and columns.
 * Each of the next m lines contains n floats indicating the rows of the matrix.
 *
 * Sample input:
 * 3 3
 *  1.0  1.0  0.0
 *  1.0  2.0  1.0
 * -2.0 -3.0  1.0
 */
int main(int argc, char **argv)
{
  FILE* fp = NULL;
  size_t m, n;

  /* Read the input. */
  //fp = fopen("input.txt", "r");
  fp = fopen("../test_data/power_iter.txt", "r");
  if (fp == NULL)
  {
    perror("Failed to open input.txt");
    exit(EXIT_FAILURE);
  }

  /* Read the dimensions of the matrix. */
  fscanf(fp, "%zu %zu", &m, &n);
  
  /* Alloate the matrix. */
  matrix* u = new_matrix(m, n);
  /* Read matrix. */
  read_matrix_data(fp, u);
  /* Close the input file. */
  fclose(fp);

  /* Test qr decomposition. */
  //test_qr_decomposition(u);

  /* Test qr iterations. */
  test_qr_iterations(u);

  /* Free the matrix memory. */
  destroy_matrix(u);

  return 0;
}