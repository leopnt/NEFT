#ifndef BIRD_HPP
#define BIRD_HPP

#include <SFML/Graphics.hpp>
#include "NEFT/organism.hpp"
#include "wall_manager.hpp"

class Bird : public Organism, public sf::Transformable, public sf::Drawable
{
protected:
    sf::CircleShape m_shape;
    
    sf::Sprite m_sprite;

    sf::Vector2f m_linearVelocity;
    sf::Vector2f m_linearAcceleration;
    sf::Vector2f m_gravity;

    const float MASS = 1.f;
    const float SHAPE_RADIUS = 20.f;
    const sf::Color DEBUG_COLOR = sf::Color(255, 0, 0, 50);
    const sf::Color SPRITE_MODULATE = sf::Color(255, 255, 255, 170);
    const sf::Vector2f JUMP_FORCE = sf::Vector2f(0.f, -14.f);

    void applyPhysics();
    bool collide(
        const WallManager& wallManager, const sf::Vector2u& windowSize) const;

public:
    Bird(const sf::Vector2u& windowSize, const sf::Texture& texture);
    ~Bird();

    sf::Vector2f getGravity() const;
    void setGravity(const sf::Vector2f& gravity);

    void applyImpulse(const sf::Vector2f& force);
    void jump();
    
    sf::CircleShape getShape() const;

    void reset(const sf::Vector2u& windowSize);
    void process(
        const WallManager& wallManager, const sf::Vector2u& windowSize);
    

    /* methods relative to abstract classes that this object inherit from */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual Bird* copy() const;
};

#endif
