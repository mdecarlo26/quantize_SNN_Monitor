#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double** read_csv(const char *filename, int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return NULL;
    }

    // Temporary storage for lines
    char buffer[10192];
    double **data = NULL;
    int row_count = 0;
    int col_count = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        row_count++;
        if (row_count == 1) {
            // First row determines the number of columns
            char *value = strtok(buffer, ",");
            while (value) {
                col_count++;
                value = strtok(NULL, ",");
            }
        }
    }

    // Rewind the file to read the data again
    rewind(file);

    // Allocate memory for the 2D array
    data = (double **)malloc(row_count * sizeof(double *));
    for (int i = 0; i < row_count; i++) {
        data[i] = (double *)malloc(col_count * sizeof(double));
    }

    int row = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        int col = 0;
        char *value = strtok(buffer, ",");
        while (value) {
            data[row][col] = atof(value);
            value = strtok(NULL, ",");
            col++;
        }
        row++;
    }

    fclose(file);
    *rows = row_count;
    *cols = col_count;

    return data;
}

void free_csv_data(double **data, int rows) {
    for (int i = 0; i < rows; i++) {
        free(data[i]);
    }
    free(data);
}
