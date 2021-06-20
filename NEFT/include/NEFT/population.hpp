#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "organism.hpp"

class Population
{
private:
    std::vector<Organism*> m_array;
    int m_generation;
    float m_mutationRate;


    void calcFitness();
    std::vector<Organism*> getMatingPool() const;
    Organism* pickParent(const std::vector<Organism*>& matingPool) const;

public:
    Population();
    Population(const float& mutationRate);
    ~Population();

    void addOrganism(Organism* newOrganism);

    Organism* get(const int& i) const;
    std::vector<Organism*> get() const;

    float getMutationRate() const;

    bool everybodyDead() const;

    int getGeneration() const;

    Organism* getBest() const;

    void nextGeneration();
};



#endif
