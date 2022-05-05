#include "tools.h"

int print_result(bool condition, int &test_number)
{
    if (condition)
    {
        printf("    TEST %d ---> %s \n", test_number++, "SUCCESS");
        return 0;
    }

    printf("    TEST %d ---> %s                 !!!\n", test_number++, "FAILURE");
    return 1;
}

