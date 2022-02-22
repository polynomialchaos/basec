/*******************************************************************************
 * @file json_parse_strings.c
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
    JSON_t *root = PARSE_JSON_STRING("{\"a\":[12,13,14,15]}");
    PRINT_JSON_OBJECT_INDENT(root, get_stdout(), -1);

    free_json_object(root);
    DEALLOCATE(root);

    return 0;
}