#include "qsfml_oscillatingsupportpendulum.h"
#include <SFML/Graphics.hpp>
#include "drawer.h"


QSFML_OscillatingSupportPendulum::QSFML_OscillatingSupportPendulum(QWidget* parent, const QPoint& position, const QSize& size):
    QSFML_Canvas(parent,position,size),
    diff_(solver::IMPLICIT_EULER),
    solver_(new solver::OscillatingSupportPendulum_ImplicitEulerSolver(this))
    {}

void QSFML_OscillatingSupportPendulum::onInit(){}
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
sf::RenderWindow::clear(sf::Color::Black);
solver_->draw();

}

void QSFML_OscillatingSupportPendulum::setDiffEqSolver(const solver::DiffEqSolver diff)
{
    diff_ = diff;
}

void QSFML_OscillatingSupportPendulum::stopSimulation()
{
    solver_->pause();
}

void QSFML_OscillatingSupportPendulum::startSimulation( const double length, const double amplitude,const double period,const double initialTheta)
{
    solver_->pause();
    solver_ ->setParameters(length,amplitude,period,initialTheta);
    solver_->restartSimulation();
    solver_->unpause();
}

void QSFML_OscillatingSupportPendulum::changeDraw(const bool is_checked)
{
    solver_->pause();
    solver_->setDrawer(is_checked ? draw::Trajectory : draw::Simulation);
    solver_->unpause();
}


