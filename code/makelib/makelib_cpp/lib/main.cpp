#include <vector>

void abort(void)
{
    while (1);
}

void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
    //
    while (1);
}

void *malloc(size_t size)
{
    // ����Ѿ����� malloc, free �������������Ͳ�Ҫ����
    return nullptr;
}

void free(void *ptr)
{
    //
}

namespace std
{
    new_handler get_new_handler() _NOEXCEPT
    {
        return nullptr;
    }
}


int test_fun1(void)
{
    std::vector<int> a;
    a.push_back(1);
    a.push_back(2);

    return a[0];
}
