#ifndef MATLIB_H
#define MATLIB_H

#include <stdlib.h>

/* Matrix & vector library. */

/* Matrix representation. */
struct matrix 
{
  size_t m;      /* Number of rows. */
  size_t n;      /* Number of columns. */
  float** data;  /* Elements. */
};

/* Vector representation. */
struct vector
{
  size_t n;     /* Dimension. */
  float* data;  /* Elements. */
};

/* Allocates matrix of size m x n on the heap. */
struct matrix* new_matrix(size_t m, size_t n);
/* Frees the memory used by the matrix mat. */
void destroy_matrix(struct matrix* mat);

/* Allocates vector of size n. */
struct vector* new_vector(size_t n);
/* Frees the memory used by the vector v. */
void destroy_vector(struct vector* v);

#endif /* src/matlib.h */