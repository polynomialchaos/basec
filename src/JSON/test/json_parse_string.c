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
    JSON_t *root = parse_json_string("{\"a\":[12,13,14,15]}");
    print_json_object_indent(root, get_stdout(), -1);

    free_json_object(root);
    DEALLOCATE(root);

    return 0;
}