/*******************************************************************************
 * @file json.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include "json_private.h"

/*******************************************************************************
 * @brief Create a JSON object child and pass file, line, function
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @return JSON_t*
 ******************************************************************************/
JSON_t *create_json_child_pass(cstring_t _file, int _line, cstring_t _function,
                               JSON_t *this)
{
    CHECK_EXPRESSION_PASS(_file, _line, _function, this != NULL);
    CHECK_EXPRESSION_PASS(_file, _line, _function,
                          (this->type == JSONObject) ||
                              (this->type == JSONArray));

    if (this->childs == NULL)
    {
        this->childs = list_allocate_pass(_file, _line, _function,
                                          free_json_object);
    }

    JSON_t *child = create_json_object();
    LIST_APPEND(this->childs, sizeof(JSON_t), child);
    DEALLOCATE(child);

    child = LIST_GET_LAST(this->childs);
    child->parent = this;

    return child;
}

/*******************************************************************************
 * @brief Create a JSON object
 * @return JSON_t*
 ******************************************************************************/
JSON_t *create_json_object()
{
    JSON_t *this = ALLOCATE(sizeof(JSON_t));

    this->key = NULL;
    this->type = _JSONUndefined;
    this->parent = NULL;
    this->childs = NULL;
    this->string = NULL;

    return this;
}

/*******************************************************************************
 * @brief Count number of JSON object childs
 * @param[in] this
 * @return size_t
 ******************************************************************************/
size_t count_json_childs(JSON_t *this)
{
    return list_length(this->childs);
}

/*******************************************************************************
 * @brief Deallocate a JSON object
 * @param[in] this
 ******************************************************************************/
void free_json_object(void *this)
{
    if (this == NULL)
        return;

    JSON_t *this_value = this;

    if (this_value->key != NULL)
        DEALLOCATE(this_value->key);

    if (this_value->childs != NULL)
        LIST_DEALLOCATE(this_value->childs);

    DEALLOCATE(this_value->childs);

    if (this_value->string != NULL)
        DEALLOCATE(this_value->string);
}