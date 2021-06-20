#include "player.hpp"

Player::Player(const sf::Vector2u& windowSize, const sf::Texture& texture): Bird(windowSize, texture)
{
}

Player::~Player()
{
}

void Player::process(
    const WallManager& wallManager, const sf::Vector2u& windowSize)
{
    if(collide(wallManager, windowSize))
    {
        m_isDead = true;
    }

    sf::Vector2f target = wallManager.getTargetPos(getPosition(), SHAPE_RADIUS);

    applyPhysics();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // make the shape follow bird's position

    target.draw(m_shape, states);
}
