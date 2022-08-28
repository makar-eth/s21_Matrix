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
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
      if (result->matrix[i] == NULL) {
        status = ERROR;
      }
    }
  }
  return status;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
    free(A->matrix);
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = SUCCESS;
  if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL) {
    if (A->rows == B->rows && A->columns == B->columns) {
      int rows = A->rows;
      int columns = A->columns;
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) < EPS) {
            status = FAILURE;
            break;
          }
        }
        if (status == FAILURE) break;
      }
    } else {
      status = CALC_ERROR;
    }
  } else {
    status = ERROR;
  }
  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL) {
    if (A->columns == B->columns && A->rows == B->rows) {
      int rows = A->rows;
      int columns = A->columns;
      int create_status = s21_create_matrix(rows, columns, result);
      if (create_status == 0) {
        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      } else {
        status = ERROR;
      }
    } else {
      status = CALC_ERROR;
    }
  } else {
    status = ERROR;
  }
  return status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL) {
    if (A->columns == B->columns && A->rows == B->rows) {
      int rows = A->rows;
      int columns = A->columns;
      int create_status = s21_create_matrix(rows, columns, result);
      if (create_status == 0) {
        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      } else {
        status = ERROR;
      }
    } else {
      status = CALC_ERROR;
    }
  } else {
    status = ERROR;
  }
  return status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = OK;
  return status;
}