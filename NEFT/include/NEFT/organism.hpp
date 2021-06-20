#ifndef ORGANISM_HPP
#define ORGANISM_HPP

#include "nn.hpp"
#include "dna.hpp"

class Organism
{
private:
    float m_fitness;

protected:
    NN m_brain;
    DNA m_dna;

    bool m_isDead;

public:
    Organism(
        const int& brainInputSize, 
        const std::vector<int>& hiddenLayersSizes,
        const int& braineOutputSize);
    virtual ~Organism();

    NN getBrain() const;
    std::vector<float> think(const std::vector<float>& input) const;

    DNA getDna() const;
    void setDna(const std::vector<float>& genes);

    float getFitness() const;
    void setFitness(const float& fitness);

    bool isDead() const;
    void setDead(const bool& isDead);

    static Organism* crossover(Organism* parentA, Organism* parentB);
    void mutate(const float& mutRate, const float& min, const float& max);

    friend std::ostream& operator<<(std::ostream& out, Organism* self);

    /* usefull abstract functions */
    virtual Organism* copy() const = 0;
};



#endif
