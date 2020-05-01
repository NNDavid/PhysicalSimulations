#ifndef SPRING_H
#define SPRING_H
#include <SFML/Graphics.hpp>
#include <QVector>
class Spring
{
public:
    Spring(const sf::Vector2f& first_end = sf::Vector2f(0,0),const sf::Vector2f& second_end = sf::Vector2f(0,0),const int line_num = 20);
    ~Spring();
    sf::Vector2f getFirst_end() const;
    sf::Vector2f getSecond_end() const;
    void setPosition(const sf::Vector2f& first_end,const sf::Vector2f& second_end);
    void draw(sf::RenderWindow& window) const;
private:
    sf::Vector2f first_end_;
    sf::Vector2f second_end_;
    int line_num_;
    QVector<sf::RectangleShape*> rectangles_;


};

#endif // SPRING_H
