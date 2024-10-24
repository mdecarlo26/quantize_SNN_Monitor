#ifndef CSV_READER_H
#define CSV_READER_H

#include <stdio.h>
#include <stdlib.h>

// Function prototype for reading a CSV file into a dynamic array
double** read_csv(const char *filename, int *rows, int *cols);

// Function prototype for freeing the dynamically allocated memory
void free_csv_data(double **data, int rows);

#endif  // CSV_READER_H
