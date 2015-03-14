#include <assert.h>
#include <math.h>
#include <stdbool.h>

#include "eigenQR.h"

/* Convergence treshold. */
static float TRESHOLD = 0.00001;

/* Calculates convergance measure for power iterations. */
static bool converged(matrix* a_k, matrix* a_k1);

void
qr_iterations(matrix* a, matrix* a_k)
{
  assert(a != NULL && a_k != NULL);
  assert(a->m == a->n && a->m == a_k->m);

  /* Allocate working matrices. */
  matrix* a_k1 = new_matrix(a->m, a->n);
  matrix* q = new_matrix(a->m, a->n);
  matrix* r = new_matrix(a->m, a->n);

  /* A1 = A */
  assign_matrix(a_k, a);

  /* Perform the qr iterations until convergence condition is not satisfied. */
  while (1)
  {
    /* Qk, Rk = qr(Ak) */
    qr_decomposition(a_k, q, r);

    /* Ak+1 = Rk Qk */
    matrix_mul(r, q, a_k1);

    /* Check if the matrix converged. */
    if (converged(a_k, a_k1))
    {
      break;
    }

    /* Ak = Ak+1 */
    assign_matrix(a_k, a_k1);
  }

  /* Free memory used by working matrices. */
  destroy_matrix(r);
  destroy_matrix(q);
  destroy_matrix(a_k1);
}

void
qr_decomposition(matrix* u, matrix* q, matrix* r)
{
  assert(u != NULL && u->m == u->n);
  assert(q != NULL && q->m == q->n);
  assert(r != NULL && r->m == r->n);

  size_t i, j;

  /* Zero q and r. */
  fill_zero(q);
  fill_zero(r);

  for (i = 0; i < u->n; i++)
  {
    /* q_i = u_i */
    assign_column(q, i, u, i);

    for (j = 0; j < i; j++)
    {
      /* r[j, i] = q_j^T u_i */
      r->data[j][i] = dot_columns(q, j, u, i);  
      /* q_i = q_i - r[j, i] q_j */
      col_multiply_substract(q, i, q, i, r->data[j][i], q, j);
    }

    /* r[i, i] = ||q_i|| */
    r->data[i][i] = l2_norm_of_column(q, i);
    /* q_i = q_i / r[i, i] */
    mul_col_by_scalar(q, i, 1 / r->data[i][i]);
  }
}

/**
 * Calculates convergence measure and compares it with the treshold
 * in order to determine if the matrix converged.
 * Convergence measure: SUM (Ak+1[i, j] - Al[i, j])^2 < TRESHOLD 
 */
static bool 
converged(matrix* a_k, matrix* a_k1)
{
  size_t i, j;
  float conv_measure = 0.0f;

  for (i = 0; i < a_k->m; i++)
  {
    for (j = 0; j < a_k->n; j++)
    {
      conv_measure += pow(a_k1->data[i][j] - a_k->data[i][j], 2);
    }
  }

  return conv_measure < TRESHOLD;
}

