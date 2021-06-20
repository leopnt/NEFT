#include "wall.hpp"

Wall::Wall(const sf::Vector2u& windowSize): m_gapSize(sf::Vector2f(70.f, 140.f))
{
    autoSize(windowSize);
}

Wall::~Wall()
{
}

void Wall::autoSize(const sf::Vector2u& windowSize)
{
    m_rectDown.setPosition(0.f, m_gapSize.y);
    m_rectDown.setSize(sf::Vector2f(m_gapSize.x, float(windowSize.y)));
    m_rectDown.setFillColor(ACTIVE_COLOR);
    m_rectUp.setPosition(0.f, 0.f);
    m_rectUp.setSize(sf::Vector2f(m_gapSize.x, -float(windowSize.y)));
    m_rectUp.setFillColor(ACTIVE_COLOR);
}

sf::Vector2f Wall::getSize() const
{
    return m_gapSize;
}

void Wall::setSize(const sf::Vector2f &size, const sf::Vector2u& windowSize)
{
    m_gapSize = size;
    autoSize(windowSize);
}

void Wall::process(const float& speed)
{
    move(-speed, 0.f);
}

bool Wall::collide(const sf::Vector2f& point, const float& radius) const
{
    // returns true if there is an intersection with the UP or the DOWN wall

    // check inside rect gap on X axis
    bool isInLeft = point.x + radius > getPosition().x;
    bool isInRight = point.x - radius < getPosition().x + m_gapSize.x;
    bool isInsideX = isInLeft && isInRight;

    // check inside rect gap on Y axis
    bool isInUp = point.y - radius > getPosition().y;
    bool isInDown = point.y + radius < getPosition().y + m_gapSize.y;
    bool isInsideY = isInUp && isInDown;

    return isInsideX && !isInsideY;
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // make shapes members follow self

    target.draw(m_rectUp, states);
    target.draw(m_rectDown, states);
}
