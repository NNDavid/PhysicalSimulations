#include "oscillatingsupportpendulum_solver.h"
#include <math.h>
#include <iostream>


namespace draw{
OscillatingSupportPendulum_Drawer::OscillatingSupportPendulum_Drawer(sf::RenderWindow* window):Drawer(window){}


OscillatingSupportPendulum_SimulationDrawer::OscillatingSupportPendulum_SimulationDrawer(sf::RenderWindow* window):OscillatingSupportPendulum_Drawer(window)
{
    body_.setRadius(25);
    body_.setOrigin(body_.getRadius(),body_.getRadius());
    body_.setFillColor(sf::Color::Red);
    body_.setPosition(window_->getSize().x / 2.0,0.75 * window_->getSize().y);

    support_.setSize(sf::Vector2f(100,30));
    support_.setOrigin(support_.getSize().x / 2.0,support_.getSize().y / 2.0);
    support_.setFillColor(sf::Color::Blue);

    rod_.setFillColor(sf::Color::White);
}

void OscillatingSupportPendulum_SimulationDrawer::draw(const double support_position, const double theta)
{
    body_.setPosition((window_->getSize().x / 2.0) + support_position + (window_->getSize().y / 4.0) * sin(theta),window_->getSize().y / 2.0  + (window_->getSize().y / 4.0) * cos(theta));

    rod_.setPosition(window_->getSize().x / 2.0 + support_position, window_->getSize().y / 2.0);
    rod_.setRotation( -180 * theta / M_PI);

    support_.setPosition(window_->getSize().x / 2.0 + support_position, window_->getSize().y / 2.0);
    window_->clear(sf::Color::Black);
    window_->draw(rod_);
    window_->draw(support_);
    window_->draw(body_);

}
DrawType OscillatingSupportPendulum_SimulationDrawer::getDrawType() const{return Simulation;}

void OscillatingSupportPendulum_SimulationDrawer::reset()
{
    rod_.setSize(sf::Vector2f(10,window_->getSize().y / 4.0));
    rod_.setOrigin(rod_.getSize().x / 2.0, 0);
}
OscillatingSupportPendulum_TrajectoryDrawer::OscillatingSupportPendulum_TrajectoryDrawer(sf::RenderWindow* window):OscillatingSupportPendulum_Drawer(window),first(true)
{
    body_.setRadius(2);
    body_.setOrigin(body_.getRadius(),body_.getRadius());
    body_.setFillColor(sf::Color::Red);
    body_.setPosition(window_->getSize().x / 2.0,0.75 * window_->getSize().y);
}
void OscillatingSupportPendulum_TrajectoryDrawer::draw(const double support_position, const double theta)
{
    body_.setPosition((window_->getSize().x / 2.0) + support_position + (window_->getSize().y / 4.0) * sin(theta),window_->getSize().y / 2.0  + (window_->getSize().y / 4.0) * cos(theta));
    if(trajectory.size() > 5000) trajectory.pop_back();
    trajectory.push_front(body_);
    window_->clear(sf::Color::Black);
    for(std::deque<sf::CircleShape>::iterator it = trajectory.begin();it != trajectory.end();it++) window_->draw(*it);

}

DrawType OscillatingSupportPendulum_TrajectoryDrawer::getDrawType() const{return Trajectory;}
void OscillatingSupportPendulum_TrajectoryDrawer::reset()
{
    trajectory.clear();
}
}


namespace solver{

//abstract
OscillatingSupportPendulum_Solver::OscillatingSupportPendulum_Solver(sf::RenderWindow* window):
    Solver(window),
    drawer_(new draw::OscillatingSupportPendulum_SimulationDrawer(window)),
    data_(new simdata::SimulationData(3,2))
{
    data_->setLabelText("Body data",0,0);
    data_->setLabelText("Support position",0,1);
    data_->show();
}

OscillatingSupportPendulum_Solver::~OscillatingSupportPendulum_Solver(){}

void OscillatingSupportPendulum_Solver::setParameters(const double length,const double amplitude,const double period,const double theta_initial)
{
    length_ = length;
    amplitude_ = amplitude;
    period_ = period;
    theta_initial_ = theta_initial * M_PI;
}


double OscillatingSupportPendulum_Solver::getSupportAcceleration(const double time)
{
    return -amplitude_ * omega_ * omega_ * cos(omega_ * time);
}

double OscillatingSupportPendulum_Solver::getSupportPosition(const double time)
{
    return amplitude_ * cos(omega_ * time);
}

double OscillatingSupportPendulum_Solver::getBodyAcceleration(const double theta, const double support_acceleration)
{
    return -(support_acceleration * cos(theta) + g * sin(theta)) / length_;
}
double OscillatingSupportPendulum_Solver::getBodyCanvasPosition(const double time)
{
    return window_->getSize().x / 4.0 * cos(omega_ * time);
}



void OscillatingSupportPendulum_Solver::setDrawer(const draw::DrawType draw)
{
    if(draw != drawer_->getDrawType())
    {
        delete drawer_;
        switch(draw)
        {
            case draw::Simulation: drawer_ = new draw::OscillatingSupportPendulum_SimulationDrawer(window_);break;
            case draw::Trajectory: drawer_ = new draw::OscillatingSupportPendulum_TrajectoryDrawer(window_);break;
        }
    }
    drawer_->reset();
}

//Implicit Euler
OscillatingSupportPendulum_ImplicitEulerSolver::OscillatingSupportPendulum_ImplicitEulerSolver(sf::RenderWindow* window):
    OscillatingSupportPendulum_Solver(window){}

OscillatingSupportPendulum_ImplicitEulerSolver::~OscillatingSupportPendulum_ImplicitEulerSolver(){}
void OscillatingSupportPendulum_ImplicitEulerSolver::restartSimulation()
{
    theta_ = theta_initial_;
    told_ = sf::seconds(0);
    thetaacc_ = getBodyAcceleration(theta_,getSupportAcceleration(0));
    thetavel_ = 0;
    omega_ = 2.0 * M_PI / period_;
    drawer_->reset();
    data_->raise();
    clock_.restart();
}


void OscillatingSupportPendulum_ImplicitEulerSolver::draw()
{
    sf::Time time_now = clock_.getElapsedTime();
    double dt = (time_now - told_).asSeconds();
    std::cout << dt << std::endl;

   theta_ += dt * thetavel_;
   thetavel_ += dt * getBodyAcceleration(theta_,getSupportAcceleration(time_now.asSeconds() + dt));

   drawer_->draw(getBodyCanvasPosition(time_now.asSeconds()),theta_);

   data_->setLabelText("Θ = " + QString::number(theta_ / M_PI,'f',3) + " π",1,0);
   data_->setLabelText("Θ velocity = " + QString::number(thetavel_ / M_PI,'f',3) + " π / s",2,0);

   data_->setLabelText("x = " + QString::number(getSupportPosition(time_now.asSeconds())) + " m",1,1);
   told_ = time_now;
}
DiffEqSolver OscillatingSupportPendulum_ImplicitEulerSolver::getSolverType() const {return IMPLICIT_EULER;}







} //namespace solver
