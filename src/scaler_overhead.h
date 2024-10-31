#ifndef SCALER_OVERHEAD_H
#define SCALER_OVERHEAD_H

#include <stdio.h>
#include <stdlib.h>

void load_scaler_params(const char *filename, double **center, double **scale, int *n_features);

void free_scaler_params(double *center, double *scale);
#endif // SCALER_OVERHEAD_H
