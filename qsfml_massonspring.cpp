#include "qsfml_massonspring.h"
#include <SFML/Graphics.hpp>
#include <math.h>
namespace massonspring{
QSFML_MassOnSpring::QSFML_MassOnSpring(QWidget* parent, const QPoint& position, const QSize& size):QSFML_Canvas(parent,position,size),diff_(EULER){}
void QSFML_MassOnSpring::onInit()
{
    solver_ = new EulerSolver(this);
    emit simulationRestarted();
}
void QSFML_MassOnSpring::onUpdate()
{
   sf::Event event;
   while(sf::RenderWindow::pollEvent(event))
   {
        if(event.type == sf::Event::Resized)
        {
          sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
          sf::RenderWindow::setView(sf::View(visibleArea));
        }
        else if(event.type == sf::Event::MouseButtonReleased)
        {
            if(solver_->getSolverType() != diff_)
            {
                delete solver_;
                switch(diff_)
                {
                   case RK4: solver_ = new RK4_Solver(this);break;
                case EULER: solver_ = new EulerSolver(this);break;
                }
            }
            emit simulationRestarted();
            solver_->restartSimulation(event);
        }
   }
    // Draw new frame
   sf::RenderWindow::clear(sf::Color(100, 100, 110));
   solver_->draw();
}
}


