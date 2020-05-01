#ifndef SPRING_H
#define SPRING_H
#include <SFML/Graphics.hpp>
#include <vector>
class Spring
{
public:
    Spring(const sf::Vector2f& first_end = sf::Vector2f(0,0),const sf::Vector2f& second_end = sf::Vector2f(0,0),const double circle_radius = 15,const int circle_num = 50);
    ~Spring();
    sf::Vector2f getFirst_end() const;
    sf::Vector2f getSecond_end() const;
    void setPosition(const sf::Vector2f& first_end,const sf::Vector2f& second_end);
    void draw(sf::RenderWindow* window,const sf::Vector2f& first_end,const sf::Vector2f& second_end);
    void setRadius(const double radius);
    double getRadius() const;

private:
    int circle_num_;
    double radius_;
    sf::Vector2f first_end_;
    sf::Vector2f second_end_;
    std::vector<sf::CircleShape> circles_;


};

#endif // SPRING_H
