#include <doctest.hh>

#include <cc/optional>

TEST_CASE("optional")
{
    auto i = cc::optional<int>();
    CHECK(!i.has_value());
}
