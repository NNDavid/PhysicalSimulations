#include "qsfml_doublependulum.h"
#include <iostream>
QSFML_DoublePendulum::QSFML_DoublePendulum(QWidget* parent, const QPoint& position, const QSize& size):QSFML_Canvas(parent,position,size),solver_(new solver::DoublePendulum_RK4Solver(this)),diff_(solver::RK4)
{

}
QSFML_DoublePendulum::~QSFML_DoublePendulum(){}
void QSFML_DoublePendulum::onInit(){}
void QSFML_DoublePendulum::onUpdate()
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

void QSFML_DoublePendulum::setDiffEqSolver(const solver::DiffEqSolver diff)
{
    diff_ = diff;
}
void QSFML_DoublePendulum::stopSimulation()
{
    solver_->pause();
}
void QSFML_DoublePendulum::startSimulation(const double mass1,const double length1,const double mass2,const double length2,const double theta1, const double theta2)
{
    solver_->pause();

    if(solver_->getSolverType() != diff_)
    {
        delete solver_;
        if(diff_ == solver::RK4) solver_ = new solver::DoublePendulum_RK4Solver(this);
        else if(diff_ == solver::IMPLICIT_EULER) solver_ = new solver::DoublePendulum_ImplicitEulerSolver(this);
        else assert(false);
    }

    solver_->setParameters(mass1,length1,mass2,length2,theta1,theta2);
    solver_->restartSimulation();
    solver_->unpause();
}
void QSFML_DoublePendulum::changeDraw(const bool is_checked)
{

     solver_->pause();
     solver_->setDrawer(is_checked ? draw::Trajectory : draw::Simulation);
     solver_->unpause();

}
