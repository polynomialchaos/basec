/*******************************************************************************
 * @file global.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <stdlib.h>
#include "basec/mpi_module.h"
#include "basec/parameter_module.h"
#include "global_private.h"

/*******************************************************************************
 * @brief Check arguments
 * @param argc
 * @param argv
 ******************************************************************************/
void check_arguments(int argc, string_t *argv)
{
    switch (argc)
    {
    case 2:
        CHECK_EXPRESSION(file_exists(argv[1]));
        read_user_inputs(argv[1]);
        break;
    case 3:
        if (is_equal(argv[1], "-g") || is_equal(argv[1], "--generate"))
        {
            flush_user_defaults(argv[2]);
            check_abort(1);
        }
        else if (is_equal(argv[1], "-s") || is_equal(argv[1], "--show"))
        {
            CHECK_EXPRESSION(file_exists(argv[2]));
            read_user_inputs(argv[2]);
            print_user_inputs();
            check_abort(1);
        }
        else
        {
            LOG_ERROR("Unsupported parameter (%s)", argv[1]);
        }
        break;
    default:
        LOG_ERROR("Unsupported number of parameters (%d)", argc);
        break;
    }
}

/*******************************************************************************
 * @brief Global finalize
 ******************************************************************************/
void global_finalize()
{
    RESET_ERROR_STATE_HANDLER();

    call_finalize_list();

    free_parameters();

    PRINTF("\n");
    printf_r_sep(GBMS);

    string_t time_string = get_clock_time_string(get_clock_time(0.0));
    PRINTF("Finished. Total runtime of %s.\n", time_string);
    DEALLOCATE(time_string);

    printf_r_sep(GBMS);

    mpi_finalize();
}

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
                       bool_t only_rank, bool_t file_out, bool_t use_arguments)
{
    set_error_state_handler(global_finalize);

    mpi_initialize(argc, argv, only_rank, file_out);

    printf_r_sep(GBMS);

    string_t time_string = GET_DATE_TIME_STRING_NOW();
    PRINTF("%s (%s)\n", argv[0], time_string);
    DEALLOCATE(time_string);

    if (is_parallel())
    {
        int n_procs = get_number_of_procs();
        int i_rank = get_rank_number();
        PRINTF("Parallel run: Running on %d processor(s). Rank is %d.\n",
               n_procs, i_rank);
    }

    printf_r_sep(GBMS);

    if (!use_mpi)
        CHECK_EXPRESSION(!is_parallel());

    if (use_arguments)
        check_arguments(argc, argv);

    call_initialize_list();
}