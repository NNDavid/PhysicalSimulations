#include "spring.h"
#include <math.h>
Spring::Spring(const sf::Vector2f& first_end,const sf::Vector2f& second_end,const double circle_radius,const int circle_num):circle_num_(circle_num),radius_(circle_radius),first_end_(first_end),second_end_(second_end)
{
    circles_.resize(circle_num_);
    for(size_t i = 0; i< circles_.size();i++)
    {
        circles_[i].setFillColor(sf::Color::Transparent);
        circles_[i].setOutlineThickness(2);
        circles_[i].setOutlineColor(sf::Color::Blue);
        circles_[i].setRadius(radius_);
        circles_[i].setOrigin(circles_[i].getRadius(),circles_[i].getRadius());
    }
}
Spring::~Spring()
{
    circles_.clear();
}
sf::Vector2f Spring::getFirst_end() const {return first_end_;}
sf::Vector2f Spring::getSecond_end() const {return second_end_;}
void Spring::setPosition(const sf::Vector2f& first_end,const sf::Vector2f& second_end)
{
    first_end_ = first_end;
    second_end_ = second_end;
}
void Spring::draw(sf::RenderWindow* window,const sf::Vector2f& first_end,const sf::Vector2f& second_end)
{
    setPosition(first_end,second_end);
    sf::Vector2f dist = (second_end_ - first_end_) / float(circle_num_);
    sf::Vector2f position = first_end_;

    for(std::vector<sf::CircleShape>::iterator it = circles_.begin();it != circles_.end();it++)
    {
       it->setPosition(position);
       window->draw(*it);
       position += dist;
    }



}
void Spring::setRadius(const double radius)
{
    radius_ = radius;
    for(std::vector<sf::CircleShape>::iterator it = circles_.begin();it != circles_.end();it++)
    {
        it->setRadius(radius);
        it->setOrigin(it->getRadius(),it->getRadius());
    }
}
double Spring::getRadius() const
{
    return radius_;
}
