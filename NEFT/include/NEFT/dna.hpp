#ifndef DNA_HPP
#define DNA_HPP

#include <vector>
#include "utils.hpp"

class DNA
{
private:
    std::vector<float> m_genes;
public:
    DNA();
    ~DNA();

    void mutate(const float& mutationRate, const float& min, const float& max);
    std::vector<float> get() const;
    void set(const std::vector<float>& array);
};


#endif
