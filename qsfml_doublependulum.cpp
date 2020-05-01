#include "qsfml_doublependulum.h"
namespace doublependulum {


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
    if(!pause_)
    {
    sf::RenderWindow::clear(sf::Color::Black);
     solver_->draw();
   //  std::cout<<"drawn"<<std::endl;
    }
}

void QSFML_DoublePendulum::setDiffEqSolver(const solver::DiffEqSolver diff)
{
    diff_ = diff;
}
void QSFML_DoublePendulum::restartSimulation()
{
    solver_->restartSimulation();
}
void QSFML_DoublePendulum::startSimulation(const double mass1,const double length1,const double mass2,const double length2,const double theta1, const double theta2)
{
    pause_ = true;

    if(solver_->getSolverType() != diff_)
    {
        delete solver_;
        if(diff_ == solver::RK4) solver_ = new solver::DoublePendulum_RK4Solver(this);
        else if(diff_ == solver::IMPLICIT_EULER) solver_ = new solver::DoublePendulum_ImplicitEulerSolver(this);
    }

    solver_->setParameters(mass1,length1,mass2,length2,theta1,theta2);
    solver_->restartSimulation();
    pause_ = false;
}
void QSFML_DoublePendulum::changeDraw(const bool is_checked)
{
    if(pause_) solver_->setDrawer(is_checked ? draw::Trajectory : draw::Simulation);
    else
    {
        pause_ = true;
        solver_->setDrawer(is_checked ? draw::Trajectory : draw::Simulation);
        pause_ = false;
    }
}
}
