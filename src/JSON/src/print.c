/*******************************************************************************
 * @file json.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "json_private.h"

/*******************************************************************************
 * @brief Print a JSON object and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param file_pointer
 * @param indent
 ******************************************************************************/
void print_json_object_pass(cstring_t _file, int _line, cstring_t _function,
                            JSON_t *this, FILE *file_pointer, int indent)
{
    check_expression_pass(_file, _line, _function, (this != NULL));
    size_t n_childs = count_json_childs(this);

    if (this->key != NULL)
    {
        fprintf(file_pointer, "\"%s\":", this->key);
        if (indent >= 0)
            fprintf(file_pointer, " ");
    }

    switch (this->type)
    {
    case JSONObject:
        fprintf(file_pointer, "{");
        if (n_childs > 0)
        {
            if (indent >= 0)
                fprintf(file_pointer, "\n");
            for (size_t i = 0; i < n_childs; ++i)
            {
                if (i != 0)
                    fprintf(file_pointer, ",");
                if ((i != 0) && (indent >= 0))
                    fprintf(file_pointer, "\n");
                if (indent >= 0)
                    fprintf(file_pointer, "%*s", (indent + 1) * 4, "");
                print_json_object_pass(_file, _line, _function,
                                       list_get_ith(this->childs, i),
                                       file_pointer,
                                       (indent >= 0) ? indent + 1 : indent);
            }
            if (indent >= 0)
                fprintf(file_pointer, "\n");
            if (indent >= 0)
                fprintf(file_pointer, "%*s", (indent)*4, "");
        }
        fprintf(file_pointer, "}");
        break;
    case JSONArray:
        fprintf(file_pointer, "[");
        if (n_childs > 0)
        {
            if (indent >= 0)
                fprintf(file_pointer, "\n");
            for (size_t i = 0; i < n_childs; ++i)
            {
                if (i != 0)
                    fprintf(file_pointer, ",");
                if ((i != 0) && (indent >= 0))
                    fprintf(file_pointer, "\n");
                if (indent >= 0)
                    fprintf(file_pointer, "%*s", (indent + 1) * 4, "");
                print_json_object_pass(_file, _line, _function,
                                       list_get_ith(this->childs, i),
                                       file_pointer,
                                       (indent >= 0) ? indent + 1 : indent);
            }
            if (indent >= 0)
                fprintf(file_pointer, "\n");
            if (indent >= 0)
                fprintf(file_pointer, "%*s", (indent)*4, "");
        }
        fprintf(file_pointer, "]");
        break;
    case JSONNull:
    case _JSONUndefined:
        fprintf(file_pointer, JSON_NULL);
        break;
    case JSONBoolean:
        if (this->boolean)
            fprintf(file_pointer, JSON_TRUE);
        else
            fprintf(file_pointer, JSON_FALSE);
        break;
    case JSONDigit:
        fprintf(file_pointer, "%d", this->digit);
        break;
    case JSONNumber:
        fprintf(file_pointer, "%e", this->number);
        break;
    case JSONString:
        fprintf(file_pointer, "\"%s\"", this->string);
        break;
    default:
        log_error_pass(_file, _line, _function, JSON_ERROR, this->type);
        break;
    }

    if (this->parent == NULL)
        fprintf(file_pointer, "\n");
}