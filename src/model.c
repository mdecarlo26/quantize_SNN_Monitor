// model.c
#include <stdio.h>
#include <stdlib.h>

#define FEATURE_SIZE 550

void apply_robust_scaler(double *input, double *output, double *medians, double *iqr) {
    for (int i = 0; i < FEATURE_SIZE; i++) {
        output[i] = (input[i] - medians[i]) / iqr[i];
    }
}

// void convert_input_double_to

int run_inference(double *input) {
    // Here, implement the logic for running inference with your quantized model
    // For example:
    // - Use the quantized decision tree logic
    // - Return the predicted class (0 or 1 in this case)
    return (input[0] > 0) ? 1 : 0;  // Placeholder logic
}
