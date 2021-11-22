/*******************************************************************************
 * @file global.c
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
    PRINTF("Hello Init!\n");
};

/*******************************************************************************
 * @brief User finalize routine
 ******************************************************************************/
void free_user()
{
    PRINTF("Hello Free!\n");
};

/*******************************************************************************
 * @brief Main test function
 * @param argc
 * @param argv
 * @return int
 ******************************************************************************/
int main(int argc, string_t *argv)
{
    REGISTER_INITIALIZE_ROUTINE(init_user);
    REGISTER_FINALIZE_ROUTINE(free_user);

    global_initialize(argc, argv, BTRU, BFLS, BFLS, BFLS);

    check_abort(1);
    return 0;
}