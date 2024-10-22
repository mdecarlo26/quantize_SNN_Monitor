#include <stdio.h>
#include "csv_reader.h"
#include "scaler.h"

int main()
{
    int row_cnt,col_cnt;
    double **data = read_csv("../data.csv", &row_cnt, &col_cnt);
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

    printf("Scaling\n");
    apply_robust_scaling(data, row_cnt, col_cnt, center, scale);

    free_scaler_params(center, scale);
    free_csv_data(data,row_cnt);
    return 0;
}