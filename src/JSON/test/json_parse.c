/*******************************************************************************
 * @file json_parse.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2021-11-23
 * @copyright Copyright (c) 2021
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
    JSON_t *root = PARSE_JSON_FILE("test.json");
    PRINT_JSON_OBJECT(root, get_stdout());

    JSON_t *tmp = GET_JSON_OBJECT_BY_PATH(root, "number vector");
    double *data;
    size_t n;

    GET_JSON_VALUE_N(tmp, JSONNumber, VOID_REF(data), &n);
    PRINTF("%ld\n", n);
    DEALLOCATE(data);

    free_json_object(root);
    DEALLOCATE(root);

    return 0;
}