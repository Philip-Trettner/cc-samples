#include <doctest.hh>

#include <cc/detail/traits/is_assignable_from.hh>
#include <cc/detail/traits/is_constructible_from.hh>
#include <cc/move>
#include <cc/unique_ptr>

// allowed:
static_assert(cc::is_default_constructible<cc::unique_ptr<int>>);
static_assert(cc::is_constructible_from<cc::unique_ptr<int>, cc::unique_ptr<int>&&>);
static_assert(cc::is_assignable_from<cc::unique_ptr<int>, cc::unique_ptr<int>&&>);
static_assert(cc::is_constructible_from<cc::unique_ptr<int>, cc::unique_ptr<int>>); // is an rvalue!
static_assert(cc::is_assignable_from<cc::unique_ptr<int>, cc::unique_ptr<int>>);

// non-copy
static_assert(!cc::is_constructible_from<cc::unique_ptr<int>, cc::unique_ptr<int> const&>);
static_assert(!cc::is_assignable_from<cc::unique_ptr<int>, cc::unique_ptr<int> const&>);
static_assert(!cc::is_constructible_from<cc::unique_ptr<int>, cc::unique_ptr<int>&>); // no accidental moves!
static_assert(!cc::is_assignable_from<cc::unique_ptr<int>, cc::unique_ptr<int>&>);

// not from ptr
static_assert(!cc::is_constructible_from<cc::unique_ptr<int>, int*>);
static_assert(!cc::is_assignable_from<cc::unique_ptr<int>, int*>);

TEST_CASE("unique_ptr")
{
    cc::unique_ptr<int> p;

    CHECK(p.get() == nullptr);
    CHECK(p == nullptr);
    CHECK(nullptr == p);

    // moves
    cc::unique_ptr<int> p2;
    p2 = move(p);
    auto p3 = move(p);
}
