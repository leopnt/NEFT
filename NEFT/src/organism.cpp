#include "NEFT/organism.hpp"

Organism::Organism(
    const int& brainInputSize,
    const std::vector<int>& hiddenLayersSizes,
    const int& braineOutputSize):
        m_fitness(0.f),
        m_brain(brainInputSize, braineOutputSize),
        m_isDead(false)
{
    // add hidden layers
    for(const int& layerSize: hiddenLayersSizes)
    {
        m_brain.addLayer(layerSize);
    }
    m_dna.set(m_brain.getWeights());    // It is very important to update DNA
                                        // each time there is a modification
                                        // on the neural net and vice-versa.
                                        // It is on the responsability of this
                                        // class to give approriate set/get
                                        // and handle it correctly
}

Organism::~Organism()
{
}

NN Organism::getBrain() const
{
    return m_brain;
}

std::vector<float> Organism::think(const std::vector<float>& input) const
{
    return m_brain.output(input);
}

DNA Organism::getDna() const
{
    return m_dna;
}

void Organism::setDna(const std::vector<float>& genes)
{
    m_dna.set(genes);
    m_brain.setWeights(m_dna.get());
}

float Organism::getFitness() const
{
    return m_fitness;
}

void Organism::setFitness(const float& fitness)
{
    m_fitness = fitness;
}

bool Organism::isDead() const
{
    return m_isDead;
}

void Organism::setDead(const bool& isDead)
{
    m_isDead = isDead;
}

Organism* Organism::crossover(Organism* parentA, Organism* parentB)
{
    // use parentA as an exemple for the child.

    int dnaSize = parentA->m_dna.get().size();
    int separator = int(Utils::random(dnaSize));

    std::vector<float> crossedGenes  = std::vector<float>();
    for(int i = 0; i < separator; i++)
    {
        // add parentA genes
        crossedGenes.push_back(parentA->m_dna.get()[i]);
    }
    for(int i = separator; i < dnaSize; i++)
    {
        // add parentB genes
        crossedGenes.push_back(parentB->getDna().get()[i]);
    }

    Organism* child(parentA);
    child->setDna(crossedGenes);
    // Set the new crossover genes: the only thing that changes between children
    // and parents. 
    // We keep the topology but the neural net weights are updated in setDna()

    return child;
}

void Organism::mutate(const float& mutRate, const float& min, const float& max)
{
    m_dna.mutate(mutRate, min, max);
    m_brain.setWeights(m_dna.get());
}

std::ostream& operator<<(std::ostream& out, Organism* self)
{
    out << self->m_brain << std::endl;
    out << "\\DNA: ";
    Utils::printArray(self->m_dna.get());

    return out;
}