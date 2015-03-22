#include <stdio.h>
#include <stdlib.h>

#include "matlib.h"
#include "eigenQR.h"

/**
 * Reads two matrices from the file and:
 * - performs qr decomposition on the first matrix U
 * - prints q and r to the console
 * - performs qr iterations on the second matrix A
 * - prints its eigen values to the console
 *
 * Matrix input format for both matrices is: 
 * The first line has m and n indicating number of rows and columns.
 * Each of the next m lines contains n floats indicating the rows of the matrix.
 *
 * Sample input:
 * 3 3
 *  1.0  1.0  0.0
 *  1.0  2.0  1.0
 * -2.0 -3.0  1.0
 * 2 2
 *  7.0  2.0
 *  2.0  4.0
 */
int main(int argc, char **argv)
{
  FILE* fp = NULL;
  matrix* u = NULL;
  matrix* q = NULL;
  matrix* r = NULL;
  matrix* a = NULL;
  matrix* a_k = NULL;
  size_t m, n;  

  /* Read the input. */
  fp = fopen("input.txt", "r");
  if (fp == NULL)
  {
    perror("Failed to open input.txt");
    exit(EXIT_FAILURE);
  }

  /* Read the dimensions of the matrix U. */
  fscanf(fp, "%zu %zu", &m, &n);
  
  /* Alloate the matrices U Q and R. */
  u = new_matrix(m, n);
  q = new_matrix(m, n);
  r = new_matrix(m, n);

  /* Read matrix data. */
  read_matrix_data(fp, u);

  /* Perform qr decomposition. */
  qr_decomposition(u, q, r);

  /* Print the matrices. */
  printf("QR decomposition:\n");
  printf("U:\n");
  print_matrix_data(stdout, u);
  printf("Q:\n");
  print_matrix_data(stdout, q);
  printf("R:\n");
  print_matrix_data(stdout, r);

  /* Free memory occupied by q and r. */
  destroy_matrix(u);  
  destroy_matrix(q);
  destroy_matrix(r);

  /* Read the dimensions of the matrix A. */
  fscanf(fp, "%zu %zu", &m, &n);

  /* Allocate a vector for storing eigen values and matrices A and A_k */
  a = new_matrix(m, n);
  a_k = new_matrix(m, n);
  float eigen_values[m];

  /* Read matix data. */
  read_matrix_data(fp, a);

  /* Perform qr iterations. */
  qr_iterations(a, a_k);

  /* Extract the eigen values. */
  extract_diagonal(a_k, eigen_values, m);

  /* Print the matrix A and its eigen values. */
  printf("\nQR iterations:\n");
  printf("A:\n");
  print_matrix_data(stdout, a);
  printf("Eigen values:\n");
  print_vector(stdout, eigen_values, m);  

  /* free memory occupied by A and A_k. */
  destroy_matrix(a);
  destroy_matrix(a_k);

  /* Close the input file. */
  fclose(fp);

  return 0;
}