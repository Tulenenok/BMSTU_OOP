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

    printf("Count tests %d, count errors: %d\n\n", test_number - 1, rc);

    return test_number;
}

static void minus_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 1 Оператор - (унарный)
        Vector<int> v = {1, -2, 3, 4, 5};
        Vector<int> neg_v(-v);
        Vector<int> perf = {-1, 2, -3, -4, -5};
        rc += print_result(neg_v == perf, test_number);
    }

    {
        // 2 Оператор - (два вектора одного типа)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> v2 = {1, -2, 3, 4, 5};
        Vector<int> res(v1 - v2);
        Vector<int> perf(5, 0);
        rc += print_result(res == perf, test_number);
    }

    {
        // 3 Оператор - (вектор и число одного типа)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> res(v1 - 6);
        Vector<int> perf = {-5, -8, -3, -2, -1};
        rc += print_result(res == perf, test_number);
    }

    {
        // 4 Оператор - (два вектора разных типов)
        Vector<int> v1 = {8, 10};
        Vector<double> v2 = {7.3, 9.8};
        Vector<double> res(v1 - v2);
        Vector<double> perf = {0.7, 0.2};
        rc += print_result(res == perf, test_number);
    }

    {
        // 5 Оператор - (вектор и число разных типов)
        Vector<int> v1 = {8, 10};
        Vector<double> res(v1 - 7.9);
        Vector<double> perf = {0.1, 2.1};
        rc += print_result(res == perf, test_number);
    }

    {
        // 6 Оператор - (вектор и число, длина вектора 0)
        Vector<int> v1;
        Vector<double> res(v1 - 7.9);
        Vector<double> perf;
        rc += print_result(res == perf, test_number);
    }

    {
        // 7 Оператор - (вектор и вектор, длина вектора 0)
        Vector<int> v1;
        Vector<char> v2;
        Vector<int> res(v1 - v2);
        Vector<int> perf;
        rc += print_result(res == perf, test_number);
    }
}

static void plus_overload_vector_tests(int &rc, int &test_number)
{
    {
        // 8 Оператор + (унарный)
        Vector<int> v = {1, -2, 3, 4, 5};
        Vector<int> res(+v);
        Vector<int> perf = {1, -2, 3, 4, 5};
        rc += print_result(res == perf, test_number);
    }

    {
        // 9 Оператор + (два вектора одного типа)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> v2 = {-1, 2, -3, -4, -5};
        Vector<int> res(v1 + v2);
        Vector<int> perf(5, 0);
        rc += print_result(res == perf, test_number);
    }

    {
        // 10 Оператор + (вектор и число одного типа)
        Vector<int> v1 = {1, -2, 3, 4, 5};
        Vector<int> res(v1 + 6);
        Vector<int> perf = {7, 4, 9, 10, 11};
        rc += print_result(res == perf, test_number);
    }

    {
        // 11 Оператор + (два вектора разных типов)
        Vector<int> v1 = {8, 10};
        Vector<double> v2 = {0.3, 1.8};
        Vector<double> res(v1 + v2);
        Vector<double> perf = {8.3, 11.8};
        rc += print_result(res == perf, test_number);
    }

    {
        // 12 Оператор + (вектор и число разных типов)
        Vector<int> v1 = {8, 10};
        Vector<double> res(v1 + 7.9);
        Vector<double> perf = {15.9, 17.9};
        rc += print_result(res == perf, test_number);
    }

    {
        // 13 Оператор + (вектор и число, длина вектора 0)
        Vector<int> v1;
        Vector<double> res(v1 + 7.9);
        Vector<double> perf;
        rc += print_result(res == perf, test_number);
    }

    {
        // 14 Оператор + (вектор и вектор, длина вектора 0)
        Vector<int> v1;
        Vector<char> v2;
        Vector<int> res(v1 + v2);
        Vector<int> perf;
        rc += print_result(res == perf, test_number);
    }
}

int overload_vector_tests()
{
    int rc = 0;
    int test_number = 1;

    printf("Overload vector tests:\n");
    minus_overload_vector_tests(rc, test_number);
    plus_overload_vector_tests(rc, test_number);

    printf("Count tests %d, count errors: %d\n\n", test_number - 1, rc);

    return test_number;
}
