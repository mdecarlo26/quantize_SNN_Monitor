#include <stdio.h>
#include "csv_reader.h"
#include "scaler_overhead.h"

#define QUANTIZE_FLAG 

#ifdef QUANTIZE_FLAG
#include "quantize_random_forest.h"
// #include "quantized_XGB.h"
//#include "quantized_LGBM.h"
#include "quantize_scaler.h"
#include "quantize_inference.h"

#else
// #include "scaler.h"
// #include "inference.h"
// #include "random_forest.h"
#endif

int main()
{
    int row_cnt,col_cnt;
    double **data = read_csv("../data.csv", &row_cnt, &col_cnt);
    //printf("%f, %d\n", data[100][100], data_quantized[100][100]);
    printf("Data loaded: %d rows, %d columns.\n", row_cnt, col_cnt);


    int n_features;
    double *center = NULL;
    double *scale = NULL;
    load_scaler_params("../scaler_vals.csv", &center, &scale, &n_features);
    printf("Scaler loaded: %d rows, %d columns.\n", n_features, 2);

    if (n_features != col_cnt)
    {
        fprintf(stderr, "Scaler file doesn't have the same features as data!\n");
        exit(EXIT_FAILURE);
    }
#ifdef QUANTIZE_FLAG
    int *center_quantize = malloc(n_features * sizeof(int));
    int *scaler_quantize = malloc(n_features * sizeof(int));

    int **data_quantized = quantize_data(data, row_cnt, col_cnt);
    
    quantize_scaler_values(n_features, center, scale, center_quantize, scaler_quantize);

    printf("Quantize Scaling\n");
    apply_robust_scaling_quantize(data_quantized, row_cnt, col_cnt, center_quantize, scaler_quantize);

    int *quantize_pred = malloc(row_cnt * sizeof(int));

    printf("Quantized Tree\n");
    for(int i = 0; i < row_cnt; i++){
        //quantize_pred[i] = apply_random_forest_quantize(data_quantized[i]);
        //quantize_pred[i] = apply_LGBM_quantize(data_quantized[i]);
        quantize_pred[i] = apply_XGB_quantize(data_quantized[i]);
    }

    // double mse_quantize = compute_error_quantized(, quantize_pred, row_cnt);
    
    free(quantize_pred);
    free_scaler_params_quantize(center_quantize, scaler_quantize);
    free_quantized_data(data_quantized, row_cnt);

#else
    // printf("Full Scaling\n");
    // apply_robust_scaling(data, row_cnt, col_cnt, center, scale);

    // double *pred = malloc(row_cnt * sizeof(double));

    // printf("Full Tree\n");
    // for(int i = 0; i < row_cnt; i++){
    //     pred[i] = apply_random_forest(data[i]);
    // }
    // free(pred);

    // double mse = compute_error(, pred, row_cnt);
#endif

    printf("Freeing Data\n");
    free_scaler_params(center, scale);
    free_csv_data(data,row_cnt);
    return 0;
}
