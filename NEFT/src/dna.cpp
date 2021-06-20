#include "NEFT/dna.hpp"

DNA::DNA()
{
    m_genes = std::vector<float>();
}

DNA::~DNA()
{
}

void DNA::mutate(const float& mutationRate, const float& min, const float& max)
{
    // pick a gene and randomize it with a probability of mutationRate

    for(float& elt: m_genes)
    {
        float r = Utils::random();
        if(r < mutationRate) elt = Utils::randrange(min, max);
    }
}

std::vector<float> DNA::get() const
{
    return m_genes;
}

void DNA::set(const std::vector<float>& array)
{
    m_genes.clear();
    for(const float& gene: array)
    {
        m_genes.push_back(gene);
    }
}