#include <zephyr/ztest.h>

ZTEST(basic_tests, test_simple)
{
    zassert_equal(1, 1, "Basic test should pass");
}

ZTEST_SUITE(basic_tests, NULL, NULL, NULL, NULL, NULL);