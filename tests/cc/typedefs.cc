#include <cc/typedefs>

static_assert(sizeof(cc::int8) == 1, "i8 is not 8bit");
static_assert(sizeof(cc::uint8) == 1, "u8 is not 8bit");

static_assert(sizeof(cc::int16) == 2, "i16 is not 16bit");
static_assert(sizeof(cc::uint16) == 2, "u16 is not 16bit");

static_assert(sizeof(cc::int32) == 4, "i32 is not 32bit");
static_assert(sizeof(cc::uint32) == 4, "u32 is not 32bit");
static_assert(sizeof(cc::float32) == 4, "f32 is not 32bit");

static_assert(sizeof(cc::int64) == 8, "i64 is not 64bit");
static_assert(sizeof(cc::uint64) == 8, "u64 is not 64bit");
static_assert(sizeof(cc::float64) == 8, "f64 is not 64bit");
