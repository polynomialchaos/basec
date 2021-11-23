/*******************************************************************************
 * @file json_parse_strings.c
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
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    JSON_t *root = PARSE_JSON_STRING("{\"a\":[12,13,14,15]}");
    PRINT_JSON_OBJECT_INDENT(root, get_stdout(), -1);

    free_json_object(root);
    DEALLOCATE(root);

    return 0;
}