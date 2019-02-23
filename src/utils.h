#pragma once

#include "range/v3/range/concepts.hpp"

CPP_def
(
    template(typename T, typename U)
    concept BothRanges, ranges::InputRange<T> && ranges::InputRange<U>
);

struct are_equal_fn
{
    CPP_template(typename T, typename U)(requires not BothRanges<T, U>)
    bool operator()(T&& actual, U&& expected) const
    {
        return((T&&) actual == (U&&) expected);
    }

    CPP_template(typename Rng1, typename Rng2)(requires BothRanges<Rng1, Rng2>)
    bool operator()(Rng1&& actual, Rng2&& expected) const
    {
        auto begin0 = ranges::begin(actual);
        auto end0 = ranges::end(actual);
        auto begin1 = ranges::begin(expected);
        auto end1 = ranges::end(expected);
        for(; begin0 != end0 && begin1 != end1; ++begin0, ++begin1)
        {
            if(!(*this)(*begin0, *begin1))
            {
                return false;
            }
        }

        return begin0 == end0 && begin1 == end1;
    }

    CPP_template(typename Rng, typename Val)(requires ranges::InputRange<Rng>)
    bool operator()(Rng&& actual, std::initializer_list<Val>&& expected) const
    {
        return (*this)(actual, expected);
    }

    CPP_template(typename Rng, typename Val)(requires ranges::InputRange<Rng>)
    bool operator()(Rng&& actual, std::initializer_list<std::initializer_list<Val>>&& expected) const
    {
        return (*this)(actual, expected);
    }
};

RANGES_INLINE_VARIABLE(are_equal_fn, are_equal)
