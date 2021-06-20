#include "NEFT/nn.hpp"

NN::NN(const int& inputSize, const int& outputSize):
    m_inputSize(inputSize), m_outputSize(outputSize)
{
    m_layers = std::vector<Layer>();
    m_layers.push_back(Layer(m_inputSize + 1, m_outputSize)); // set first layer
                                                              // + 1 for bias
    randomize(-1, 1);
}

NN::~NN()
{
}

void NN::addLayer(const int& inputSize)
{
    // modify current last layer to match with the next last layer
    int lastLayerIndex = m_layers.size() -1;
    int lastInputSize = m_layers[lastLayerIndex].getInputSize();
    m_layers[lastLayerIndex] = Layer(lastInputSize, inputSize);

    // add last layer
    Layer newLayer(inputSize + 1, m_outputSize); // + 1 for the bias
    m_layers.push_back(newLayer);

    randomize(-1, 1);
}

void NN::randomize(const float& min, const float& max)
{
    for(Layer& layer: m_layers)
    {
        layer.randomize(min, max);
    }
}

std::vector<float> NN::output(const std::vector<float>& input) const
{
    // the array that will go through the NN
    std::vector<float> signal = input;

    for(const Layer& layer: m_layers)
    {
        // prepare next input with bias
        std::vector<float> biasedSignal = Utils::withBias(signal);

        // feed forward with the current layer
        signal = Matrix2::mult(biasedSignal, layer);
        // pass the output through the activation function
        NN::activate(signal);
    }
    
    return signal;
}

std::vector<float> NN::getWeights() const
{
    std::vector<float> weights = std::vector<float>();
    for(const Layer& layer: m_layers)
    {
        for(const float& weight: layer.getWeights())
        {
            weights.push_back(weight);
        }
    }

    return weights;
}

void NN::setWeights(const std::vector<float>& weights)
{
    if(size() != int(weights.size()))
    {
        std::cout << "NN::>Warning: set weights with different sizes";
        std::cout << std::endl;
        return;
    }

    int blockIndex = 0;
    for(Layer& layer: m_layers)
    {
        // extract layer weights from full NN weights
        std::vector<float> layerBlock = Utils::slice(
            weights, blockIndex, blockIndex + layer.size());

        // then set the layer with the extracted sub array corresponding
        // to this layer
        layer.setWeights(layerBlock);
        blockIndex += layer.size();
    }
}

int NN::size() const
{
    int size = 0;
    for(const Layer& layer: m_layers)
    {
        size += layer.size();
    }

    return size;
}

void NN::activate(std::vector<float>& arr)
{
    // keep values normalized and coherent

    for(float& x: arr)
    {
        x = tanh(x); // tanh returns values between [-1, 1]
    }
}

std::ostream& operator<<(std::ostream& out, const NN& self)
{
    out << "NN[in: " << self.m_inputSize << " +1 ";
    out << "==> out: " << self.m_outputSize;
    out << "] " << std::endl;
    out << "|< in" << std::endl << "v" << std::endl;
    for(const Layer& layer: self.m_layers)
    {
        out << layer << std::endl;
        out << "v" << std::endl;
    } 
    out << "|> out";

    return out;
}