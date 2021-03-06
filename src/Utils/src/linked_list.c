/*******************************************************************************
 * @file linked_list.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <string.h>
#include "utils_private.h"

/*******************************************************************************
 * @brief Get the ith node
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @param[in] ith
 * @return node_t*
 ******************************************************************************/
node_t *list_get_ith_node(cstring_t _file, int _line, cstring_t _function,
                          list_t *list, size_t ith);

/*******************************************************************************
 * @brief Deallocate a node
 * @param[in] node
 * @param[in] fun_ptr
 ******************************************************************************/
void list_deallocate_node(node_t *node, void_void_ft fun_ptr);

/*******************************************************************************
 * @brief Allocate and initialize a linked list and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] fun_ptr
 * @return list_t*
 ******************************************************************************/
list_t *list_allocate_pass(cstring_t _file, int _line, cstring_t _function,
                           void_void_ft fun_ptr)
{
    list_t *list = BM_ALLOCATE(sizeof(list_t));
    list_init_pass(_file, _line, _function, list, fun_ptr);
    return list;
}

/*******************************************************************************
 * @brief Call a function for each node and check for all results
 * and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @param[in] fun_ptr
 * @return bool_t
 ******************************************************************************/
bool_t list_all_pass(cstring_t _file, int _line, cstring_t _function,
                     list_t *list, bool_void_ft fun_ptr)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, list != NULL);
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, fun_ptr != NULL);

    bool_t result = BC_FALSE;

    node_t *node = list->head;
    while (node != NULL)
    {
        result = fun_ptr(node->data);
        if (!result)
            break;
        node = node->next;
    }

    return result;
}

/*******************************************************************************
 * @brief Append a node to a linked list and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @param[in] size
 * @param[in] data
 ******************************************************************************/
void list_append_pass(cstring_t _file, int _line, cstring_t _function,
                      list_t *list, size_t size, void *data)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, list != NULL);
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, size > 0);

    node_t *new = BM_ALLOCATE(sizeof(node_t));
    new->data = BM_ALLOCATE(size);
    if (data != NULL)
        memcpy(new->data, data, size);

    new->next = NULL;
    new->previous = list->tail;

    if (new->previous != NULL)
        new->previous->next = new;

    list->tail = new;
    if (list->head == NULL)
        list->head = list->tail;

    list->length++;
}

/*******************************************************************************
 * @brief Call a function for each node and check for any result
 * and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @param[in] fun_ptr
 * @return bool_t
 ******************************************************************************/
bool_t list_any_pass(cstring_t _file, int _line, cstring_t _function,
                     list_t *list, bool_void_ft fun_ptr)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, list != NULL);
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, fun_ptr != NULL);

    bool_t result = BC_FALSE;

    node_t *node = list->head;
    while (node != NULL)
    {
        result = fun_ptr(node->data);
        if (result)
            break;
        node = node->next;
    }

    return result;
}

/*******************************************************************************
 * @brief Deallocate the ith node in a linked list
 * and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @param[in] ith
 ******************************************************************************/
void list_deallocate_ith_pass(cstring_t _file, int _line, cstring_t _function,
                              list_t *list, size_t ith)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, list != NULL);
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, list->length > 0);
    node_t *current = list_get_ith_node(_file, _line, _function, list, ith);

    if (list->head == current)
        list->head = current->next;

    if (list->tail == current)
        list->tail = current->previous;

    if (current->previous != NULL)
        current->previous->next = current->next;

    if (current->next != NULL)
        current->next->previous = current->previous;

    list_deallocate_node(current, list->deallocate);
    list->length--;
}

/*******************************************************************************
 * @brief Deallocate a node
 * @param[in] node
 * @param[in] fun_ptr
 ******************************************************************************/
void list_deallocate_node(node_t *node, void_void_ft fun_ptr)
{
    if (node == NULL)
        return;

    if (fun_ptr != NULL)
        fun_ptr(node->data);

    BM_DEALLOCATE(node->data);
    BM_DEALLOCATE(node);
}

/*******************************************************************************
 * @brief Deallocate a linked list and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 ******************************************************************************/
void list_deallocate_pass(cstring_t _file, int _line, cstring_t _function,
                          list_t *list)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, list != NULL);

    node_t *current = list->head;
    while (current != NULL)
    {
        node_t *next = current->next;
        list_deallocate_node(current, list->deallocate);
        list->length--;
        current = next;
    }

    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, list->length == 0);
}

/*******************************************************************************
 * @brief Call a function for each node and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @param[in] fun_ptr
 ******************************************************************************/
void list_for_each_pass(cstring_t _file, int _line, cstring_t _function,
                        list_t *list, void_void_ft fun_ptr)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, list != NULL);
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, fun_ptr != NULL);

    node_t *node = list->head;
    while (node != NULL)
    {
        fun_ptr(node->data);
        node = node->next;
    }
}

/*******************************************************************************
 * @brief Get first node in a linked list and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @return void*
 ******************************************************************************/
void *list_get_first_pass(cstring_t _file, int _line, cstring_t _function,
                          list_t *list)
{
    return list_get_ith_pass(_file, _line, _function, list, 0);
}

/*******************************************************************************
 * @brief Get the ith node and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @param[in] ith
 * @return node_t*
 ******************************************************************************/
node_t *list_get_ith_node(cstring_t _file, int _line, cstring_t _function,
                          list_t *list, size_t ith)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, list != NULL);
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, ith < list_length(list));

    node_t *current = list->head;
    for (size_t i = 0; i < ith; ++i)
        current = current->next;

    return current;
}

/*******************************************************************************
 * @brief Get ith node in a linked list and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @param[in] ith
 * @return void*
 ******************************************************************************/
void *list_get_ith_pass(cstring_t _file, int _line, cstring_t _function,
                        list_t *list, size_t ith)
{
    node_t *node = list_get_ith_node(_file, _line, _function, list, ith);
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, node != NULL);
    return node->data;
}

/*******************************************************************************
 * @brief Get last node in a linked list and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @return void*
 ******************************************************************************/
void *list_get_last_pass(cstring_t _file, int _line, cstring_t _function,
                         list_t *list)
{
    int idx = list_length(list) - 1;
    return list_get_ith_pass(_file, _line, _function, list, idx);
}

/*******************************************************************************
 * @brief Initialize a linked list and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @param[in] fun_ptr
 ******************************************************************************/
void list_init_pass(cstring_t _file, int _line, cstring_t _function,
                    list_t *list, void_void_ft fun_ptr)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, list != NULL);

    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    list->deallocate = fun_ptr;
}

/*******************************************************************************
 * @brief Return the number of a linked list elements
 * @param[in] list
 * @return size_t
 ******************************************************************************/
size_t list_length(list_t *list)
{
    return (list == NULL) ? 0 : list->length;
}

/*******************************************************************************
 * @brief Prepend a node to a linked list and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @param[in] size
 * @param[in] data
 ******************************************************************************/
void list_prepend_pass(cstring_t _file, int _line, cstring_t _function,
                       list_t *list, size_t size, void *data)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, list != NULL);
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, size > 0);

    node_t *new = BM_ALLOCATE(sizeof(node_t));

    new->data = BM_ALLOCATE(size);
    if (data != NULL)
        memcpy(new->data, data, size);

    new->next = list->head;
    new->previous = NULL;

    if (new->next != NULL)
        new->next->previous = new;

    list->head = new;
    if (list->tail == NULL)
        list->tail = list->head;

    list->length++;
}