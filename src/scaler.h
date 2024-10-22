#ifndef SCALER_H
#define SCALER_H

#include <stdio.h>
#include <stdlib.h>

// Function to load the scaler parameters (center and scale)
void load_scaler_params(const char *filename, double **center, double **scale, int *n_features);

// Function to apply robust scaling
void apply_robust_scaling(double **data, int n_samples, int n_features, double *center, double *scale);

// Function to free the dynamically allocated memory for center and scale
void free_scaler_params(double *center, double *scale);

#endif  // SCALER_H
