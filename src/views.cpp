#include "boost/test/unit_test.hpp"

#include "range/v3/view.hpp"

#include "utils.h"

namespace
{

static const std::initializer_list<int> firstNats = { 4, 5, 6, 7, 8, 9, 10 };

template <typename T, typename K>
auto pair( T&& t, K&& k )
{
  return std::pair<T, K>( std::forward<T>( t ), std::forward<K>( k ) );
}

}  // namespace

BOOST_AUTO_TEST_SUITE( RangeV3ViewsTests )


BOOST_AUTO_TEST_CASE( AdjacentRemoveIf )
{
  const auto F = std::equal_to<int>{};

  const auto input = { 1, 1, 1, 2, 2, 3, 4, 4, 4, 1 };
  BOOST_CHECK( are_equal( input | ranges::view::adjacent_remove_if( F ), { 1, 2, 3, 4, 1 } ) );
}


BOOST_AUTO_TEST_CASE( All )
{
  BOOST_CHECK( are_equal( firstNats | ranges::view::all, { 4, 5, 6, 7, 8, 9, 10 } ) );
}


BOOST_AUTO_TEST_CASE( CartesianProduct )
{
  const auto a = { 1, 2, 3 };
  const auto b = { 4, 5, 6 };

  using CT = ranges::common_tuple<int, int>;
  BOOST_CHECK(
      are_equal( ranges::view::cartesian_product( a, b ),
                 { CT{ 1, 4 }, CT{ 1, 5 }, CT{ 1, 6 }, CT{ 2, 4 }, CT{ 2, 5 }, CT{ 2, 6 }, CT{ 3, 4 }, CT{ 3, 5 }, CT{ 3, 6 } } ) );
}


BOOST_AUTO_TEST_CASE( Chunk )
{
  const int N = 3;

  // split range by subranges of N elements
  BOOST_CHECK( are_equal( firstNats | ranges::view::chunk( N ), { { 4, 5, 6 }, { 7, 8, 9 }, { 10 } } ) );
}


// BOOST_AUTO_TEST_CASE( Common )


BOOST_AUTO_TEST_CASE( Concat )
{
  // join two ranges into one
  BOOST_CHECK( are_equal( ranges::view::concat( firstNats, firstNats ), { 4, 5, 6, 7, 8, 9, 10, 4, 5, 6, 7, 8, 9, 10 } ) );
}


// BOOST_AUTO_TEST_CASE( Const )


// BOOST_AUTO_TEST_CASE( Counted )


BOOST_AUTO_TEST_CASE( Cycle )
{
  BOOST_CHECK(
      are_equal( firstNats | ranges::view::cycle | ranges::view::take( 18 ), { 4, 5, 6, 7, 8, 9, 10, 4, 5, 6, 7, 8, 9, 10, 4, 5, 6, 7 } ) );
}


BOOST_AUTO_TEST_CASE( Delimit )
{
  const int N = 8;
  // take range elements until element with value N is met
  BOOST_CHECK( are_equal( firstNats | ranges::view::delimit( N ), { 4, 5, 6, 7 } ) );
}


BOOST_AUTO_TEST_CASE( Drop )
{
  const int N = 3;

  // drop first N elements
  BOOST_CHECK( are_equal( firstNats | ranges::view::drop( N ), { 7, 8, 9, 10 } ) );
}


BOOST_AUTO_TEST_CASE( Enumerate )
{
  BOOST_CHECK( are_equal( firstNats | ranges::view::enumerate,
                          { pair( 0, 4 ), pair( 1, 5 ), pair( 2, 6 ), pair( 3, 7 ), pair( 4, 8 ), pair( 5, 9 ), pair( 6, 10 ) } ) );
}


BOOST_AUTO_TEST_CASE( Iota )
{
  const int N = 1;
  const int M = 6;

  // make range of elements [N...M)
  BOOST_CHECK( are_equal( ranges::view::iota( N, M ), { 1, 2, 3, 4, 5 } ) );
  BOOST_CHECK( are_equal( ranges::view::ints( N, M ), { 1, 2, 3, 4, 5 } ) );

  // make range of elements [N...M]
  BOOST_CHECK( are_equal( ranges::view::closed_iota( N, M ), { 1, 2, 3, 4, 5, 6 } ) );
}


