#include <assert.h>
#include <stdio.h>

#include "matlib.h"

struct matrix*
new_matrix(size_t m, size_t n)
{
  assert(m >= 0 && n >= 0);

  /* Allocate memory for the matrix struct. */
  struct matrix* mat = (struct matrix*) malloc(sizeof(struct matrix));
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
destroy_matrix(struct matrix* mat)
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