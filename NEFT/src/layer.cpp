#include "NEFT/layer.hpp"

Layer::Layer(const int& inSize, const int& outSize): Matrix2(inSize, outSize)
{
}

Layer::~Layer()
{
}

std::vector<float> Layer::getWeights() const
{
    return toArray();
}

void Layer::setWeights(const std::vector<float>& weights)
{
    if(size() != int(weights.size()))
    {
        std::cout << "Layer::>Warning: set weights with different sizes";
        std::cout << std::endl;
        return;
    }

    for(int i = 0; i < size(); i++)
    {
        m_array[i] = weights[i];
    }
}

int Layer::getInputSize() const
{
    return m_rows;
}

int Layer::getOutputSize() const
{
    return m_cols;
}