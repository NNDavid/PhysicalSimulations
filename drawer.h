#ifndef DRAWER_H
#define DRAWER_H
#include <SFML/Graphics.hpp>
#include <QMessageBox>
namespace draw {
enum DrawType{Simulation,Trajectory};

template<typename DrawData>
class Drawer
{
public:
    Drawer(sf::RenderWindow* window):window_(window),pause_(true),msgbox(nullptr){}
    virtual ~Drawer(){}
    virtual DrawType getDrawType() const = 0;
    void pause(){pause_ = true;}
    void unpause(){
        pause_ = false;
        delete msgbox;
        msgbox = nullptr;
                  }
    virtual void draw(const DrawData& data)
    {
        if(!pause_){ draw_data = data;}
    }
protected:
    sf::RenderWindow* window_;
    bool pause_;
    DrawData draw_data;
    QMessageBox* msgbox;
};
}

#endif // DRAWER_H
