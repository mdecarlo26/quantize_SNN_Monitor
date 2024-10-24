#include <stdio.h>
#include "csv_reader.h"
#include "scaler.h"
#include "inference.h"
#include "random_forest.h"
#include "quantize_random_forest.h"

int main()
{
    int row_cnt,col_cnt;
    double **data = read_csv("../data.csv", &row_cnt, &col_cnt);
    int **data_quantized = quantize_data(data, row_cnt, col_cnt);
    //printf("%f, %d\n", data[100][100], data_quantized[100][100]);
    printf("Data loaded: %d rows, %d columns.\n", row_cnt, col_cnt);


    int n_features;
    double *center = NULL;
    double *scale = NULL;
    load_scaler_params("../scaler_vals.csv", &center, &scale, &n_features);
    printf("Scaler loaded: %d rows, %d columns.\n", n_features, 2);

    int *center_quantize = malloc(n_features * sizeof(int));
    int *scaler_quantize = malloc(n_features * sizeof(int));
    
    quantize_scaler_values(n_features, center, scale, center_quantize, scaler_quantize);

    if (n_features != col_cnt)
    {
        fprintf(stderr, "Scaler file doesn't have the same features as data!\n");
        exit(EXIT_FAILURE);
    }

    printf("Full Scaling\n");
    apply_robust_scaling(data, row_cnt, col_cnt, center, scale);

    printf("Quantize Scaling\n");
    apply_robust_scaling_quantize(data_quantized, row_cnt, col_cnt, center_quantize, scaler_quantize);

    int *quantize_pred = malloc(row_cnt * sizeof(int));
    double *pred = malloc(row_cnt * sizeof(double));

    printf("Full Tree\n");
    for(int i = 0; i < row_cnt; i++){
        pred[i] = apply_random_forest(data[i]);
    }

    printf("Quantized Tree\n");
    for(int i = 0; i < row_cnt; i++){
        quantize_pred[i] = apply_random_forest_quantize(data_quantized[i]);
    }

    for(int i = 0; i < 5; i++){
        printf("%f, %d, %f\n", pred[i], quantize_pred[i], quantize_pred[i] / SCALER_FLOAT / SCALER_FLOAT);
    }

    // double mse = compute_error(, pred, row_cnt);
    // double mse_quantize = compute_error_quantized(, quantize_pred, row_cnt);
    printf("Freeing Data\n");
    free(quantize_pred);
    free(pred);
    free_scaler_params(center, scale);
    free_scaler_params_quantize(center_quantize, scaler_quantize);
    free_quantized_data(data_quantized, row_cnt);
    free_csv_data(data,row_cnt);
    return 0;
}
