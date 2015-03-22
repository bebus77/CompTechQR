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

  /* Clear the result matrix. */
  fill_zero(c);

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
  assert(a != NULL);

  size_t i;
  float norm = 0;

  for (i = 0; i < a->m; i++)
  {
    norm += a->data[i][col] * a->data[i][col]; 
  }

  return sqrtf(norm);
}

float 
dot_columns(matrix* a, size_t col_a, matrix* b, size_t col_b)
{
  assert(a != NULL && b != NULL && a->m == b->m);

  float dot = 0;
  size_t i;

  for (i = 0; i < a->m; i++)
  {
    dot += a->data[i][col_a] * b->data[i][col_b];
  }

  return dot;
}

void
mul_col_by_scalar(matrix* a, size_t col, float scalar)
{
  assert(a != NULL);

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
  assert(a != NULL && b != NULL && c != NULL);
  assert(a->m == b->m && b->m == c->m);

  size_t i;

  for (i = 0; i < a->m; i++)
  {
    a->data[i][col_a] = b->data[i][col_b] - scalar * c->data[i][col_c];
  }
}

void 
assign_column(matrix* a, size_t col_a, matrix* b, size_t col_b)
{
  assert(a != NULL && b != NULL && a->m == a->n);

  size_t i;

  for (i = 0; i < a->m; i++)
  {
    a->data[i][col_a] = b->data[i][col_b];
  }
}

void
assign_matrix(matrix* a, matrix* b)
{
  assert(a != NULL && b != NULL && a->m == b->m && a->n == b->n);

  size_t i, j;

  for (i = 0; i < a->m; i++)
  {
    for (j = 0; j < a->n; j++)
    {
      a->data[i][j] = b->data[i][j];
    }
  }
}

void
fill_zero(matrix* a)
{
  assert(a != NULL);

  size_t i, j;

  for (i = 0; i < a->m; i++)
  {
    for (j = 0; j < a->n; j++)
    {
      a->data[i][j] = 0.0f;
    }
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

 void 
 read_matrix_data(FILE* fp, matrix* mat)
 {
  assert(fp != NULL && mat != NULL);

  size_t i, j;

  for (i = 0; i < mat->m; i++)
  {
    for (j = 0; j < mat->n; j++)
    {
      fscanf(fp, "%f", &(mat->data[i][j]));
    }
  }
 }

void 
print_matrix_data(FILE* fp, matrix* mat)
{
  assert(fp != NULL && mat != NULL);

  size_t i, j;

  for (i = 0; i < mat->m; i++)
  {
    for (j = 0; j < mat->n; j++)
    {
      fprintf(fp, "% f ", mat->data[i][j]);
    }
    fprintf(fp, "\n");
  } 
}

void 
extract_diagonal(matrix* a, float* diag, size_t n)
{
  assert(a != NULL && diag != NULL);
  assert(a->m == a->n && a->n == n);

  size_t i;

  for (i = 0; i < n; i++)
  {
    diag[i] = a->data[i][i];
  }
}

bool
equal_matrix(matrix* a, matrix* b, float treshold)
{
  assert(a != NULL && b != NULL);

  size_t i, j;

  if (a->m != b->m || a->n != b->n)
  {
    return false;
  }

  for (i = 0; i < a->m; i++)
  {
    for (j = 0; j < a->n; j++)
    {
      if (abs(a->data[i][j] - b->data[i][j]) > treshold)
      {
        return false;
      }
    }
  }
  return true;
}

bool 
equal_vector(float* v1, size_t l1, float* v2, size_t l2, float treshold)
{
  assert(v1 != NULL && v2 != NULL);

  size_t i;

  if (l1 != l2)
  {
    return false;
  }

  for (i = 0; i < l1; i++)
  {
    if (abs(v1[i] - v2[i]) > treshold)
    {
      return false;
    }
  }
  return true;
}

void 
read_vector_data(FILE* fp, float* v, size_t len)
{
  assert(fp != NULL && v != NULL);

  size_t i;

  for (i = 0; i < len; i++)
  {
    fscanf(fp, "%f", &(v[i]));
  }
}

void 
print_vector(FILE* fp, float* v, size_t len)
{
  assert(fp != NULL && v != NULL);

  size_t i;

  for (i = 0; i < len; i++)
  {
    fprintf(fp, "% f ", v[i]);
  }
  fprintf(fp, "\n");
}

