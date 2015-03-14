#include <assert.h>

#include "eigenQR.h"


void
qr_decomposition(matrix* u, matrix* q, matrix* r)
{
  assert(u != NULL && u->m == u->n);
  assert(q != NULL && q->m == q->n);
  assert(r != NULL && r->m == r->n);

  size_t i, j;

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