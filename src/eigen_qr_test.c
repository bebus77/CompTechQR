#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matlib.h"
#include "eigen_qr.h"

/**
 * Test module. Test data is located in test_data directory.
 * http://www.bluebit.gr/matrix-calculator/
 * was used to calculate the expected results.
 */

/* Threshold used for equality comparisons. */
static const float TRESHOLD = 0.0001f;

static void run_qr_decom_tests(void);
static void run_qr_iter_tests(void);

/**
 * Tests qr decomposition.
 */
void run_qr_decom_tests(void)
{
  size_t test_count, t, m, n;
  FILE* fp = NULL;
  matrix* u = NULL;
  matrix* q = NULL;
  matrix* r = NULL;
  matrix* expected_q = NULL;
  matrix* expected_r = NULL;

  /* Read the input test file. */
  fp = fopen("../test_data/qr_decom_test.txt", "r");
  if (fp == NULL) 
  {
    perror("Failed to open qr_decom_test.txt");
    exit(EXIT_FAILURE);
  }

  /* Read the number of test cases. */
  fscanf(fp, "%zu", &test_count);
  
  /* Test each of the test samples. */
  for (t = 0; t < test_count; t++)
  {
    /* Read the dimensions of the input matrix. */
    fscanf(fp, "%zu %zu", &m, &n);

    /* Allocate the memory for the matrices. */
    u = new_matrix(m, n);
    q = new_matrix(m, n);
    r = new_matrix(m, n);
    expected_q = new_matrix(m, n);
    expected_r = new_matrix(m, n);

    /* Read the input and expected matrices. */
    read_matrix_data(fp, u);
    read_matrix_data(fp, expected_q);
    read_matrix_data(fp, expected_r);

    /* Perform qr decomposition. */
    qr_decomposition(u, q, r);

    /* Check the result. */
    assert(equal_matrix(expected_q, q, TRESHOLD));
    assert(equal_matrix(expected_r, r, TRESHOLD));

    /* Free the memory used for matrices. */
    destroy_matrix(u);
    destroy_matrix(q);
    destroy_matrix(r);
    destroy_matrix(expected_q);
    destroy_matrix(expected_r);
  }

  /* Close the input file. */
    fclose(fp);
}

/**
 * Tests qr iterations.
 */
void run_qr_iter_tests(void)
{
  size_t test_count, t, m, n;
  FILE* fp = NULL;
  matrix* a = NULL;
  matrix* a_k = NULL;

  /* Read the input test file. */
  fp = fopen("../test_data/qr_iter_test.txt", "r");
  if (fp == NULL) 
  {
    perror("Failed to open qr_iter_test.txt");
    exit(EXIT_FAILURE);
  }

  /* Read the number of test cases. */
  fscanf(fp, "%zu", &test_count);
  
  /* Test each of the test samples. */
  for (t = 0; t < test_count; t++)
  {
    /* Read the dimensions of the input matrix. */
    fscanf(fp, "%zu %zu", &m, &n);

    /* Allocate the memory for the matrices. */
    a = new_matrix(m, n);
    a_k = new_matrix(m, n);

    /* Read the input matrix. */
    read_matrix_data(fp, a);

    /* Allocate memory for eigen values. */
    float eigen_values[m];
    float expected_eigen_values[m];

    /* Read the expected eigen values. */
    read_vector_data(fp, expected_eigen_values, m);

    /* Perform qr iterations. */
    qr_iterations(a, a_k);

    /* Extract the eigen values obtained. */
    extract_diagonal(a_k, eigen_values, m);   

    /* Check the rsult. */
    assert(equal_vector(expected_eigen_values, m, eigen_values, m, TRESHOLD));

    /* Free the memory used for matrices. */
    destroy_matrix(a);
    destroy_matrix(a_k);
  }

  /* Close the input file. */
    fclose(fp);
}

int main(void)
{
  /* Test qr decomposition. */
  run_qr_decom_tests();
  /* Test qr iterations. */
  run_qr_iter_tests();
}