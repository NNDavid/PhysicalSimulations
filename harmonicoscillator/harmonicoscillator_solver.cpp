#include "harmonicoscillator_solver.h"
#include "drawer.h"
#include <cmath>
#include <iostream>

namespace draw
{
HarmonicOscillator_SimulationDrawer::HarmonicOscillator_SimulationDrawer(sf::RenderWindow* window):Drawer(window),spring_(sf::Vector2f(0,0),sf::Vector2f(0,0),10,50)
{
    body_.setRadius(50.0);
    body_.setOrigin(body_.getRadius(),body_.getRadius());
    body_.setFillColor(sf::Color::Red);
    body_.setPosition(window_->getSize().x/2.0,window_->getSize().y/2.0);
}
HarmonicOscillator_SimulationDrawer::~HarmonicOscillator_SimulationDrawer(){}
void HarmonicOscillator_SimulationDrawer::draw(const double& data)
{
    Drawer::draw(data);
    if(msgbox == nullptr && draw_data != draw_data)
    {
        msgbox = new QMessageBox(QMessageBox::Icon::Critical,"Simulation has crashed","We are sorry to inform you that the differential equation solver has crashed!",QMessageBox::Button::Yes);
        msgbox->show();
    }

    body_.setPosition(window_->getSize().x / 2.0, window_->getSize().y / 2.0 + draw_data);
    spring_.draw(window_,sf::Vector2f(window_->getSize().x / 2.0,spring_.getRadius()),sf::Vector2f(window_->getSize().x / 2.0,window_->getSize().y / 2.0 + draw_data));
    window_->draw(body_);
}
DrawType HarmonicOscillator_SimulationDrawer::getDrawType() const {return Simulation;}

HarmonicOscillator_CompareSimulationDrawer::HarmonicOscillator_CompareSimulationDrawer(sf::RenderWindow* window):
    Drawer(window),
    spring1_(sf::Vector2f(0,0),sf::Vector2f(0,0),10,50),
    spring2_(sf::Vector2f(0,0),sf::Vector2f(0,0),10,50)
{
    body1_.setRadius(50.0);
    body1_.setOrigin(body1_.getRadius(),body1_.getRadius());
    body1_.setFillColor(sf::Color::Red);

    body2_.setRadius(50.0);
    body2_.setOrigin(body1_.getRadius(),body1_.getRadius());
    body2_.setFillColor(sf::Color::Green);



}
HarmonicOscillator_CompareSimulationDrawer::~HarmonicOscillator_CompareSimulationDrawer(){}
void HarmonicOscillator_CompareSimulationDrawer::draw(const std::pair<double,double>& data)
{
    Drawer::draw(data);
    if(msgbox == nullptr && draw_data.first != draw_data.first)
    {
        msgbox = new QMessageBox(QMessageBox::Icon::Critical,"Simulation has crashed","We are sorry to inform you that the differential equation solver has crashed!",QMessageBox::Button::Yes);
        msgbox->show();
    }
    body1_.setPosition(0.25f  * window_->getSize().x , window_->getSize().y / 2.0f + draw_data.first);
    spring1_.draw(window_,sf::Vector2f(0.25f * window_->getSize().x,spring1_.getRadius()),sf::Vector2f(0.25f * window_->getSize().x,window_->getSize().y / 2.0 + draw_data.first));

    body2_.setPosition(0.75f * window_->getSize().x, window_->getSize().y / 2.0 + draw_data.second);
    spring2_.draw(window_,sf::Vector2f(0.75f * window_->getSize().x,spring1_.getRadius()),sf::Vector2f(0.75f * window_->getSize().x,window_->getSize().y / 2.0 + draw_data.second));

    window_->draw(body1_);
    window_->draw(body2_);

}
DrawType HarmonicOscillator_CompareSimulationDrawer::getDrawType() const
{
    return Simulation;
}

}





