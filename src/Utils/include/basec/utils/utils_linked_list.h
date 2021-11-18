/*******************************************************************************
 * @file utils_linked_list.h
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef UTILS_LINKED_LIST_H
#define UTILS_LINKED_LIST_H

#include <stdlib.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief A macro to allocate and initialize a linked list
 ******************************************************************************/
#define list_allocate(fun_ptr) list_allocate_pass(__PASS__, (fun_ptr))

/*******************************************************************************
 * @brief A macro to call a function for each node and check for all results
 ******************************************************************************/
#define list_all(list, fun_ptr) list_all_pass(__PASS__, (list), (fun_ptr))

/*******************************************************************************
 * @brief A macro to append a node to a linked list
 ******************************************************************************/
#define list_append(list, size, element) \
    list_append_pass(__PASS__, (list), (size), (element))

/*******************************************************************************
 * @brief A macro to call a function for each node and check for any result
 ******************************************************************************/
#define list_any(list, fun_ptr) list_any_pass(__PASS__, (list), (fun_ptr))

/*******************************************************************************
 * @brief A macro to deallocate the ith node in a linked list
 ******************************************************************************/
#define list_deallocate_ith(list, ith) \
    list_deallocate_ith_pass(__PASS__, (list), (ith))

/*******************************************************************************
 * @brief A macro to deallocate a linked list
 ******************************************************************************/
#define list_deallocate(list) list_deallocate_pass(__PASS__, (list))

/*******************************************************************************
 * @brief A macro to call a function for each node
 ******************************************************************************/
#define list_for_each(list, fun_ptr) \
    list_for_each_pass(__PASS__, (list), (fun_ptr))

/*******************************************************************************
 * @brief A macro to get first node in a linked list
 ******************************************************************************/
#define list_get_first(list) list_get_first_pass(__PASS__, (list))

/*******************************************************************************
 * @brief A macro to get ith node in a linked list
 ******************************************************************************/
#define list_get_ith(list, ith) list_get_ith_pass(__PASS__, (list), (ith))

/*******************************************************************************
 * @brief A macro to get last node in a linked list
 ******************************************************************************/
#define list_get_last(list) list_get_last_pass(__PASS__, (list))

/*******************************************************************************
 * @brief A macro to initialize a linked list
 ******************************************************************************/
#define list_init(list, fun_ptr) list_init_pass(__PASS__, (list), (fun_ptr))

/*******************************************************************************
 * @brief  A macro to prepend a node to a linked list
 ******************************************************************************/
#define list_prepend(list, size, element) \
    list_prepend_pass(__PASS__, (list), (size), (element))

/** Linked list void return function type */
typedef void (*void_void_ft)(void *);

/** Linked list bool_t return function type */
typedef bool_t (*bool_void_ft)(void *);

/*******************************************************************************
 * @brief Linked list node structure
 ******************************************************************************/
typedef struct Node
{
    void *data;            /** Node data */
    struct Node *next;     /** Next node */
    struct Node *previous; /** Previous node */
} node_t;

/*******************************************************************************
 * @brief Linked list structure
 ******************************************************************************/
typedef struct List
{
    size_t length;           /** List length */
    node_t *head;            /** List header */
    node_t *tail;            /** List tail */
    void_void_ft deallocate; /** List node deallocate function */
} list_t;

/*******************************************************************************
 * @brief Allocate and initialize a linked list and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] fun_ptr
 * @return list_t*
 ******************************************************************************/
list_t *list_allocate_pass(cstring_t _file, int _line, cstring_t _function,
                           void_void_ft fun_ptr);

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
                     list_t *list, bool_void_ft fun_ptr);

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
                      list_t *list, size_t size, void *data);

/*******************************************************************************
 * @brief Call a function for each node and check for any result
 * and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @param[in] fun_ptr
 * @return true
 * @return false
 ******************************************************************************/
bool_t list_any_pass(cstring_t _file, int _line, cstring_t _function,
                     list_t *list, bool_void_ft fun_ptr);

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
                              list_t *list, size_t ith);

/*******************************************************************************
 * @brief Deallocate a linked list and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 ******************************************************************************/
void list_deallocate_pass(cstring_t _file, int _line, cstring_t _function,
                          list_t *list);

/*******************************************************************************
 * @brief Call a function for each node and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @param[in] fun_ptr
 ******************************************************************************/
void list_for_each_pass(cstring_t _file, int _line, cstring_t _function,
                        list_t *list, void_void_ft fun_ptr);

/*******************************************************************************
 * @brief Get first node in a linked list and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @return void*
 ******************************************************************************/
void *list_get_first_pass(cstring_t _file, int _line, cstring_t _function,
                          list_t *list);

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
                        list_t *list, size_t ith);

/*******************************************************************************
 * @brief Get last node in a linked list and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @return void*
 ******************************************************************************/
void *list_get_last_pass(cstring_t _file, int _line, cstring_t _function,
                         list_t *list);

/*******************************************************************************
 * @brief Initialize a linked list and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] list
 * @param[in] fun_ptr
 ******************************************************************************/
void list_init_pass(cstring_t _file, int _line, cstring_t _function,
                    list_t *list, void_void_ft fun_ptr);

/*******************************************************************************
 * @brief Return the number of a linked list elements
 * and pass file, line, function
 * @param[in] list
 * @return size_t
 ******************************************************************************/
size_t list_length(list_t *list);

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
                       list_t *list, size_t size, void *data);

#endif /* UTILS_LINKED_LIST_H */