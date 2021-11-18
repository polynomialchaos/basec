/*******************************************************************************
 * @file json.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "json_private.h"

/*******************************************************************************
 * @brief Create a JSON object child and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @return JSON_t*
 ******************************************************************************/
JSON_t *create_json_child_pass(cstring_t _file, int _line, cstring_t _function,
                               JSON_t *this)
{
    check_expression_pass(_file, _line, _function, this != NULL);
    check_expression_pass(_file, _line, _function,
                          (this->type == JSONObject) || (this->type == JSONArray));

    if (this->childs == NULL)
    {
        this->childs = list_allocate_pass(_file, _line, _function,
                                          free_json_object);
    }

    JSON_t *child = create_json_object();
    list_append(this->childs, sizeof(JSON_t), child);
    DEALLOCATE(child);

    child = list_get_last(this->childs);
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
 * @param this
 * @return size_t
 ******************************************************************************/
size_t count_json_childs(JSON_t *this)
{
    return list_length(this->childs);
}

/*******************************************************************************
 * @brief Deallocate a JSON object
 * @param this
 ******************************************************************************/
void free_json_object(void *this)
{
    if (this == NULL)
        return;

    JSON_t *this_value = this;

    if (this_value->key != NULL)
        DEALLOCATE(this_value->key);

    if (this_value->childs != NULL)
        list_deallocate(this_value->childs);

    DEALLOCATE(this_value->childs);

    if (this_value->string != NULL)
        DEALLOCATE(this_value->string);
}