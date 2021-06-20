#include "wall_manager.hpp"

WallManager::WallManager(
    const int& size, const sf::Vector2u& windowSize): m_wallSpeed(2.f)
{
    m_walls = std::vector<Wall>();
    m_gapLength = float(windowSize.x) / float(size);
    
    // size + 1 to keep constant gap between walls sequences
    for(int i = 0; i < size + 1; i++)
    {
        m_walls.push_back(Wall(windowSize));
    }
    reset(windowSize);
}

WallManager::~WallManager()
{
}

float WallManager::getWallSpeed() const
{
    return m_wallSpeed;
}

void WallManager::setWallSpeed(const float& wallSpeed)
{
    m_wallSpeed = wallSpeed;
}

void WallManager::process(const sf::Vector2u& windowSize)
{
    for(Wall& wall: m_walls)
    {
        wall.process(m_wallSpeed);

        // reset new wall position when it goes outside of window
        if(wall.getPosition().x < -m_gapLength)
        {
            wall.setPosition(
                float(windowSize.x),
                Utils::randrange(0.2f * windowSize.y, 0.5f * windowSize.y));
        }
    }
}

std::vector<Wall> WallManager::getWalls() const
{
    return m_walls;
}


void WallManager::setWallSize(
    const sf::Vector2f& size, const sf::Vector2u& windowSize)
{
    for(Wall& wall: m_walls)
    {
        wall.setSize(size, windowSize);
    }
}

void WallManager::reset(const sf::Vector2u& windowSize)
{
    for(size_t i = 0; i < m_walls.size(); i++)
    {
        m_walls[i].setPosition(
            float(i + 2) * m_gapLength,
            Utils::randrange(0.2f * windowSize.y, 0.5f * windowSize.y));
    }
}

sf::Vector2f WallManager::getTargetPos(
    const sf::Vector2f& from, const float& shapeRadius) const
{
    // return the position of the closest wall to "from"

    sf::Vector2f closestPos = sf::Vector2f(4000.f, 0.f); // get an overshoot
    for(const Wall& wall: m_walls)
    {
        float dist = wall.getPosition().x - from.x; // to beginning of wall
        dist += wall.getSize().x; // aim at end of wall
        dist += shapeRadius; // wait for the shape to have passed the wall

        if(dist > 0 && dist < closestPos.x)
        {
            // aim at middle right
            closestPos = wall.getPosition() + sf::Vector2f(
                wall.getSize().x + shapeRadius, 0.5f * wall.getSize().y);
        }
    }

    return closestPos - from;
}