#include "scaler.h"
#include <string.h>

// Function to load the scaler parameters (center and scale) from a CSV file
void load_scaler_params(const char *filename, double **center, double **scale, int *n_features) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open scaler parameters file.\n");
        exit(1);
    }

    char buffer[1024];
    int count = 0;

    fgets(buffer, sizeof(buffer), file);  // Skip header line

    // Read first data row to determine the number of features (columns)
    fgets(buffer, sizeof(buffer), file);
    char *value = strtok(buffer, ",");
    while (value) {
        count++;
        value = strtok(NULL, ",");
    }
    *n_features = count;

    // Allocate memory for center and scale arrays
    *center = (double *)malloc(count * sizeof(double));
    *scale = (double *)malloc(count * sizeof(double));

    // Rewind the file and skip header again
    rewind(file);
    fgets(buffer, sizeof(buffer), file);  // Skip header line

    // Read center values
    fgets(buffer, sizeof(buffer), file);
    int i = 0;
    value = strtok(buffer, ",");
    while (value) {
        (*center)[i++] = atof(value);
        value = strtok(NULL, ",");
    }

    // Read scale values
    fgets(buffer, sizeof(buffer), file);
    i = 0;
    value = strtok(buffer, ",");
    while (value) {
        (*scale)[i++] = atof(value);
        value = strtok(NULL, ",");
    }

    fclose(file);
}

// Function to apply robust scaling
void apply_robust_scaling(double **data, int n_samples, int n_features, double *center, double *scale) {
    for (int i = 0; i < n_samples; i++) {
        for (int j = 0; j < n_features; j++) {
            data[i][j] = (data[i][j] - center[j]) / scale[j];
        }
    }
}

// Function to free the dynamically allocated memory for center and scale
void free_scaler_params(double *center, double *scale) {
    free(center);
    free(scale);
}
