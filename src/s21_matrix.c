#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;
  if (rows < 1 || columns < 1) {
    status = ERROR;
  } else {
    result->columns = columns;
    result->rows = rows;
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (result->matrix == NULL) {
      status = ERROR;
    }
    for (size_t i = 0; i < rows; i++) {
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
      if (result->matrix[i] == NULL) {
        status = ERROR;
      }
    }
  }
  return status;
}