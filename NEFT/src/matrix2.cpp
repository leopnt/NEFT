#include "NEFT/matrix2.hpp"

Matrix2::Matrix2(const int& rows, const int& cols): m_rows(rows), m_cols(cols)
{
    m_array = std::vector<float>(size());
}

Matrix2::~Matrix2()
{
}

int Matrix2::index(const int& i, const int& j) const
{
    // translates 2d array indexes into 1d array index

    //        j
    //  |  0  1  2  3 |
    // i|  4  5  6  7 | <--> [0, 1, 2, 3; 4, 5, 6, 7; 8, 9, 10, 11]
    //  |  8  9 10 11 |                      ^
    //                                 i * m_cols + j
    //
    // This allows for easy access to the matrix while keeping 1d array
    // for performances
    // ==> m_array[index(i, j)]

    return i * m_cols + j;
}

void Matrix2::randomize(const float& min, const float& max)
{
    for(float& elt: m_array)
    {
        elt = Utils::randrange(min, max);
    }
}

void Matrix2::set(const int& i, const int& j, const float& value)
{
    m_array[index(i, j)] = value;
}

float Matrix2::get(const int& i, const int& j) const
{
    return m_array[index(i, j)];
}

int Matrix2::size() const
{
    return m_rows * m_cols;
}

std::vector<float> Matrix2::toArray() const
{
    return m_array;
}

std::vector<float> Matrix2::mult(const std::vector<float>& A, const Matrix2& B)
{
    if((int) A.size() != B.m_rows)
    {
        std::cout << "Matrix2::>Warning: Incompatible multiplication ";
        std::cout << A.size() << "x" << B.size() << std::endl;
        return std::vector<float>();
    }

    std::vector<float> C = std::vector<float>(B.m_cols);
    for(int j = 0; j < B.m_cols; j++)
    {
        float sum = 0;
        for(int k = 0; k < B.m_rows; k++)
        {
            sum += A[k] * B.get(k, j);
        }
        C[j] = sum;
    }

    return C;
}

std::ostream& operator<<(std::ostream& out, const Matrix2& self)
{
    out << std::fixed << std::setprecision(2);

    out << "[" << self.m_rows << "x" << self.m_cols << "]";
    for(int i = 0; i < self.m_rows; i++)
    {
        out << std::endl << "| ";
        for(int j = 0; j < self.m_cols; j++)
        {
            out << std::setw(5);
            out << self.get(i, j) << " ";
        }
        out << "|";
    }

    return out;
}