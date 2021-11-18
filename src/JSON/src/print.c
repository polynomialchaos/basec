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

#define JIND 4    /** Space indentation */
#define JWSP " "  /** Whitespace */
#define JNWL "\n" /** Newline */

#define JLBC "{"  /** Left brace */
#define JRBC "}"  /** Right brace */
#define JLBK "["  /** Left bracket */
#define JRBK "]"  /** Left bracket */
#define JSTR "\"" /** String keeper */
#define JOSP ":"  /** Object separator */
#define JVSP ","  /** Value separator */

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
    check_expression_pass(_file, _line, _function, this != NULL);
    size_t n_childs = count_json_childs(this);

    if (this->key != NULL)
    {
        fprintf(file_pointer, JSTR "%s" JSTR JOSP, this->key);
        if (indent >= 0)
            fprintf(file_pointer, JWSP);
    }

    switch (this->type)
    {
    case JSONObject:
    case JSONArray:
        fprintf(file_pointer, this->type == JSONObject ? JLBC : JLBK);
        if (n_childs > 0)
        {
            if (indent >= 0)
                fprintf(file_pointer, JNWL);
            for (size_t i = 0; i < n_childs; ++i)
            {
                if (i != 0)
                {
                    fprintf(file_pointer, JVSP);
                    if (indent >= 0)
                        fprintf(file_pointer, JNWL);
                }

                if (indent >= 0)
                    fprintf(file_pointer, "%*s", (indent + 1) * JIND, "");
                print_json_object_pass(_file, _line, _function,
                                       list_get_ith(this->childs, i),
                                       file_pointer,
                                       (indent >= 0) ? indent + 1 : indent);
            }
            if (indent >= 0)
                fprintf(file_pointer, JNWL "%*s", (indent + 0) * JIND, "");
        }
        fprintf(file_pointer, this->type == JSONObject ? JRBC : JRBK);
        break;
    case JSONNull:
        fprintf(file_pointer, JNLL);
        break;
    case JSONBoolean:
        if (this->boolean)
            fprintf(file_pointer, JTRU);
        else
            fprintf(file_pointer, JFLS);
        break;
    case JSONDigit:
        fprintf(file_pointer, "%d", this->digit);
        break;
    case JSONNumber:
        fprintf(file_pointer, "%e", this->number);
        break;
    case JSONString:
        fprintf(file_pointer, JSTR "%s" JSTR, this->string);
        break;
    default:
        log_error_pass(_file, _line, _function, JERR, this->type);
        break;
    }

    if (this->parent == NULL)
        fprintf(file_pointer, JNWL);
}