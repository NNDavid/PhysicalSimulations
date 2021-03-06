#include "qsfml_harmonicoscillation.h"
#include "harmonicoscillator_solver.h"
#include <SFML/Graphics.hpp>
#include <iostream>
namespace harmonicoscillation {


QSFML_HarmonicOscillation::QSFML_HarmonicOscillation(QWidget* parent, const QPoint& position, const QSize& size):QSFML_Canvas(parent,position,size),diff_(solver::EXACT){}
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

    sf::RenderWindow::clear(sf::Color::Black);
    solver_->draw();
}

void QSFML_HarmonicOscillation::setDiffEqSolver(const solver::DiffEqSolver diff)
{
    diff_ = diff;
}
void QSFML_HarmonicOscillation::stopSimulation()
{
    solver_->pause();
}
void QSFML_HarmonicOscillation::startSimulation(const double mass, const double elastic_constant, const double amplitude)
{
    solver_->pause();
    if(solver_->getSolverType() != diff_)
    {
        delete solver_;
        switch (diff_)
        {
            case solver::EXACT:         solver_ = new solver::HarmonicOscillator_ExactSolver(this);break;
            case solver::EULER:         solver_ = new solver::HarmonicOscillator_EulerSolver(this);break;
            case solver::COMPARE_EULER: solver_ = new solver::HarmonicOscillator_CompareEulerSolver(this);break;
            default: assert(false);break;
        }

    }
    solver_->setParameters(mass,elastic_constant,amplitude);
    solver_->restartSimulation();
    solver_->unpause();
}

} //namespace harmonicoscillation
