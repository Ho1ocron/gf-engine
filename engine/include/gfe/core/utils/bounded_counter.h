#pragma once

#include <limits>

template <class T>
struct BoundedCounter
{
    T value;
    constexpr static T max = std::numeric_limits<T>().max();
    constexpr static T min = std::numeric_limits<T>().min();

    constexpr BoundedCounter(const T& value) : value(value) {}

    BoundedCounter& operator++()
    {
        if(value != max) value++;
        return *this;
    }
    BoundedCounter& operator--()
    {
        if(value != min) value--;
        return *this;
    }
    BoundedCounter operator++(int)
    {
        if(value != max)
        {
            BoundedCounter old{*this};
            operator++();
            return old;
        }
        else
            return *this;
    }
    BoundedCounter operator--(int)
    {
        if(value != min)
        {
            BoundedCounter old{*this};
            operator--();
            return old;
        }
        else
            return *this;
    }
    bool operator==(const T& other) { return value == other; }
    bool operator!=(const T& other) { return value != other; }
};
