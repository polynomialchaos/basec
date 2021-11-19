/*******************************************************************************
 * @file main.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "basec/global_module.h"

/*******************************************************************************
 * @brief User intialize routine
 ******************************************************************************/
void init_user()
{
    printf_r("Hello Init!\n");
};

/*******************************************************************************
 * @brief User finalize routine
 ******************************************************************************/
void free_user()
{
    printf_r("Hello Free!\n");
};

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main(int argc, string_t *argv)
{
    register_initialize_routine(init_user);
    register_finalize_routine(free_user);

    global_initialize(argc, argv, BTRU, BFLS, BFLS, BFLS);

    check_abort(1);
    return 0;
}