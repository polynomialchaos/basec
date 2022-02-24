/*******************************************************************************
 * @file json_parse.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <stdio.h>
#include "basec/utils_module.h"
#include "basec/json_module.h"

/*******************************************************************************
 * @brief Main function
 * @return int
 ******************************************************************************/
int main()
{
    JSON_t *root = BM_PARSE_JSON_FILE("test.json");
    BM_PRINT_JSON_OBJECT(root, get_stdout());

    JSON_t *tmp = BM_GET_JSON_OBJECT_BY_PATH(root, "number vector");
    double *data;
    size_t n;

    BM_GET_JSON_VALUE_N(tmp, JSONNumber, BM_VOID_REF(data), &n);
    BM_PRINT("%ld\n", n);
    BM_DEALLOCATE(data);

    free_json_object(root);
    BM_DEALLOCATE(root);

    return 0;
}