#pragma once

#include "range/v3/view/all.hpp"

#include <algorithm>
#include <ostream>
#include <vector>

using vec = std::vector<int>;
using vec2d = std::vector<vec>;

namespace std
{

inline
std::ostream& operator<<(std::ostream& s, const vec& v)
{
    s << ( v | ranges::view::all );
    return s;
}

inline
std::ostream& operator<<(std::ostream& s, const vec2d& v)
{
    s << ( v | ranges::view::all );
    return s;
}

template <typename Range>
bool operator==( const vec& v, const Range& r )
{
    return std::equal( v.begin(), v.end(), r.begin() );
}

template<typename Range>
bool operator==( const vec2d& v, const Range& r )
{
    return std::equal( v.begin(), v.end(), r.begin());
}

}
