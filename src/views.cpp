#include "boost/test/unit_test.hpp"

#include "range/v3/view.hpp"

#include "utils.h"

namespace {

struct Fixture
{
    const vec firstNats = { 4, 5, 6, 7, 8, 9, 10 };
};

}

BOOST_FIXTURE_TEST_SUITE(RangeV3ViewsTests, Fixture)

BOOST_AUTO_TEST_CASE(All)
{
    BOOST_CHECK_EQUAL( (vec{ 4, 5, 6, 7, 8, 9, 10 }), firstNats | ranges::view::all );
}

BOOST_AUTO_TEST_CASE(Chunk)
{
    const int N = 3;

    // split range by subranges of N elements
    BOOST_CHECK_EQUAL( (vec2d{ { 4, 5, 6 }, { 7, 8, 9 }, { 10 } }),
                       firstNats | ranges::view::chunk( N ) );
}

BOOST_AUTO_TEST_CASE(Concat)
{
    // join two ranges into one
    BOOST_CHECK_EQUAL( (vec{ 4, 5, 6, 7, 8, 9, 10, 4, 5, 6, 7, 8, 9, 10 }),
                       ranges::view::concat( firstNats, firstNats ) );
}

BOOST_AUTO_TEST_CASE(Iota)
{
    const int N = 1;
    const int M = 6;

    // make range of elements [N, M)
    BOOST_CHECK_EQUAL( (vec{ 1, 2, 3, 4, 5 }), ranges::view::iota( N, M ) );
    BOOST_CHECK_EQUAL( (vec{ 1, 2, 3, 4, 5 }), ranges::view::ints( N, M ) );

    // make range of elements [N, M]
    BOOST_CHECK_EQUAL( (vec{ 1, 2, 3, 4, 5, 6 }), ranges::view::closed_iota( N, M ) );
}

BOOST_AUTO_TEST_CASE(PartialSum)
{
    BOOST_CHECK_EQUAL( (vec{ 4, 9, 15, 22, 30, 39, 49}), firstNats | ranges::view::partial_sum );
}

BOOST_AUTO_TEST_CASE(Repeat)
{
    const int N = 9;

    // repeat value N infinite number of times
    BOOST_CHECK_EQUAL( (vec{ 9, 9, 9, 9, 9 }), ranges::view::repeat( N ) | ranges::view::take( 5 ) );
}

BOOST_AUTO_TEST_CASE(Replace)
{
    const int X = 6;
    const int Y = 99;

    // replace elements values from X to Y
    BOOST_CHECK_EQUAL( (vec{ 4, 5, 99, 7, 8, 9, 10 }), firstNats | ranges::view::replace( X, Y ) );
}

BOOST_AUTO_TEST_CASE(Reverse)
{
    BOOST_CHECK_EQUAL( (vec{ 10, 9, 8, 7, 6, 5, 4 }), firstNats | ranges::view::reverse );
}

BOOST_AUTO_TEST_CASE(Slice)
{
    const int N = 1;
    const int M = 4;

    // take elements from N-th to M-th
    BOOST_CHECK_EQUAL( (vec{ 5, 6, 7, 8 }), firstNats | ranges::view::slice( N, M ) );
}

BOOST_AUTO_TEST_CASE(Sliding)
{
    BOOST_CHECK_EQUAL( (vec2d{ { 4, 5, 6 }, { 5, 6, 7 }, { 6, 7, 8 }, { 7, 8, 9 }, { 8, 9, 10 } }),
                       firstNats | ranges::view::sliding( 3 ) );
}

BOOST_AUTO_TEST_CASE(Stride)
{
    const int N = 3;

    // keep only every N-th element
    BOOST_CHECK_EQUAL( (vec{ 4, 7, 10 }), firstNats | ranges::view::stride( N ) );
}

BOOST_AUTO_TEST_CASE(Tail)
{
    // drop first element
    BOOST_CHECK_EQUAL( (vec{ 5, 6, 7, 8, 9, 10 }), firstNats | ranges::view::tail );
}

BOOST_AUTO_TEST_CASE(Take)
{
    const int N = 4;

    // keep only first N elements
    BOOST_CHECK_EQUAL( (vec{ 4, 5, 6, 7 }), firstNats | ranges::view::take( N ) );
}

BOOST_AUTO_TEST_CASE(Transform)
{
    BOOST_CHECK_EQUAL( (vec{ 7, 8, 9, 10, 11, 12, 13 }),
                       firstNats | ranges::view::transform( []( int n ) { return n + 3; } ) );
}

BOOST_AUTO_TEST_SUITE_END()
