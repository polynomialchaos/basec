/*******************************************************************************
 * @file string_conversion.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdio.h>
#include "basec/basec_module.h"

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    // double clock_time = 0.0;

    // int *tes = ALLOCATE(12 * sizeof(int));
    // tes = REALLOCATE(tes, 15 * sizeof(int));
    // DEALLOCATE(tes);

    // string_t test_string = allocate_strcpy("Hallo du .....");
    // printf_r("%s\n", test_string);
    // DEALLOCATE(test_string);

    // bool_t value_b;
    // string_to("True", VariableBoolean, &value_b);
    // printf_r("%d\n", value_b);

    // size_t n = 0;
    // bool_t *values_b = NULL;
    // string_to_n("[0,1,True,False]", VariableBoolean, as_void_ref(values_b), &n);
    // for (size_t i = 0; i < n - 1; ++i)
    //     printf_r("%d, ", values_b[i]);
    // printf_r("%d\n", values_b[n - 1]);
    // DEALLOCATE(values_b);

    // int value_i;
    // string_to("1234", VariableDigit, &value_i);
    // printf_r("%d\n", value_i);

    // int *values_i;
    // string_to_n("[1,2,3,4,5,6,7,8,9,10]", VariableDigit, as_void_ref(values_i), &n);
    // for (size_t i = 0; i < n - 1; ++i)
    //     printf_r("%d, ", values_i[i]);
    // printf_r("%d\n", values_i[n - 1]);
    // DEALLOCATE(values_i);

    // double value_d;
    // string_to("1234", VariableNumber, &value_d);
    // printf_r("%e\n", value_d);

    // double *values_d = NULL;
    // string_to_n("[0,1,2,3,4]", VariableNumber, as_void_ref(values_d), &n);
    // for (size_t i = 0; i < n - 1; ++i)
    //     printf_r("%e, ", values_d[i]);
    // printf_r("%e\n", values_d[n - 1]);
    // DEALLOCATE(values_d);

    // string_t value_c = NULL;
    // char string[] = " 1234      ";
    // string_to(trim(&string[0]), VariableString, &value_c);
    // printf_r("'%s' from '%s'\n", value_c, string);
    // DEALLOCATE(value_c);

    // string_t *values_c = NULL;
    // string_to_n("[Hello, Wolrd      ,   for,you]", VariableString, as_void_ref(values_c), &n);
    // for (size_t i = 0; i < n - 1; ++i)
    //     printf_r("%s, ", values_c[i]);
    // printf_r("%s\n", values_c[n - 1]);
    // for (size_t i = 0; i < n; ++i)
    //     DEALLOCATE(values_c[i]);
    // DEALLOCATE(values_c);

    // printf_r("%d %d %d\n", is_equal("test", "1234"), is_equal(NULL, NULL), is_equal("ddddd", "ddddd"));

    // string_t date = get_date_string_now();
    // string_t time = get_time_string_now();
    // string_t datetime = get_date_time_string_now();

    // clock_time = get_clock_time(clock_time);
    // string_t clock_time_string = get_clock_time_string(clock_time);

    // printf_r("%s %s ... %s / %s\n", date, time, datetime, clock_time_string);

    // DEALLOCATE(date);
    // DEALLOCATE(time);
    // DEALLOCATE(datetime);
    // DEALLOCATE(clock_time_string);

    // FILE *tmp = create_file("test.dat");
    // close_file(tmp);
    // tmp = open_file("test.dat");
    // close_file(tmp);
    // printf_r("File: %d\n", file_exists("test.dat"));

    // int test_val = 12;
    // list_t test;
    // list_init(&test, NULL);
    // list_append(&test, sizeof(int), &test_val);
    // list_prepend(&test, sizeof(int), &test_val);
    // list_append(&test, sizeof(int), &test_val);
    // list_append(&test, sizeof(int), &test_val);
    // list_append(&test, sizeof(int), &test_val);
    // list_append(&test, sizeof(int), &test_val);
    // list_prepend(&test, sizeof(int), &test_val);
    // list_prepend(&test, sizeof(int), &test_val);
    // list_deallocate(&test);

    // set_exit_with_failure(0);
    // // log_debug( "Dummy debug message!" );
    // // log_debug_pass( "tmp", 1, "tmp", "Dummy debug message!" );

    // // log_info( "Dummy info message!" );
    // // log_info_pass( "tmp", 1, "tmp", "Dummy detailed info message!" );

    // set_warning("Dummy warning message!");
    // set_warning_pass("tmp", 1, "tmp", "Dummy warning message!");

    // // set_error( "Dummy error message!" );
    // set_error_pass("tmp", 1, "tmp", "Dummy error message!");

    // check_error(false);
    // check_error(true);

    // check_abort(1);

    return 0;
}