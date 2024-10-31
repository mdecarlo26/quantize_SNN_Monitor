#include "scaler.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Function to apply robust scaling
void apply_robust_scaling(double **data, int n_samples, int n_features, double *center, double *scale) {
    for (int i = 0; i < n_samples; i++) {
        for (int j = 0; j < n_features; j++) {
            data[i][j] = (data[i][j] - center[j]) / scale[j];
        }
    }
    printf("%f, %f, %f\n", data[100][100], center[100], scale[100]);
}

