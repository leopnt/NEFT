#ifndef NN_HPP
#define NN_HPP

#include <cmath>
#include "layer.hpp"

class NN
{
private:
    int m_inputSize;
    int m_outputSize;

    std::vector<Layer> m_layers;
    
public:
    NN(const int& inputSize, const int& outputSize);
    ~NN();

    void addLayer(const int& inputSize);
    void randomize(const float& min, const float& max);

    std::vector<float> output(const std::vector<float>& input) const;

    std::vector<float> getWeights() const;
    void setWeights(const std::vector<float>& weights);

    int size() const;

    static void activate(std::vector<float>& arr);

    friend std::ostream& operator<<(std::ostream& out, const NN& self);
};



#endif
