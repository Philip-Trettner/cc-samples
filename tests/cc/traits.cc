#include <doctest.hh>

#include <cc/detail/traits/declval.hh>
#include <cc/detail/traits/has_operator.hh>
#include <cc/detail/traits/is_assignable_from.hh>
#include <cc/detail/traits/is_constructible_from.hh>
#include <cc/detail/traits/is_same.hh>
#include <cc/detail/traits/remove_reference.hh>
#include <cc/move>

// for comparing with std
#include <type_traits>
#include <utility>

namespace
{
template <class A, class B>
[[maybe_unused]] static auto test_ctor(A&&, B&& b) -> decltype(A(b), cc::true_type());
[[maybe_unused]] static inline cc::false_type test_ctor(...);

struct foo
{
};

struct foo_d : foo
{
};

struct bar_mut
{
    bool operator<(bar_mut const& rhs);
};

struct bar_mut2
{
    bool operator<(bar_mut& rhs) const;
};

struct bar
{
    bool operator<(bar const& rhs) const;
};

struct baz
{
};
[[maybe_unused]] bool operator<(baz a, baz const& b);

struct intwrapper
{
    intwrapper(int);
};
struct eintwrapper
{
    explicit eintwrapper(int);
};
} // namespace

TEST_CASE("is_same")
{
    static_assert(cc::is_same<int, int>);
    static_assert(!cc::is_same<int, int&>);
    static_assert(!cc::is_same<int, int&&>);
    static_assert(!cc::is_same<int, int const>);
    static_assert(!cc::is_same<int, int const&>);
    static_assert(!cc::is_same<int, int const&&>);
    static_assert(!cc::is_same<bool, int>);
    static_assert(!cc::is_same<foo, int>);
    static_assert(cc::is_same<foo, foo>);
    static_assert(!cc::is_same<foo, foo_d>);
}

TEST_CASE("has_operator_less")
{
    static_assert(cc::has_operator_less<int>);
    static_assert(cc::has_operator_less<int*>);
    static_assert(cc::has_operator_less<int&>);
    static_assert(cc::has_operator_less<int&&>);
    static_assert(cc::has_operator_less<int const&>);
    static_assert(cc::has_operator_less<bool>);
    static_assert(cc::has_operator_less<double>);
    static_assert(!cc::has_operator_less<foo>);
    static_assert(!cc::has_operator_less<bar_mut>);  // must be const
    static_assert(!cc::has_operator_less<bar_mut2>); // must be const
    static_assert(cc::has_operator_less<bar>);
    static_assert(cc::has_operator_less<baz>);
}

TEST_CASE("remove_reference")
{
    static_assert(cc::is_same<cc::remove_reference<int>, int>);
    static_assert(cc::is_same<cc::remove_reference<int&>, int>);
    static_assert(cc::is_same<cc::remove_reference<int&&>, int>);
    static_assert(cc::is_same<cc::remove_reference<int const>, int const>);
    static_assert(cc::is_same<cc::remove_reference<int const&>, int const>);
    static_assert(cc::is_same<cc::remove_reference<int const&&>, int const>);
    static_assert(cc::is_same<cc::remove_reference<int*>, int*>);
    static_assert(cc::is_same<cc::remove_reference<int*&>, int*>);
}

TEST_CASE("declval")
{
    static_assert(cc::is_same<decltype(cc::declval<int>()), int&&>); // because it's the return value of a function!
    static_assert(cc::is_same<decltype(cc::declval<int&>()), int&>);
    static_assert(cc::is_same<decltype(cc::declval<int&&>()), int&&>);
    static_assert(cc::is_same<decltype(cc::declval<int const>()), int const&&>); // because it's the return value of a function!
    static_assert(cc::is_same<decltype(cc::declval<int const&>()), int const&>);
    static_assert(cc::is_same<decltype(cc::declval<int const&&>()), int const&&>);
    static_assert(cc::is_same<decltype(cc::declval<int*>()), int*&&>); // because it's the return value of a function!

    // compare with std
    static_assert(cc::is_same<decltype(std::declval<int>()), int&&>); // because it's the return value of a function!
    static_assert(cc::is_same<decltype(std::declval<int&>()), int&>);
    static_assert(cc::is_same<decltype(std::declval<int&&>()), int&&>);
    static_assert(cc::is_same<decltype(std::declval<int const>()), int const&&>); // because it's the return value of a function!
    static_assert(cc::is_same<decltype(std::declval<int const&>()), int const&>);
    static_assert(cc::is_same<decltype(std::declval<int const&&>()), int const&&>);
    static_assert(cc::is_same<decltype(std::declval<int*>()), int*&&>); // because it's the return value of a function!
}

