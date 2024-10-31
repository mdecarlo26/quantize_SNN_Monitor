#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Function to load the scaler parameters (center and scale) from a CSV file
void load_scaler_params(const char *filename, double **center, double **scale, int *n_features) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open scaler parameters file.\n");
        exit(1);
    }

    char buffer[2048];
    int count = 0;

    fgets(buffer, sizeof(buffer), file);  // Read header line ("Center,Scale")

    // Read the file line by line to count the number of features (rows)
    while (fgets(buffer, sizeof(buffer), file)) {
        count++;
    }
    *n_features = count;

    // Allocate memory for center and scale arrays based on the number of features
    *center = (double *)malloc(count * sizeof(double));
    *scale = (double *)malloc(count * sizeof(double));

    // Rewind the file to read the data again
    rewind(file);
    fgets(buffer, sizeof(buffer), file);  // Skip header line

    // Read center and scale values from each row
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        char *center_val = strtok(buffer, ",");
        char *scale_val = strtok(NULL, ",");
        
        (*center)[i] = atof(center_val);
        (*scale)[i] = atof(scale_val);
        i++;
    }

    fclose(file);
}

void free_scaler_params(double *center, double *scale)
{
	free(center);
	free(scale);
}
