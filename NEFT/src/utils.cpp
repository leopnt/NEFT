#include "NEFT/utils.hpp"

float Utils::random()
{
    return randrange(0.f, 1.f);
}

float Utils::random(const float& max)
{
    return randrange(0.f, max);
}

float Utils::randrange(const float& min, const float& max)
{
    float r = float(std::rand()) / RAND_MAX;
    return min + r * (max - min);
}

void Utils::printArray(const std::vector<float>& array)
{
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "[";
    for(const float& elt: array)
    {
        std::cout << std::setw(5);
        std::cout << elt << ", ";
    }
    std::cout << "\b\b]" << std::endl;
}

std::vector<float> Utils::withBias(std::vector<float> array)
{
    // [4.5, -1.2] --> [4.5, -1.2, 1.0]
    array.push_back(1.f);
    return array;
}

std::vector<float> Utils::slice(
    const std::vector<float>& array, const int& start, const int& end)
{
    // returns the subarray from start to end

    auto first = array.begin() + start;
    auto last = array.begin() + end;
    std::vector<float> subArr(first, last);

    return subArr;
}