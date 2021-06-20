#ifndef WALL_MANAGER_HPP
#define WALL_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "NEFT/utils.hpp"
#include "wall.hpp"

class WallManager
{
private:
    float m_gapLength; // between each wall
    std::vector<Wall> m_walls;

    float m_wallSpeed;

public:
    WallManager(const int& size, const sf::Vector2u& windowSize);
    ~WallManager();

    float getWallSpeed() const;
    void setWallSpeed(const float& wallSpeed);

    void process(const sf::Vector2u& windowSize);
    std::vector<Wall> getWalls() const;
    void setWallSize(const sf::Vector2f& size, const sf::Vector2u& windowSize);
    void reset(const sf::Vector2u& windowSize);
    sf::Vector2f getTargetPos(
        const sf::Vector2f& from, const float& shapeRadius) const;
};


#endif