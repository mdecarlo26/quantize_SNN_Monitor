#include <stdlib.h>

#define SCALER 1000

double *malloc_prediction(int row_num)
{
    return malloc(row_num * sizeof(double));
}

// mean squared error
double compute_error(double *ground_truth, double *prediction, int row_count)
{
    double mse = 0.0;
    double *err = malloc(row_count * sizeof(double));

    for (int i = 0; i < row_count; i++) {
        err[i] = ground_truth[i] - prediction[i];
        mse += err[i] * err[i];
    }

    free(err);

    return mse / row_count;
}
