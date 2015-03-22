#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matlib.h"
#include "eigenQR.h"

/**
 * Test module. Test data is located in test_data directory.
 */

static const float TRESHOLD = 0.000001f;

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
    assert(equal(expected_q, q, TRESHOLD));
    assert(equal(expected_r, r, TRESHOLD));

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

}

int main(void)
{
  return 0;
}