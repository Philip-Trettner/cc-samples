#include <doctest.hh>

#include <cc/assert>

namespace
{
struct assertion
{
};

void foo(int i) { ASSERT(i >= 0); }
void bounds(int i, int a, int b) { CC_BOUND_CHECK(i, a, b); }

void throwing_handler(cc::detail::assertion_info const&) { throw assertion(); }
} // namespace

TEST_CASE("assertions")
{
    cc::set_assertion_handler(throwing_handler);

    CHECK_NOTHROW(foo(0));
    CHECK_NOTHROW(foo(1));
    CHECK_NOTHROW(foo(100));
    CHECK_THROWS_AS(foo(-1), assertion);
    CHECK_THROWS_AS(foo(-100), assertion);

    CHECK_NOTHROW(bounds(0, 0, 10));
    CHECK_NOTHROW(bounds(5, 0, 10));
    CHECK_NOTHROW(bounds(9, 0, 10));
    CHECK_THROWS_AS(bounds(-1, 0, 10), assertion);
    CHECK_THROWS_AS(bounds(10, 0, 10), assertion);
    CHECK_THROWS_AS(bounds(-5, 0, 10), assertion);
    CHECK_THROWS_AS(bounds(15, 0, 10), assertion);

    CHECK_NOTHROW(bounds(5, 5, 7));
    CHECK_NOTHROW(bounds(6, 5, 7));
    CHECK_THROWS_AS(bounds(4, 5, 7), assertion);
    CHECK_THROWS_AS(bounds(7, 5, 7), assertion);

    cc::set_assertion_handler(nullptr);
}