namespace solver {
//Abstract class

HarmonicOscillator_Solver::HarmonicOscillator_Solver(sf::RenderWindow* window,const int rows, const int cols):
    Solver(window,new draw::HarmonicOscillator_SimulationDrawer(window),rows, cols)

{
    data_->setLabelText("Body data",0,0);
    data_->show();
}
HarmonicOscillator_Solver::~HarmonicOscillator_Solver()
{
}

void HarmonicOscillator_Solver::setParameters(const double mass, const double elastic_constant,const double amplitude)
{
    mass_ = mass;
    elastic_constant_ = elastic_constant;
    amplitude_ = amplitude;
}

//Exact solver
HarmonicOscillator_ExactSolver::HarmonicOscillator_ExactSolver(sf::RenderWindow* window):
    HarmonicOscillator_Solver(window){}

HarmonicOscillator_ExactSolver::~HarmonicOscillator_ExactSolver(){}

void HarmonicOscillator_ExactSolver::restartSimulation()
{

    circular_frequency_ = sqrt(elastic_constant_ / mass_);
        data_->raise();
    clock_.restart();
}

void HarmonicOscillator_ExactSolver::draw()
{
    told_ = clock_.getElapsedTime();
    double x_exact = (window_->getSize().y / 4.0) * cos(circular_frequency_ * told_.asSeconds());
    double v_exact = circular_frequency_ * amplitude_ * std::sin(circular_frequency_ * told_.asSeconds()) / 4.0;
    drawer_->draw(x_exact);
    double x_exact_exact = amplitude_ * cos(circular_frequency_ * told_.asSeconds());

    data_->setLabelText("x = " + QString::number(x_exact_exact,'f',3) + " m",1,0);
    data_->setLabelText("v = " + QString::number(v_exact,'f',3) + " m / s",2,0);
}

DiffEqSolver HarmonicOscillator_ExactSolver::getSolverType() const {return EXACT;}




//Euler solver

HarmonicOscillator_EulerSolver::HarmonicOscillator_EulerSolver(sf::RenderWindow* window):
    HarmonicOscillator_Solver(window){}
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

        v_ = vold_ + dt * (-elastic_constant_/mass_) * xold_;
        x_ = xold_ + dt * vold_;
        vold_ = v_;
        xold_ = x_;

    drawer_->draw(x_);

    data_->setLabelText("x = " + QString::number(x_,'f',3) + " m",1,0);
    data_->setLabelText("v = " + QString::number(v_,'f',3) + " m / s",2,0);

    told_ = time_now;
}

DiffEqSolver HarmonicOscillator_EulerSolver::getSolverType() const {return EULER;}

HarmonicOscillator_CompareEulerSolver::HarmonicOscillator_CompareEulerSolver(sf::RenderWindow* window,int rows, int cols):HarmonicOscillator_Solver(window,rows,cols),drawernew_(new draw::HarmonicOscillator_CompareSimulationDrawer(window)){}
HarmonicOscillator_CompareEulerSolver::~HarmonicOscillator_CompareEulerSolver(){}
void HarmonicOscillator_CompareEulerSolver::draw()
{
    sf::Time time_now = clock_.getElapsedTime();
    float dt = (time_now - told_).asSeconds();

        v_ = vold_ + dt * (-elastic_constant_/mass_) * xold_;
        x_ = xold_ +dt * vold_;
        vold_ = v_;
        xold_ = x_;
        double x_exact = (window_->getSize().y / 4.0) * cos(circular_frequency_ * time_now.asSeconds());
        double x_exact_exact = amplitude_ * cos(circular_frequency_ * time_now.asSeconds());
        double v_exact = circular_frequency_ * amplitude_ * std::sin(circular_frequency_ * time_now.asSeconds());
        drawernew_->draw(std::pair<double,double>(xold_,x_exact));
        data_->setLabelText("x exact = " + QString::number(x_exact_exact,'f',3) +" m",0,0);
        data_->setLabelText("v exact = " + QString::number(v_exact,'f',3) +" m",1,0);
        data_->setLabelText("x Euler= " + QString::number( x_ /(window_->getSize().y / 4.0) * amplitude_,'f',3) +" m / s",0,1);
        data_->setLabelText("v Euler = " + QString::number(vold_ / (window_->getSize().y / 4.0) * amplitude_,'f',3) +" m / s",1,1);
        told_ = time_now;
}
void HarmonicOscillator_CompareEulerSolver:: restartSimulation()
{
    circular_frequency_ = sqrt(elastic_constant_ / mass_);
    told_ = sf::seconds(0.0);
    xold_ = window_->getSize().y / 4.0;
    vold_ = 0;
     data_->raise();
    clock_.restart();
}

void HarmonicOscillator_CompareEulerSolver::pause()
{
    HarmonicOscillator_CompareEulerSolver::drawernew_->pause();
    data_->pause();
}
void HarmonicOscillator_CompareEulerSolver::unpause()
{
    HarmonicOscillator_CompareEulerSolver::drawernew_->unpause();
    data_->unpause();
}
DiffEqSolver HarmonicOscillator_CompareEulerSolver::getSolverType() const
{
    return COMPARE_EULER;
}


}
