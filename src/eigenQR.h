#ifndef EIGEN_QR_H
#define EIGEN_QR_H

#include "matlib.h"

/**
 * Functions for computing eigen values using QR algorithm
 */

/**
 * Performs QR iterations.
 */
void qr_iterations(void);

/** 
 * Performs QR decomposition. 
 */
void qr_decomposition(matrix* u, matrix* q, matrix* r);

#endif /* src/eigenQR.h */