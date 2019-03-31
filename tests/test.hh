#include <doctest.hh>

#include <cc/assert>

namespace cctests
{
struct exception
{
};

struct throwing_assertion_scope
{
    static void handler(cc::detail::assertion_info const&) { throw ::cctests::exception(); }

    throwing_assertion_scope() { cc::set_assertion_handler(handler); }
    ~throwing_assertion_scope() { cc::set_assertion_handler(nullptr); }
};
} // namespace cctests

#define ENABLE_ASSERTION_TESTS() auto _assertion_scope = ::cctests::throwing_assertion_scope()

#define CHECK_ASSERTS(expr) CHECK_THROWS_AS(expr, ::cctests::exception)
#define CHECK_NO_ASSERTS(expr) CHECK_NOTHROW(expr)
