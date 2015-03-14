#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "matlib.h"

void
matrix_mul(matrix* a, matrix* b, matrix* c)
{
  assert(a != NULL && b != NULL && c != NULL);
  assert(a->n == b->m && c->m == a->m && c->n == b->n);
  
  size_t i, j, k;

  for (i = 0; i < a->m; i++)
  {
    for (j = 0; j < b->n; j++)
    {
      for (k = 0; k < a->n; k++)
      {
        c->data[i][j] += a->data[i][k] * b->data[k][j]; 
      }
    }
  }
}

float
l2_norm_of_column(matrix *a, size_t col)
{
  assert(a != NULL && col >= 0 && col < a->n);

  size_t i;
  float norm = 0;

  for (i = 0; i < a->m; i++)
  {
    norm += a->data[i][col] * a->data[i][col]; 
  }

  return sqrtf(norm);
}

float 
dot_columns(matrix* a, size_t col_1, size_t col_2)
{
  assert(a != NULL);
  assert(col_1 >= 0 && col_1 < a->n && col_2 >= 0 && col_2 < a->n);

  float dot = 0;
  size_t i;

  for (i = 0; i < a->m; i++)
  {
    dot += a->data[i][col_1] * a->data[i][col_2];
  }

  return dot;
}

void
mul_col_by_scalar(matrix* a, size_t col, float scalar)
{
  assert(a != NULL && col >= 0 && col < a->n);

  size_t i;

  for (i = 0; i < a->m; i++)
  {
    a->data[i][col] = scalar * a->data[i][col];
  }
}

void
col_multiply_substract(matrix* a, size_t col_a, 
                       matrix* b, size_t col_b, 
                       float scalar, 
                       matrix *c, size_t col_c)
{
  assert(a != NULL && col_a >= 0 && col_a < a->n);
  assert(b != NULL && col_b >= 0 && col_b < b->n);
  assert(c != NULL && col_c >= 0 && col_c < c->n);
  assert(a->m == b->m && b->m == c->m);

  size_t i;

  for (i = 0; i < a->m; i++)
  {
    a->data[i][col_a] = b->data[i][col_b] - scalar * c->data[i][col_c];
  }
}

matrix*
new_matrix(size_t m, size_t n)
{
  assert(m >= 0 && n >= 0);

  /* Allocate memory for the matrix struct. */
  matrix* mat = (matrix*) malloc(sizeof(matrix));
  if (mat == NULL)
  {
    perror("Failed to allocate memory for mat.");
    exit(EXIT_FAILURE);
  }

  /* Set the dimensions. */
  mat->m = m;
  mat->n = n;

  /* Allocate memory for the rows. */
  mat->data = (float**) malloc(sizeof(float*) * m);
  if (mat->data == NULL)
  {
    perror("Failed to allocate memory for mat rows.");
    exit(EXIT_FAILURE);
  }

  /* Allocate memory for the columns. */
  for (size_t i = 0; i < m; i++)
  {
    mat->data[i] = (float*) malloc(sizeof(float) * n); 
    if (mat->data[i] == NULL)
    {
      perror("Failed to allocate memory for mat columns");
      exit(EXIT_FAILURE);
    }
  }

  return mat;
}

void
destroy_matrix(matrix* mat)
{
  assert(mat != NULL);

  /* Free the columns. */
  for (size_t i = 0; i < mat->m; i++)
  {
    free(mat->data[i]);
  }

  /* Free the rows. */
  free(mat->data);
  /* Free the matrix struct. */
  free(mat);
}

struct vector*
new_vector(size_t n)
{
  assert(n >= 0);
  
  /* Allocate memory for the vector struct. */
  struct vector* v = (struct vector*) malloc(sizeof(struct vector));
  if (v == NULL)
  {
    perror("Failed to allocate memory for the vector struct.");
    exit(EXIT_FAILURE);
  }

  /* Set the size. */
  v->n = n;

  /* Allocate memory for data. */
  v->data = (float*) malloc(sizeof(float) * n);
  if (v->data == NULL)
  {
    perror("Failed to allocate memory for data.");
    exit(EXIT_FAILURE);
  }

  return v;
}