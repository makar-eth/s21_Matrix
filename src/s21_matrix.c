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
  }
  free(A->matrix);
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
  if (A->matrix != NULL && A != NULL) {
    int rows = A->rows;
    int columns = A->columns;
    int create_status = s21_create_matrix(rows, columns, result);
    if (create_status == 0) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          result->matrix[i][j] = number * A->matrix[i][j];
        }
      }
    } else {
      status = ERROR;
    }
  } else {
    status = ERROR;
  }
  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL) {
    if (A->columns == B->rows) {
      status = s21_create_matrix(A->rows, B->columns, result);
       if (status == 0) {
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            double sum = 0;
            for (int k = 0; k < A->columns; k++) {
              sum += A->matrix[i][k] * B->matrix[k][j];
            }
            result->matrix[i][j] = sum;
          }
        }
      }
    } else {
      status = CALC_ERROR;
    }
  } else {
    status = ERROR;
  }
  return status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (A->matrix != NULL && A != NULL) {
    int rows = A->rows;
    int columns = A->columns;
    int create_status = s21_create_matrix(columns, rows, result);
    if (create_status == 0) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    } else {
      status = ERROR;
    }
  } else {
    status = ERROR;
  }
  return status;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (A != NULL && A->matrix != NULL) {
    if (A->columns == A->rows) {
      int grade = A->rows;
      int create_status = s21_create_matrix(grade, grade, result);
      if (create_status == 0) {
        for (int i = 0; i < grade; i++) {
          for (int j = 0; j < grade; j++) {
            matrix_t *buf = NULL;
            s21_create_matrix(grade - 1, grade - 1, buf);
            s21_fill_minor(A, buf, i, j);
            double *minor_determinant = NULL;
            s21_determinant(buf, minor_determinant);
            result->matrix[i][j] = *minor_determinant;
            s21_remove_matrix(buf);
          }
        }
        for (int i = 0; i < grade; i++) {
          for (int j = 0; j < grade; j++) {
            result->matrix[i][j] = result->matrix[i][j] * pow((-1), i + j);
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

int s21_determinant(matrix_t *A, double *result) {
  int status = OK;
  if (A != NULL && A->matrix != NULL) {
    if (A->columns == A->rows) {
      int grade = A->rows;
      if (grade == 1) {
        *result = A->matrix[0][0];
      } else if (grade > 1) {
        *result = 0;
        for (int j = 0; j < grade; j++) {
          matrix_t *buf = NULL;
          s21_create_matrix(grade - 1, grade - 1, buf);
          s21_fill_minor(A, buf, 0, j);
          double *minor_determinant = NULL;
          s21_determinant(buf, minor_determinant);
          s21_remove_matrix(buf);
          *result += pow(-1, j) * A->matrix[0][j] * (*minor_determinant);
        }
      }
    } else {
      status = CALC_ERROR;
    }
  } else {
    status = ERROR;
  }
  return status;
}

int s21_fill_minor(matrix_t *A, matrix_t *B, int row, int column) {
  int grade = A->rows;
  int minor_column = 0;
  int minor_row = 0;
  for (int i = 0; i < grade; i++) {
    for (int j = 0; j < grade; j++) {
      if (i != row && j != column) {
        if (minor_column == grade - 1) {
          minor_row++;
          minor_column = 0;
        }
        B->matrix[minor_row][minor_column] = A->matrix[i][j];
        minor_column++;
      }
    }
  }
  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (A->matrix != NULL && A != NULL) {
    double *D = NULL;
    if (s21_determinant(A, D) == 0 && *D != 0) {
      matrix_t *buf = NULL;
      status = s21_calc_complements(A, buf);
      if (status == 0) {
        status = s21_transpose(buf, result);
        s21_remove_matrix(buf);
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