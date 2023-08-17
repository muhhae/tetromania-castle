#pragma once

#include <functional>
#include <vector>

template <typename T>
void deleteAll(std::vector<T> & vec, std::function<bool(T&)> condition)
{
    auto it = vec.begin();
    while (it != vec.end())
    {
        if (condition(*it))
        {
            it = vec.erase(it);
        } else it++;
    }
}