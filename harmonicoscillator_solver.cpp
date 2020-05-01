#include "harmonicoscillator_solver.h"
#include <math.h>
#include <iostream>
namespace solver {

//Abstract class

HarmonicOscillator_Solver::HarmonicOscillator_Solver(sf::RenderWindow* window,const double mass,const double elastic_constant, const double amplitude):
    Solver(window),
    mass_(mass),
    elastic_constant_(elastic_constant),
    amplitude_(amplitude)

{
    body_.setRadius(50.0);
    body_.setOrigin(body_.getRadius(),body_.getRadius());
    body_.setFillColor(sf::Color(128,0,0));
    body_.setPosition(window_->getSize().x/2.0,window_->getSize().y/2.0);

}
HarmonicOscillator_Solver::~HarmonicOscillator_Solver(){}

void HarmonicOscillator_Solver::setParameters(const double mass, const double elastic_constant,const double amplitude)
{
    mass_ = mass;
    elastic_constant_ = elastic_constant;
    amplitude_ = amplitude;
}

//Exact solver
HarmonicOscillator_ExactSolver::HarmonicOscillator_ExactSolver(sf::RenderWindow* window,const double mass,const double elastic_constant, const double amplitude):
    HarmonicOscillator_Solver(window,mass,elastic_constant,amplitude){}

HarmonicOscillator_ExactSolver::~HarmonicOscillator_ExactSolver(){}

void HarmonicOscillator_ExactSolver::restartSimulation()
{

    circular_frequency_ = sqrt(elastic_constant_ / mass_);
    clock_.restart();
}

void HarmonicOscillator_ExactSolver::draw()
{
    window_->clear(sf::Color(255,255,255));
    told_ = clock_.getElapsedTime();
    double x_exact = (window_->getSize().y / 4.0) * cos(circular_frequency_ * told_.asSeconds());
    //float v_exact = circular_frequency_ * amplitude_ * std::sin(circular_frequency_ * told_.asSeconds()) / 4.0;
    //float a_exact = -circular_frequency_ * circular_frequency_ * amplitude_ * sin(circular_frequency_ * told_.asSeconds()) / 4.0;
    body_.setPosition(window_->getSize().x / 2.0, window_->getSize().y / 2.0 + x_exact);
    std::cout << x_exact << " " << told_.asSeconds() <<" "<< body_.getPosition().x<<" " << body_.getPosition().y<<std::endl;
    window_->draw(body_);
}

DiffEqSolver HarmonicOscillator_ExactSolver::getSolverType() const {return EXACT;}




//Euler solver

HarmonicOscillator_EulerSolver::HarmonicOscillator_EulerSolver(sf::RenderWindow* window,const double mass,const double elastic_constant, const double amplitude):
    HarmonicOscillator_Solver(window,mass,elastic_constant,amplitude){restartSimulation();}
HarmonicOscillator_EulerSolver::~HarmonicOscillator_EulerSolver(){}



void HarmonicOscillator_EulerSolver::restartSimulation()
{
    told_ = sf::seconds(0.0);
    xold_ = window_->getSize().y / 4.0;
    vold_ = 0;
    clock_.restart();
}

void HarmonicOscillator_EulerSolver::draw()
{
    sf::Time time_now = clock_.getElapsedTime();
    float dt = (time_now - told_).asSeconds();
    int times = int(dt / h_);
    for(int i = 0 ;i < times;i++)
    {
        v_ = vold_ + h_ * (-elastic_constant_/mass_) * xold_;
        x_ = xold_+ h_ * vold_;
        vold_ = v_;
        xold_ = x_;
    }
    body_.setPosition(window_->getSize().x / 2.0, window_->getSize().y / 2.0 + x_);
    window_->draw(body_);
    told_ = time_now;
}

DiffEqSolver HarmonicOscillator_EulerSolver::getSolverType() const {return EULER;}


}