TEST_CASE("declvar")
{
    static_assert(cc::is_same<decltype(cc::declvar<int>), int>); // because it's the return value of a function!
    static_assert(cc::is_same<decltype(cc::declvar<int&>), int&>);
    static_assert(cc::is_same<decltype(cc::declvar<int&&>), int&&>);
    static_assert(cc::is_same<decltype(cc::declvar<int const>), int const>); // because it's the return value of a function!
    static_assert(cc::is_same<decltype(cc::declvar<int const&>), int const&>);
    static_assert(cc::is_same<decltype(cc::declvar<int const&&>), int const&&>);
    static_assert(cc::is_same<decltype(cc::declvar<int*>), int*>); // because it's the return value of a function!
}

TEST_CASE("move")
{
    // note: declval is an rvalue
    static_assert(cc::is_same<decltype(cc::move(cc::declval<int>())), int&&>);
    static_assert(cc::is_same<decltype(cc::move(cc::declval<int&>())), int&&>);
    static_assert(cc::is_same<decltype(cc::move(cc::declval<int&&>())), int&&>);
    static_assert(cc::is_same<decltype(cc::move(cc::declval<int const>())), int const&&>);
    static_assert(cc::is_same<decltype(cc::move(cc::declval<int const&>())), int const&&>);
    static_assert(cc::is_same<decltype(cc::move(cc::declval<int const&&>())), int const&&>);

    // compare with std
    static_assert(cc::is_same<decltype(std::move(std::declval<int>())), int&&>);
    static_assert(cc::is_same<decltype(std::move(std::declval<int&>())), int&&>);
    static_assert(cc::is_same<decltype(std::move(std::declval<int&&>())), int&&>);
    static_assert(cc::is_same<decltype(std::move(std::declval<int const>())), int const&&>);
    static_assert(cc::is_same<decltype(std::move(std::declval<int const&>())), int const&&>);
    static_assert(cc::is_same<decltype(std::move(std::declval<int const&&>())), int const&&>);

    // note: declvar is an lvalue
    static_assert(cc::is_same<decltype(cc::move(cc::declvar<int>)), int&&>);
    static_assert(cc::is_same<decltype(cc::move(cc::declvar<int&>)), int&&>);
    static_assert(cc::is_same<decltype(cc::move(cc::declvar<int&&>)), int&&>);
    static_assert(cc::is_same<decltype(cc::move(cc::declvar<int const>)), int const&&>);
    static_assert(cc::is_same<decltype(cc::move(cc::declvar<int const&>)), int const&&>);
    static_assert(cc::is_same<decltype(cc::move(cc::declvar<int const&&>)), int const&&>);

    // compare with std
    static_assert(cc::is_same<decltype(std::move(cc::declvar<int>)), int&&>);
    static_assert(cc::is_same<decltype(std::move(cc::declvar<int&>)), int&&>);
    static_assert(cc::is_same<decltype(std::move(cc::declvar<int&&>)), int&&>);
    static_assert(cc::is_same<decltype(std::move(cc::declvar<int const>)), int const&&>);
    static_assert(cc::is_same<decltype(std::move(cc::declvar<int const&>)), int const&&>);
    static_assert(cc::is_same<decltype(std::move(cc::declvar<int const&&>)), int const&&>);
}

