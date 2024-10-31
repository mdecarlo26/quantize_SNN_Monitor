#ifndef QUANTIZE_INFERENCE_H
#define QUANTIZE_INFERENCE_H

int *malloc_quantized_prediction(int row_num);

double compute_error_quantized(double *ground_truth, int *prediction, int row_count);

#endif  // QUANTIZE_INFERENCE_H
