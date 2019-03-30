#include <doctest.hh>

#include <cc/unique_ptr>

TEST_CASE("empty unique_ptr")
{
    cc::unique_ptr<int> p;

    CHECK(p.get() == nullptr);
}
