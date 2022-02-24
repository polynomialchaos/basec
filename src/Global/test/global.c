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
    BM_PRINT("Hello Init!\n");
};

/*******************************************************************************
 * @brief User finalize routine
 ******************************************************************************/
void free_user()
{
    BM_PRINT("Hello Free!\n");
};

/*******************************************************************************
 * @brief Main function
 * @param argc
 * @param argv
 * @return int
 ******************************************************************************/
int main(int argc, string_t *argv)
{
    BM_REGISTER_INITIALIZE_ROUTINE(init_user);
    BM_REGISTER_FINALIZE_ROUTINE(free_user);

    global_initialize(argc, argv, BC_TRUE, BC_FALSE, BC_FALSE, BC_FALSE);

    check_abort(1);
    return 0;
}