TEST_CASE("forward")
{
    // TODO: should something here not be an rvalue reference?

    // note: declval is an rvalue
    static_assert(cc::is_same<decltype(cc::forward<int>(cc::declval<int>())), int&&>);
    static_assert(cc::is_same<decltype(cc::forward<int>(cc::declval<int&>())), int&&>);
    static_assert(cc::is_same<decltype(cc::forward<int>(cc::declval<int&&>())), int&&>);
    static_assert(cc::is_same<decltype(cc::forward<int const>(cc::declval<int const>())), int const&&>);
    static_assert(cc::is_same<decltype(cc::forward<int const>(cc::declval<int const&>())), int const&&>);
    static_assert(cc::is_same<decltype(cc::forward<int const>(cc::declval<int const&&>())), int const&&>);

    // compare with std
    static_assert(cc::is_same<decltype(std::forward<int>(std::declval<int>())), int&&>);
    static_assert(cc::is_same<decltype(std::forward<int>(std::declval<int&>())), int&&>);
    static_assert(cc::is_same<decltype(std::forward<int>(std::declval<int&&>())), int&&>);
    static_assert(cc::is_same<decltype(std::forward<int const>(std::declval<int const>())), int const&&>);
    static_assert(cc::is_same<decltype(std::forward<int const>(std::declval<int const&>())), int const&&>);
    static_assert(cc::is_same<decltype(std::forward<int const>(std::declval<int const&&>())), int const&&>);

    // note: declvar is an lvalue
    static_assert(cc::is_same<decltype(cc::forward<int>(cc::declvar<int>)), int&&>);
    static_assert(cc::is_same<decltype(cc::forward<int>(cc::declvar<int&>)), int&&>);
    static_assert(cc::is_same<decltype(cc::forward<int>(cc::declvar<int&&>)), int&&>);
    static_assert(cc::is_same<decltype(cc::forward<int const>(cc::declvar<int const>)), int const&&>);
    static_assert(cc::is_same<decltype(cc::forward<int const>(cc::declvar<int const&>)), int const&&>);
    static_assert(cc::is_same<decltype(cc::forward<int const>(cc::declvar<int const&&>)), int const&&>);

    // compare with std
    static_assert(cc::is_same<decltype(std::forward<int>(cc::declvar<int>)), int&&>);
    static_assert(cc::is_same<decltype(std::forward<int>(cc::declvar<int&>)), int&&>);
    static_assert(cc::is_same<decltype(std::forward<int>(cc::declvar<int&&>)), int&&>);
    static_assert(cc::is_same<decltype(std::forward<int const>(cc::declvar<int const>)), int const&&>);
    static_assert(cc::is_same<decltype(std::forward<int const>(cc::declvar<int const&>)), int const&&>);
    static_assert(cc::is_same<decltype(std::forward<int const>(cc::declvar<int const&&>)), int const&&>);
}

TEST_CASE("is_constructible_from")
{
    static_assert(cc::is_constructible_from<int, int>);
    static_assert(cc::is_constructible_from<int, bool>);
    static_assert(cc::is_constructible_from<int, float>);
    static_assert(cc::is_constructible_from<float, bool>);
    static_assert(!cc::is_constructible_from<foo, int*>);
    static_assert(cc::is_constructible_from<foo, foo>);
    static_assert(cc::is_constructible_from<foo, foo const&>);
    static_assert(cc::is_constructible_from<foo, foo&&>);
    static_assert(cc::is_constructible_from<intwrapper, int>);
    static_assert(cc::is_constructible_from<eintwrapper, int>);

    static_assert(cc::is_default_constructible<int>);
    static_assert(cc::is_default_constructible<int*>);
    static_assert(cc::is_default_constructible<foo>);
    static_assert(!cc::is_default_constructible<intwrapper>);
}

TEST_CASE("is_assignable_from")
{
    static_assert(cc::is_assignable_from<int, int>);
    static_assert(cc::is_assignable_from<int, bool>);
    static_assert(cc::is_assignable_from<int, float>);
    static_assert(cc::is_assignable_from<float, bool>);
    static_assert(!cc::is_assignable_from<foo, int*>);
    static_assert(cc::is_assignable_from<foo, foo>);
    static_assert(cc::is_assignable_from<foo, foo const&>);
    static_assert(cc::is_assignable_from<foo, foo&&>);
    static_assert(cc::is_assignable_from<intwrapper, int>);
    static_assert(!cc::is_assignable_from<eintwrapper, int>);
}
