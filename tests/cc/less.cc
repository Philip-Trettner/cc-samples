#include <doctest.hh>

#include <cc/less>

namespace
{
struct foo
{
};
[[maybe_unused]] bool operator<(foo const&, foo const&) { return true; }
} // namespace

TEST_CASE("less")
{
    SUBCASE("int")
    {
        cc::less<int> less;
        CHECK(less(1, 2));
        CHECK(!less(-1, -2));
    }

    SUBCASE("int*")
    {
        int a, b;
        cc::less<int*> less;
        CHECK_UNARY(less(&a, &b) || less(&b, &a));
    }

    SUBCASE("foo")
    {
        foo a, b;
        cc::less<foo> less;
        CHECK(less(a, b));
    }
}
