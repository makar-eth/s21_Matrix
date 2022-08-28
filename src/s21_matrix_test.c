#include "s21_matrix.h"
#include <check.h>

void run_test(Suite *thesuit) {
  SRunner *therunner = srunner_create(thesuit);

  srunner_set_fork_status(therunner, CK_NOFORK);
  srunner_run_all(therunner, CK_NORMAL);
  srunner_ntests_failed(therunner);
  srunner_free(therunner);

  printf("\n");
}

START_TEST(test_create_1) {
    matrix_t m;
    int result = s21_create_matrix(5, 7, &m);

    ck_assert_int_eq(m.columns, 7);
    ck_assert_int_eq(m.rows, 5);
    ck_assert_int_eq(result, 0);
    
    s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_create_2) {
    matrix_t m;
    int result = s21_create_matrix(1, 1, &m);

    ck_assert_int_eq(m.columns, 1);
    ck_assert_int_eq(m.rows, 1);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_create_3) {
    matrix_t m;
    int result = s21_create_matrix(100, 100, &m);

    ck_assert_int_eq(m.columns, 100);
    ck_assert_int_eq(m.rows, 100);
    ck_assert_int_eq(result, 0);

    s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_create_4) {
    matrix_t m;
    int result = s21_create_matrix(0, 10, &m);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_create_5) {
    matrix_t m;
    int result = s21_create_matrix(2, 0, &m);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_create_6) {
    matrix_t m;
    int result = s21_create_matrix(-1, 0, &m);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_create_7) {
    matrix_t m;
    int result = s21_create_matrix(0, 0, &m);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_create_8) {
    matrix_t m;
    int result = s21_create_matrix(-10, -10, &m);
    ck_assert_int_eq(result, 1);
}
END_TEST

Suite *suite_create_matrix() {
  Suite *s = suite_create("suite_create_matrix");
  TCase *tc = tcase_create("tc_create_matrix");

  tcase_add_test(tc, test_create_1);
  tcase_add_test(tc, test_create_2);
  tcase_add_test(tc, test_create_3);
  tcase_add_test(tc, test_create_4);
  tcase_add_test(tc, test_create_5);
  tcase_add_test(tc, test_create_6);
  tcase_add_test(tc, test_create_7);
  tcase_add_test(tc, test_create_8);

  suite_add_tcase(s, tc);

  return s;
}


int main() {
    Suite *s_create = suite_create_matrix();

    run_test(s_create);

    return 0;
}