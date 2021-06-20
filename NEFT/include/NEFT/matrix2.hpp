#ifndef MATRIX2_HPP
#define MATRIX2_HPP

#include <iostream>
#include <iomanip> // for std::cout formatting
#include <vector>
#include "utils.hpp"

class Matrix2
{
private:
    int index(const int& i, const int& j) const;

protected:
    int m_rows;
    int m_cols;
    std::vector<float> m_array;

public:
    Matrix2(const int& rows, const int& cols);
    ~Matrix2();

    void randomize(const float& min, const float& max);
    
    void set(const int& i, const int& j, const float& value);
    float get(const int& i, const int& j) const;

    int size() const;
    std::vector<float> toArray() const;

    static std::vector<float> mult(
        const std::vector<float>& A, const Matrix2& B);
    
    friend std::ostream& operator<<(std::ostream& out, const Matrix2& self);
};


#endif
