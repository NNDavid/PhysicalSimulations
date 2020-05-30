#include "qsfml_massonspring.h"
#include <SFML/Graphics.hpp>
#include <cmath>

QSFML_MassOnSpring::QSFML_MassOnSpring(QWidget* parent, const QPoint& position, const QSize& size):QSFML_Canvas(parent,position,size),diff_(solver::MODIFIED_EULER),pause_(true){}
void QSFML_MassOnSpring::onInit()
{
    solver_ = new solver::MassOnSpring_ModifiedEulerSolver(this);
}

void QSFML_MassOnSpring::stopSimulation()
{
   solver_->pause();
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
    }
    sf::RenderWindow::clear(sf::Color::Black);
     // Draw new frame
   solver_->draw();

}


void QSFML_MassOnSpring::setDiffEqSolver(const solver::DiffEqSolver diff)
{
    diff_ = diff;
}
void QSFML_MassOnSpring::startSimulation(const double mass, const double elastic_constant, const double theta_initial,const double l,const double x)
{
    solver_->pause();

    if(solver_->getSolverType() != diff_)
    {
        delete solver_;
        if(diff_ == solver::MODIFIED_EULER) solver_ = new solver::MassOnSpring_ModifiedEulerSolver(this);
        else assert(false);
    }

    solver_->setParameters(mass,elastic_constant,theta_initial,l,x);
    solver_->restartSimulation();
    solver_->unpause();
}
void QSFML_MassOnSpring::changeDraw(const bool is_checked)
{

        solver_->pause();
        solver_->setDrawer(is_checked ? draw::Trajectory : draw::Simulation);
        solver_->unpause();
}



