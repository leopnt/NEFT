#include "bird.hpp"

Bird::Bird(const sf::Vector2u &windowSize, const sf::Texture &texture) :
    Organism(3, {6, 4}, 1), m_gravity(sf::Vector2f(0.0f, 0.4f))
{
    reset(windowSize);
    m_shape.setRadius(SHAPE_RADIUS);
    // center the shape on bird's position
    m_shape.setOrigin(sf::Vector2f(m_shape.getRadius(), m_shape.getRadius()));
    m_shape.setFillColor(DEBUG_COLOR);

    m_sprite.setTexture(texture);
    m_sprite.setOrigin(32, 32);
    m_sprite.setColor(SPRITE_MODULATE);
}

Bird::~Bird()
{
}

sf::Vector2f Bird::getGravity() const
{
    return m_gravity;
}

void Bird::setGravity(const sf::Vector2f &gravity)
{
    m_gravity = gravity;
}

void Bird::applyImpulse(const sf::Vector2f &force)
{
    m_linearAcceleration += MASS * force;
}

void Bird::jump()
{
    applyImpulse(JUMP_FORCE);
}

bool Bird::collide(
    const WallManager &wallManager, const sf::Vector2u &windowSize) const
{
    // collision with walls
    for (Wall &wall : wallManager.getWalls())
    {
        if (wall.collide(getPosition(), m_shape.getRadius()))
        {
            return true;
        }
    }

    // collision with window boundaries
    if (getPosition().y < 0 || getPosition().y > windowSize.y)
    {
        return true;
    }

    return false;
}

sf::CircleShape Bird::getShape() const
{
    return m_shape;
}

void Bird::reset(const sf::Vector2u &windowSize)
{
    m_isDead = false;
    setPosition(sf::Vector2f(100.f, float(windowSize.y) / 2.f));
    m_linearAcceleration *= 0.f;
    m_linearVelocity *= 0.f;
    setFitness(0);
}

void Bird::process(
    const WallManager &wallManager, const sf::Vector2u &windowSize)
{
    if (!isDead())
    {
        if (collide(wallManager, windowSize))
        {
            setDead(true);
        }

        sf::Vector2f targetPos = wallManager.getTargetPos(
            getPosition(), SHAPE_RADIUS);
        // wait that bird has passed the wall:
        targetPos += sf::Vector2f(SHAPE_RADIUS, 0.f);

        std::vector<float> input = std::vector<float>(3);
        input[0] = targetPos.x / float(windowSize.x); // normalize
        input[1] = targetPos.y / float(windowSize.y);
        input[2] = 0.1f * m_linearVelocity.y;

        //Utils::printArray(input);
        bool shouldJump = think(input)[0] > 0.f;
        if (shouldJump)
            jump();

        applyPhysics();

        // rotation movement with falling speed
        bool heaviside = m_linearVelocity.y > 1.f;
        float angle = heaviside * pow(m_linearVelocity.y - 1.f, 2);
        if (angle > 90.f)
            angle = 90.f;
        setRotation(angle - 5.f);

        setFitness(getFitness() + 0.1f);
    }
}

void Bird::applyPhysics()
{
    applyImpulse(m_gravity); // gravity
    m_linearVelocity += m_linearAcceleration;
    move(m_linearVelocity);
    m_linearAcceleration *= 0.f; // reset acceleration to keep impulse effect
}

void Bird::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // make the shape follow bird's position

    // draw collision shape
    //target.draw(m_shape, states);

    target.draw(m_sprite, states);
}

Bird *Bird::copy() const
{
    // return a pointer to a copy of the current bird

    Bird *copyBird = new Bird(*this);
    return copyBird;
}
