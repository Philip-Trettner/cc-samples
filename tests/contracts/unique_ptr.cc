#include <test.hh>

#include <cc/unique_ptr>

TEST_CASE("unique_ptr contracts")
{
    ENABLE_ASSERTION_TESTS();

    cc::unique_ptr<int> p;

    // doesn't work because *p is noexcept!
    // CHECK_ASSERTS(*p);
}
