#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <iomanip> // for std::cout formattin
#include <vector>

class Utils
{
public:
    static float random();
    static float random(const float& max);
    static float randrange(const float& min, const float& max);

    static void printArray(const std::vector<float>& array);

    static std::vector<float> withBias(const std::vector<float> array);

    static std::vector<float> slice(
        const std::vector<float>& array, const int& start, const int& end);
};


#endif