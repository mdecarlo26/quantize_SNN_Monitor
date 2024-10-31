#ifndef SCALER_H
#define SCALER_H

#include <stdio.h>
#include <stdlib.h>

#define SCALER_VAL 1000
#define SCALER_FLOAT 1000.0

// Function to load the scaler parameters (center and scale)

// Function to apply robust scaling
void apply_robust_scaling(double **data, int n_samples, int n_features, double *center, double *scale);

#endif  // SCALER_H