BOOST_AUTO_TEST_CASE( Join )
{
    const std::initializer_list<std::initializer_list<int>> v = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
    BOOST_CHECK( are_equal( v | ranges::view::join, { 1, 2, 3, 4, 5, 6 } ) );
    BOOST_CHECK( are_equal( v | ranges::view::join( 0 ), { 1, 2, 0, 3, 4, 0, 5, 6 } ) );
}


BOOST_AUTO_TEST_CASE( PartialSum )
{
  BOOST_CHECK( are_equal( firstNats | ranges::view::partial_sum, { 4, 9, 15, 22, 30, 39, 49 } ) );
}


BOOST_AUTO_TEST_CASE( Repeat )
{
  const int N = 9;

  // repeat value N infinite number of times and 5 elements are taken from the infinite range
  BOOST_CHECK( are_equal( ranges::view::repeat( N ) | ranges::view::take( 5 ), { 9, 9, 9, 9, 9 } ) );
}


BOOST_AUTO_TEST_CASE( RepeatN )
{
  const int N = 9;
  const int M = 5;

  // repeat value N M number of times
  BOOST_CHECK( are_equal( ranges::view::repeat_n( N, M ), { 9, 9, 9, 9, 9 } ) );
}


BOOST_AUTO_TEST_CASE( Replace )
{
  const int X = 6;
  const int Y = 99;

  // replace elements values from X to Y
  BOOST_CHECK( are_equal( firstNats | ranges::view::replace( X, Y ), { 4, 5, 99, 7, 8, 9, 10 } ) );
}


BOOST_AUTO_TEST_CASE( ReplaceIf )
{
    BOOST_CHECK( are_equal( firstNats | ranges::view::replace_if( []( const int X ){ return X % 2 == 0; }, 42 ), { 42, 5, 42, 7, 42, 9, 42 } ) );
}


BOOST_AUTO_TEST_CASE( Reverse )
{
  BOOST_CHECK( are_equal( firstNats | ranges::view::reverse, { 10, 9, 8, 7, 6, 5, 4 } ) );
}


BOOST_AUTO_TEST_CASE( Single )
{
  const int N = 42;

  // make a range containing a single element N
  BOOST_CHECK( are_equal( ranges::view::single( N ), { 42 } ) );
}


BOOST_AUTO_TEST_CASE( Slice )
{
  const int N = 1;
  const int M = 4;

  // take elements from N-th to M-th
  BOOST_CHECK( are_equal( firstNats | ranges::view::slice( N, M ), { 5, 6, 7 } ) );
}


BOOST_AUTO_TEST_CASE( Sliding )
{
  BOOST_CHECK( are_equal( firstNats | ranges::view::sliding( 3 ), { { 4, 5, 6 }, { 5, 6, 7 }, { 6, 7, 8 }, { 7, 8, 9 }, { 8, 9, 10 } } ) );
}


BOOST_AUTO_TEST_CASE( Stride )
{
  const int N = 3;

  // keep only every N-th element
  BOOST_CHECK( are_equal( firstNats | ranges::view::stride( N ), { 4, 7, 10 } ) );
}


BOOST_AUTO_TEST_CASE( Tail )
{
  // drop first element
  BOOST_CHECK( are_equal( firstNats | ranges::view::tail, { 5, 6, 7, 8, 9, 10 } ) );
}


BOOST_AUTO_TEST_CASE( Take )
{
  const int N = 5;

  // keep only first N elements
  BOOST_CHECK( are_equal( firstNats | ranges::view::take( N ), { 4, 5, 6, 7, 8 } ) );
}


BOOST_AUTO_TEST_CASE( Transform )
{
  const auto F = []( int n ) { return n + 3; };

  // apply F to every range element
  BOOST_CHECK( are_equal( firstNats | ranges::view::transform( F ), { 7, 8, 9, 10, 11, 12, 13 } ) );
}


BOOST_AUTO_TEST_CASE( Zip )
{
  const auto a = { 1, 2, 3 };
  const auto b = { 4, 5, 6 };
  BOOST_CHECK( are_equal( ranges::view::zip( a, b ), { pair( 1, 4 ), pair( 2, 5 ), pair( 3, 6 ) } ) );

  const auto c = { 4, 5 };
  BOOST_CHECK( are_equal( ranges::view::zip( a, c ), { pair( 1, 4 ), pair( 2, 5 ) } ) );
  BOOST_CHECK( are_equal( ranges::view::zip( c, a ), { pair( 4, 1 ), pair( 5, 2 ) } ) );
}


BOOST_AUTO_TEST_SUITE_END()
