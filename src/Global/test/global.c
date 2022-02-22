/*******************************************************************************
 * @file global.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
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
 * @brief Main function
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