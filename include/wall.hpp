#ifndef WALL_HPP
#define WALL_HPP

#include <SFML/Graphics.hpp>

class Wall : public sf::Transformable, public sf::Drawable
{
private:
    sf::Vector2f m_gapSize;

    sf::RectangleShape m_rectUp;
    sf::RectangleShape m_rectDown;

    void autoSize(const sf::Vector2u& windowSize);

    const sf::Color ACTIVE_COLOR = sf::Color(50, 210, 80);

public:
    Wall(const sf::Vector2u& windowSize);
    ~Wall();

    sf::Vector2f getSize() const;
    void setSize(const sf::Vector2f &size, const sf::Vector2u &windowSize);

    void process(const float& speed);
    bool collide(const sf::Vector2f& point, const float& radius) const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif