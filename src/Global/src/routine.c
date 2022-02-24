/*******************************************************************************
 * @file routine.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <string.h>
#include "global_private.h"

/*******************************************************************************
 * @brief Handler structure
 ******************************************************************************/
typedef struct HandlerData
{
    string_t file;    /** File string */
    void_ft function; /** Function pointer */
} handler_data_t;

list_t *initialize_list = NULL; /** Initialize list header */
list_t *finalize_list = NULL;   /** Finalize list header */

/*******************************************************************************
 * @brief Call routines list
 * @param routines
 * @param title
 ******************************************************************************/
void call_routines(list_t *routines, cstring_t title)
{
    BM_PRINT("\n");
    printf_r_sep_title(GBMS, title);

    const size_t n = list_length(routines);
    for (size_t i = 0; i < n; ++i)
    {
        handler_data_t *this = BM_LIST_GET_ITH(routines, i);
        BM_PRINT(" * %s\n", this->file);
        this->function();
        check_abort(0);
        if (i < n - 1)
            printf_r_sep('-');
    }

    printf_r_sep(GBMS);
}

/*******************************************************************************
 * @brief Deallocate routines list data
 * @param this
 ******************************************************************************/
void free_routine_hanlder(void *this)
{
    handler_data_t *this_value = this;

    BM_DEALLOCATE(this_value->file);
    this_value->function = NULL;
}

/*******************************************************************************
 * @brief Initialize routines list
 * @return list_t*
 ******************************************************************************/
list_t *init_routines()
{
    list_t *routines = BM_ALLOCATE(sizeof(list_t));
    BM_LIST_INIT(routines, free_routine_hanlder);

    return routines;
}

/*******************************************************************************
 * @brief Call the list of initialize functions
 ******************************************************************************/
void call_initialize_list()
{
    call_routines(initialize_list, "Initialize");

    if (initialize_list != NULL)
        BM_LIST_DEALLOCATE(initialize_list);
    BM_DEALLOCATE(initialize_list);
}

/*******************************************************************************
 * @brief Call the list of finalize functions
 ******************************************************************************/
void call_finalize_list()
{
    call_routines(finalize_list, "Finalize");

    if (finalize_list != NULL)
        BM_LIST_DEALLOCATE(finalize_list);
    BM_DEALLOCATE(finalize_list);
}

/*******************************************************************************
 * @brief Register a initialize routine
 * @param _file
 * @param fun_ptr
 ******************************************************************************/
void register_initialize_routine_pass(cstring_t _file, void_ft function)
{
    if (initialize_list == NULL)
        initialize_list = init_routines();

    BM_LIST_APPEND(initialize_list, sizeof(handler_data_t), NULL);
    handler_data_t *last = BM_LIST_GET_LAST(initialize_list);

    last->file = allocate_strcpy(_file);
    last->function = function;
}

/*******************************************************************************
 * @brief Register a finalize routine
 * @param _file
 * @param fun_ptr
 ******************************************************************************/
void register_finalize_routine_pass(cstring_t _file, void_ft function)
{
    if (finalize_list == NULL)
        finalize_list = init_routines();

    BM_LIST_PREPEND(finalize_list, sizeof(handler_data_t), NULL);
    handler_data_t *first = BM_LIST_GET_FIRST(finalize_list);

    first->file = allocate_strcpy(_file);
    first->function = function;
}
