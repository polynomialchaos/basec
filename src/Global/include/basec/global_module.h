/*******************************************************************************
 * @file global_module.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef GLOBAL_MODULE_H
#define GLOBAL_MODULE_H

#include "basec/basec_macro.h"
#include "basec/basec_type.h"
#include "basec/utils_module.h"

/*******************************************************************************
 * @brief A macro to register a initialize routine
 ******************************************************************************/
#define BM_REGISTER_INITIALIZE_ROUTINE(fun_ptr) \
    register_initialize_routine_pass(__FILE__, (fun_ptr))

/*******************************************************************************
 * @brief A macro to register a finalize routine
 ******************************************************************************/
#define BM_REGISTER_FINALIZE_ROUTINE(fun_ptr) \
    register_finalize_routine_pass(__FILE__, (fun_ptr))

/*******************************************************************************
 * @brief Global initialize
 * @param argc
 * @param argv
 * @param use_mpi
 * @param only_rank
 * @param file_out
 * @param use_arguments
 ******************************************************************************/
void global_initialize(int argc, string_t *argv, bool_t use_mpi,
                       bool_t only_rank, bool_t file_out, bool_t use_arguments);

/*******************************************************************************
 * @brief Register a initialize routine
 * @param _file
 * @param fun_ptr
 ******************************************************************************/
void register_initialize_routine_pass(cstring_t _file, void_ft fun_ptr);

/*******************************************************************************
 * @brief Register a finalize routine
 * @param _file
 * @param fun_ptr
 ******************************************************************************/
void register_finalize_routine_pass(cstring_t _file, void_ft fun_ptr);

#endif /* GLOBAL_MODULE_H */