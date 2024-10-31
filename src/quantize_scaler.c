#include "quantize_scaler.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void apply_robust_scaling_quantize(int **data, int n_samples, int n_features, int *center, int *scale) {
    for (int i = 0; i < n_samples; i++) {
        for (int j = 0; j < n_features; j++) {
            data[i][j] = (data[i][j] - center[j]) * QUANTIZE_SCALER_VAL / scale[j];
        }
    }
    printf("%d, %d, %d\n", data[100][100], center[100], scale[100]);
}

void quantize_scaler_values(int n_features, double *center_float, double *scaler_float, int *center, int* scaler)
{
    for (int j = 0; j < n_features; j++) {
        center[j] = (int)(center_float[j] * QUANTIZE_SCALER_VAL);
        scaler[j] = (int)(scaler_float[j] * QUANTIZE_SCALER_VAL);
    }
}

int **quantize_data(double **d, int row_count, int col_count)
{
	int **data = malloc_quantize_data(row_count, col_count);
	for (int i = 0; i < row_count; i++) {
		for (int j = 0; j < col_count; j++) {
			data[i][j] = (int)(d[i][j] * QUANTIZE_SCALER_VAL);
		}
	}
	return data;
}

int **malloc_quantize_data(int row_count, int col_count) {
    int **data = (int **)malloc(row_count * sizeof(int *));
    for (int i = 0; i < row_count; i++) {
        data[i] = (int *)malloc(col_count * sizeof(int));
    }
    return data;
}

void free_scaler_params_quantize(int *center, int *scale) {
    free(center);
    free(scale);
}

void free_quantized_data(int **data, int num_rows) {
    for(int i = 0; i < num_rows; i++){
        free(data[i]);
    }
}
