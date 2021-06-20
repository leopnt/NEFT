#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "bird.hpp"

class Player : public Bird
{
public:
    Player(const sf::Vector2u& windowSize, const sf::Texture& texture);
    ~Player();

    virtual void process(
        const WallManager& wallManager, const sf::Vector2u& windowSize);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif
