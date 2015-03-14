#ifndef MATLIB_H
#define MATLIB_H

#include <stdlib.h>
#include <stdio.h>

/** 
 * Matrix & vector library. 
 */

/**
 * Matrix representation. 
 */
typedef struct 
{
  size_t m;      /* Number of rows. */
  size_t n;      /* Number of columns. */
  float** data;  /* Elements. */
} matrix;

/**
 * Vector representation. 
 */
struct vector
{
  size_t n;     /* Dimension. */
  float* data;  /* Elements. */
};

/** 
 * Allocates matrix of size m x n on the heap. 
 */
matrix* new_matrix(size_t m, size_t n);

/** 
 * Frees the memory used by the matrix mat. 
 */
void destroy_matrix(matrix* mat);

/**
 * Reads matrix data from fp.
 */
 void read_matrix_data(FILE* fp, matrix* mat);

/**
 * Prints matrix data to fp.
 */
void print_matrix_data(FILE* fp, matrix* mat);

/**
 * Allocates vector of size n. 
 */
struct vector* new_vector(size_t n);

/** 
 * Frees the memory used by the vector v. 
 */
void destroy_vector(struct vector* v);

/** 
 * Multiplies a by b and stores the resulting matrix in c. 
 */
void matrix_mul(matrix* a, matrix* b, matrix* c);

/* Calculates the l2 norm of column vector of a. */
float l2_norm_of_column(matrix* a, size_t col);

/**
 * Performs dot product between two column vectors of a and b. 
 */
float dot_columns(matrix* a, size_t col_a, matrix* b, size_t col_b);

/**
 * Multiplies a column of the matrix by a scalar.
 */
void mul_col_by_scalar(matrix* a, size_t col, float scalar);

/** 
 * Performs multpily and substract on colums of  a, b and c.
 * In particular: a[col_a] = b[col_b] - scalar * c[col_c] 
 */
void col_multiply_substract(matrix* a, size_t col_a,
                            matrix* b, size_t col_b,
                            float scalar,
                            matrix* c, size_t col_c);

/**
 * Assigns jth column of b to ith column of a.
 */
void assign_column(matrix* a, size_t col_a, matrix* b, size_t col_b);

#endif /* src/matlib.h */