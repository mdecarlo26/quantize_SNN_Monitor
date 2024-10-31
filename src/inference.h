#ifndef INFERENCE_H
#define INFERENCE_H

double *malloc_prediction(int row_num);

double compute_error(double *ground_truth, double *prediction, int row_count);

#endif  // INFERENCE_H
