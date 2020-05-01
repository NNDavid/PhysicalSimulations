#include "qsfml_oscillatingsupportpendulum.h"
#include <SFML/Graphics.hpp>
#include "drawer.h"
namespace oscillatingsupportpendulum {

QSFML_OscillatingSupportPendulum::QSFML_OscillatingSupportPendulum(QWidget* parent, const QPoint& position, const QSize& size):QSFML_Canvas(parent,position,size),diff_(solver::IMPLICIT_EULER),pause_(true){}

void QSFML_OscillatingSupportPendulum::onInit()
{
    solver_ = new solver::OscillatingSupportPendulum_ImplicitEulerSolver(this);
}
void QSFML_OscillatingSupportPendulum::onUpdate()
{

    sf::Event event;
    while(sf::RenderWindow::pollEvent(event))
    {
         if(event.type == sf::Event::Resized)
         {
           sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
           sf::RenderWindow::setView(sf::View(visibleArea));
         }
    }
     // Draw new frame
     if(!pause_) solver_->draw();

}


void QSFML_OscillatingSupportPendulum::setDiffEqSolver(const solver::DiffEqSolver diff)
{
    diff_ = diff;
}

void QSFML_OscillatingSupportPendulum::restartSimulation()
{
    sf::RenderWindow::clear(sf::Color::Black);
    solver_->restartSimulation();
    pause_ = false;
}
void QSFML_OscillatingSupportPendulum::startSimulation( const double length, const double amplitude,const double period,const double initialTheta)
{
    pause_ = true;
    solver_ ->setParameters(length,amplitude,period,initialTheta);
    restartSimulation();
}

void QSFML_OscillatingSupportPendulum::changeDraw(const bool is_checked)
{
    if(pause_) solver_->setDrawer(is_checked ? draw::Trajectory : draw::Simulation);
    else
    {
        pause_ = true;
        solver_->setDrawer(is_checked ? draw::Trajectory : draw::Simulation);
        pause_ = false;
    }
}


} //namespace oscillatingsupportpendulum
