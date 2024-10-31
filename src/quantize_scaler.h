#ifndef QUANTIZE_SCALER_H
#define QUANTIZE_SCALER_H

#include <stdio.h>
#include <stdlib.h>

#define QUANTIZE_SCALER_VAL 1000
#define QUANTIZE_SCALER_FLOAT 1000.0

void apply_robust_scaling_quantize(int **data, int n_samples, int n_features, int *center, int *scale); 

void quantize_scaler_values(int n_features, double *center_float, double *scaler_float, int *center, int* scaler);

int **quantize_data(double **d, int row_count, int col_count);
int **malloc_quantize_data(int row_count, int col_count);

void free_scaler_params_quantize(int *center, int *scale);
void free_quantized_data(int **data, int num_rows); 

#endif  // QUANTIZE_SCALER_H
