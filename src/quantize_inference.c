#include <stdlib.h>

#define SCALER 1000

int *malloc_quantized_prediction(int row_num)
{
    return malloc(row_num * sizeof(int));
}

double compute_error_quantized(double *ground_truth, int *prediction, int row_count)
{
    double mse = 0.0;
    double *err = malloc(row_count * sizeof(double));

    for (int i = 0; i < row_count; i++) {
        err[i] = ground_truth[i] - ((double)prediction[i] / SCALER);
        mse += err[i] * err[i];
    }

    free(err);

    return mse / row_count;
}
