#ifndef DRAWER_H
#define DRAWER_H
#include <SFML/Graphics.hpp>
namespace draw {
enum DrawType{Simulation,Trajectory};

class Drawer
{
public:
    Drawer(sf::RenderWindow* window);
    virtual ~Drawer(){}
    virtual DrawType getDrawType() const = 0;
protected:
    sf::RenderWindow* window_;
};
}

#endif // DRAWER_H
