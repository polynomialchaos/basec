/*******************************************************************************
 * @file main.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdio.h>
#include "basec/utils_module.h"
#include "basec/json_module.h"

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    JSON_t *root = parse_json_file("test.json");
    print_json_object(root, get_stdout());

    JSON_t *tmp = get_json_object_by_path(root, "number vector");
    double *data;
    size_t n;

    get_json_value_n(tmp, JSONNumber, VOID_REF(data), &n);
    printf_r("%ld\n", n);
    DEALLOCATE(data);

    free_json_object(root);
    DEALLOCATE(root);

    return 0;
}