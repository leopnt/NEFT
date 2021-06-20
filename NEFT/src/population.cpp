#include "NEFT/population.hpp"

Population::Population(): m_generation(0), m_mutationRate(0.01f)
{
    m_array = std::vector<Organism*>();

    std::cout << "Population::>mutationRate set to " << m_mutationRate;
    std::cout << std::endl;
}

Population::Population(const float& mutationRate):
    m_generation(0), m_mutationRate(mutationRate)
{
    m_array = std::vector<Organism*>();

    std::cout << "Population::>mutationRate set to " << m_mutationRate;
    std::cout << std::endl;
}

Population::~Population()
{
    for(Organism* organism: m_array)
    {
        delete organism;
        organism = nullptr;
    }
}

void Population::addOrganism(Organism* newOrganism)
{
    m_array.push_back(newOrganism);
}

Organism* Population::get(const int& i) const
{
    return m_array[i];
}

std::vector<Organism*> Population::get() const
{
    return m_array;
}

float Population::getMutationRate() const
{
    return m_mutationRate;
}

bool Population::everybodyDead() const
{
    for(Organism* organism: m_array)
    {
        if(!organism->isDead()) return false;
    }

    return true;
}

void Population::nextGeneration()
{
    calcFitness();
    std::vector<Organism*> matingPool = getMatingPool();

    /* begin reproduction */
    int size = (int) m_array.size();

    // delete each organism before new allocation
    for(Organism* organism: m_array)
    {
        delete organism;
        organism = nullptr;
    }

    for(int i = 0; i < size; i++)
    {
        Organism* parentA(pickParent(matingPool));
        Organism* parentB(pickParent(matingPool));

        Organism* child = Organism::crossover(parentA, parentB)->copy();
        m_array[i] = child;
        m_array[i]->mutate(m_mutationRate, -1.f, 1.f);

        delete parentA;
        parentA = nullptr;
        delete parentB;
        parentB = nullptr;
    }

    /* end of reproduction */

    // free mating pool
    for(Organism* organism: matingPool)
    {
        delete organism;
        organism = nullptr;
    }

    m_generation++;
}

void Population::calcFitness()
{
    // normalize the fitness according to the population
    float fitSum = 0;
    for(Organism* organism: m_array)
    {
        organism->setFitness(0.01 * pow(organism->getFitness(), 2));
        fitSum += organism->getFitness();
    }
    for(Organism* organism: m_array)
    {
        organism->setFitness(organism->getFitness() / (fitSum + 1));
        // avoid zero-division errors by adding 1
    }
}

int Population::getGeneration() const
{
    return m_generation;
}

Organism* Population::getBest() const
{
    float bestFit = m_array[0]->getFitness();
    int bestIndex = 0;
    for(size_t i = 1; i < m_array.size(); i++)
    {
        if(m_array[i]->getFitness() > bestFit)
        {
            bestFit = m_array[i]->getFitness();
            bestIndex = i;
        }
    }

    return m_array[bestIndex];
}

std::vector<Organism*> Population::getMatingPool() const
{
    std::vector<Organism*> matingPool = std::vector<Organism*>();
    for(Organism* organism: m_array)
    {
        int orgPercent = int(organism->getFitness() * 100.f + 1.f);
        for(int i = 0; i < orgPercent; i++)
        {
            matingPool.push_back(organism->copy());
        }
    }

    return matingPool;
}

Organism* Population::pickParent(const std::vector<Organism*>& matingPool) const
{
    int r = int(Utils::random((float) matingPool.size() -1));
    return matingPool[r]->copy();
}

