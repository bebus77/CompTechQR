#include <stdio.h>
#include <stdlib.h>

#include "matlib.h"
#include "eigenQR.h"

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
  fp = fopen("input.txt", "r");
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
  
  /* Perform qr */
  matrix* q = new_matrix(m, n);
  matrix* r = new_matrix(m, n);

  qr_decomposition(u, q, r);

  /* Print matrix. */
  printf("U:\n");
  print_matrix_data(stdout, u);
  printf("Q:\n");
  print_matrix_data(stdout, q);
  printf("R:\n");
  print_matrix_data(stdout, r);

  /* Close the input file. */
  fclose(fp);

  /* Free the matrix memory. */
  destroy_matrix(u);

  return 0;
}