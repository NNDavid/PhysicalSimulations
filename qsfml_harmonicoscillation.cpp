#include "qsfml_harmonicoscillation.h"
#include "harmonicoscillator_solver.h"
#include <SFML/Graphics.hpp>
namespace harmonicoscillation {


QSFML_HarmonicOscillation::QSFML_HarmonicOscillation(QWidget* parent, const QPoint& position, const QSize& size):QSFML_Canvas(parent,position,size),diff_(solver::EXACT),pause_(true){}
void QSFML_HarmonicOscillation::onInit()
{
    solver_ = new solver::HarmonicOscillator_ExactSolver(this);
}


QSFML_HarmonicOscillation::~QSFML_HarmonicOscillation()
{
    delete solver_;
}

void QSFML_HarmonicOscillation::onUpdate()
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
    sf::RenderWindow::clear(sf::Color(150, 200, 110));
     solver_->draw();
   //  std::cout<<"drawn"<<std::endl;
    }
}

void QSFML_HarmonicOscillation::setDiffEqSolver(const solver::DiffEqSolver diff)
{
    diff_ = diff;
}
void QSFML_HarmonicOscillation::restartSimulation()
{
    solver_->restartSimulation();
}
void QSFML_HarmonicOscillation::startSimulation(const double mass, const double elastic_constant, const double amplitude)
{
    pause_ = true;
    if(solver_->getSolverType() != diff_)
    {
        delete solver_;
        switch (diff_)
        {
            case solver::EXACT: solver_ = new solver::HarmonicOscillator_ExactSolver(this,mass,elastic_constant,amplitude);break;
            case solver::EULER: solver_ = new solver::HarmonicOscillator_EulerSolver(this,mass,elastic_constant,amplitude);break;
        }

    }
    else solver_->setParameters(mass,elastic_constant,amplitude);
    solver_->restartSimulation();
    pause_ = false;
}

} //namespace harmonicoscillation
