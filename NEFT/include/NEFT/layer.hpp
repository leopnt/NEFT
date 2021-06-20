#ifndef LAYER_HPP
#define LAYER_HPP


#include "matrix2.hpp"

class Layer : public Matrix2
{
public:
    Layer(const int& inSize, const int& outSize);
    ~Layer();

    std::vector<float> getWeights() const;
    void setWeights(const std::vector<float>& weights);

    int getInputSize() const;
    int getOutputSize() const;
};


#endif
