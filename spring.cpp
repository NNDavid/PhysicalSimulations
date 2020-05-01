#include "spring.h"
#include <math.h>
Spring::Spring(const sf::Vector2f& first_end,const sf::Vector2f& second_end,const int line_num):first_end_(first_end),second_end_(second_end)
{
    float line_length = 3.0;
    rectangles_.resize(line_num);
    rectangles_[0] = new sf::RectangleShape(sf::Vector2f(line_length/2.0,5.0));
    rectangles_[0]->setPosition(first_end);
    rectangles_[0]->setRotation(10.0f);
    for(QVector<sf::RectangleShape*>::size_type i = 1;i<rectangles_.size() - 1;i++)
    {
        rectangles_[i] = new sf::RectangleShape(sf::Vector2f(line_length,5.0));
        rectangles_[i]->setPosition(rectangles_[i-1]->getPosition() + sf::Vector2f(cos(10.0) * line_length,sin(10.0) * 5.0));

        if(i % 2 == 1) rectangles_[i]->setRotation(180 + 10.0f);
        else rectangles_[i]->setRotation(10.0f);

    }
    rectangles_.back() = new sf::RectangleShape(sf::Vector2f(line_length/2.0,5.0));

}
Spring::~Spring()
{
    for(QVector<sf::RectangleShape*>::size_type i = 0;i<rectangles_.size();i++) delete rectangles_[i];
}
sf::Vector2f Spring::getFirst_end() const {return first_end_;}
sf::Vector2f Spring::getSecond_end() const {return second_end_;}
void Spring::setPosition(const sf::Vector2f& first_end,const sf::Vector2f& second_end)
{
    first_end_ = first_end;
    second_end_ = second_end;
}
void Spring::draw(sf::RenderWindow& window) const
{
    for(QVector<sf::RectangleShape*>::size_type i = 0;i<rectangles_.size();i++) window.draw(*rectangles_[i]);
}
