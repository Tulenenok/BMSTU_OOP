#include "vectorTests.h"
#include "../inc/Vector.h"

int constructors_vector_tests()
{
    int rc = 0;
    int test_number = 1;

    printf("Constructors vector tests:\n");
    {
        // Простая инициализация
        Vector<int> v;
        rc += print_result(v.isEmpty() and v.getSize() == 0, test_number);
    }

    {
        // Инициализация с размером
        Vector<int> v(5);
        rc += print_result(not v.isEmpty() and v.getSize() == 5, test_number);
    }

    {
        // Инициализация с размером и заполняющим значением
        Vector<int> v(5, 3);
        rc += print_result(not v.isEmpty() and v.getSize() == 5 and v[0] == 3, test_number);
    }

    {
        // Инициализация с размером и заполняющим массивом
        double arr[] = {1, 2, 3};
        Vector<double> v(5, arr);
        rc += print_result(not v.isEmpty() and
                           v.getSize() == 5 and v[0] == 1 and v[1] == 2 and v[2] == 3, test_number);
    }

    {
        // Инициализация с размером и заполняющим массивом
        typedef struct test_struct
        {
            int a;
            char b;
        } test_struct_t;

        test_struct_t arr[] = {{1, 2}, {5, 6}};
        Vector<test_struct> v(5, arr);
        rc += print_result(not v.isEmpty() and v.getSize() == 5 and
                           v[0].a == 1 and v[0].b == 2 and v[1].a == 5 and v[1].b == 6, test_number);
    }
    {
        // Инициализация встроенным листом
        Vector<char> v({'a', 'b', 'c', 'd'});
        rc += print_result(not v.isEmpty() and v.getSize() == 4 and
                           v[0] == 'a' and v[1] == 'b' and v[2] == 'c' and v[3] == 'd', test_number);
    }

    {
        // Копирование
        Vector<char> v({'a', 'b'});
        Vector<char> v_copy(v);
        rc += print_result(not v.isEmpty() and v.getSize() == 2
                           and v_copy[0] == 'a' and v_copy[1] == 'b', test_number);
    }

    printf("Count tests %d, count errors: %d\n", test_number - 1, rc);

    return test_number;
}
