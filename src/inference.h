#ifndef INFERENCE_H
#define INFERENCE_H

int *malloc_quantized_prediction(int row_num);

double *malloc_prediction(int row_num);

double compute_error(double *ground_truth, double *prediction, int row_count);

double compute_error_quantized(double *ground_truth, int *prediction, int row_count);

#endif  // INFERENCE_H