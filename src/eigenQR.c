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

    for (j = 0; j < i; j++)
    {
         
    }
  }

}