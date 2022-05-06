#include "tools.h"

int print_result(bool condition, int &test_number)
{
    if (condition)
    {
        printf("    TEST %2.d ---> %s \n", test_number++, "SUCCESS");
        return 0;
    }

    printf("    TEST %2.d ---> %s                 !!!\n", test_number++, "FAILURE");
    return 1;
}

