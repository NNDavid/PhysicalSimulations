#include "doublependulum_solver.h"
#include <cmath>
#include <iostream>


namespace draw {


DoublePendulum_Drawer::DoublePendulum_Drawer(sf::RenderWindow* window):Drawer(window){}
DoublePendulum_Drawer::~DoublePendulum_Drawer(){}

DoublePendulum_SimulationDrawer::DoublePendulum_SimulationDrawer(sf::RenderWindow* window):DoublePendulum_Drawer(window)
{
    body1_.setRadius(25);
    body1_.setOrigin(body1_.getRadius(),body1_.getRadius());
    body1_.setFillColor(sf::Color::Red);


    body2_.setRadius(25);
    body2_.setOrigin(body2_.getRadius(),body2_.getRadius());
    body2_.setFillColor(sf::Color::Blue);


    rod1_.setFillColor(sf::Color::White);

    rod2_.setFillColor(sf::Color::White);


}


void DoublePendulum_Drawer::reset(const double length1,const double length2)
{
    const double x = length1 / length2;
    canvas_length2_ = (window_->getSize().y / 2.0) / (x + 1.0);
    canvas_length1_ = x * canvas_length2_;
}

DoublePendulum_SimulationDrawer::~DoublePendulum_SimulationDrawer(){}
DrawType DoublePendulum_SimulationDrawer::getDrawType() const
{
    return Simulation;
}
void DoublePendulum_SimulationDrawer::draw(const double theta1, const double theta2)
{
    body1_.setPosition(window_->getSize().x / 2.0 + canvas_length1_ * sin(theta1),window_->getSize().y / 2.0 + canvas_length1_ * cos(theta1));
    body2_.setPosition(body1_.getPosition() + sf::Vector2f(canvas_length2_ * sin(theta2),canvas_length2_ * cos(theta2)));

    rod1_.setPosition(window_->getSize().x / 2.0,window_->getSize().y / 2.0);
    rod1_.setRotation(-180.0 * theta1 / M_PI);

    rod2_.setPosition(body1_.getPosition());
    rod2_.setRotation(-180.0 * theta2 / M_PI);

    window_->draw(rod1_);
    window_->draw(rod2_);
    window_->draw(body1_);
    window_->draw(body2_);

}
void DoublePendulum_SimulationDrawer::reset(const double length1,const double length2)
{
    DoublePendulum_Drawer::reset(length1,length2);

    rod1_.setSize(sf::Vector2f(10,canvas_length1_));
    rod1_.setOrigin(rod1_.getSize().x  / 2.0,0);

    rod2_.setSize(sf::Vector2f(10,canvas_length2_));
    rod2_.setOrigin(rod2_.getSize().x / 2.0,0);
}


DoublePendulum_TrajectoryDrawer::DoublePendulum_TrajectoryDrawer(sf::RenderWindow* window):DoublePendulum_Drawer(window)
{
    body1_.setRadius(5);
    body1_.setOrigin(body1_.getRadius(),body1_.getRadius());
    body1_.setFillColor(sf::Color::Red);


    body2_.setRadius(5);
    body2_.setOrigin(body2_.getRadius(),body2_.getRadius());
    body2_.setFillColor(sf::Color::Blue);
}
DoublePendulum_TrajectoryDrawer::~DoublePendulum_TrajectoryDrawer(){}
DrawType DoublePendulum_TrajectoryDrawer::getDrawType() const{return Trajectory;}
void DoublePendulum_TrajectoryDrawer::draw(const double theta1, const double theta2)
{
    body1_.setPosition(window_->getSize().x / 2.0 + canvas_length1_ * sin(theta1),window_->getSize().y / 2.0 + canvas_length1_ * cos(theta1));
    body2_.setPosition(body1_.getPosition() + sf::Vector2f(canvas_length2_ * sin(theta2),canvas_length2_ * cos(theta2)));

    if(trajectory1_.size() > 10) trajectory1_.pop_back();
    trajectory1_.push_front(body1_);

    if(trajectory2_.size() > 1000) trajectory2_.pop_back();
    trajectory2_.push_front(body2_);

    for(std::deque<sf::CircleShape>::iterator it = trajectory1_.begin(); it != trajectory1_.end();it++) window_->draw(*it);
    for(std::deque<sf::CircleShape>::iterator it = trajectory2_.begin(); it != trajectory2_.end();it++) window_->draw(*it);

}
void DoublePendulum_TrajectoryDrawer::reset(const double length1,const double length2)
{
    DoublePendulum_Drawer::reset(length1,length2);
    trajectory1_.clear();
    trajectory2_.clear();
}
}


namespace solver {

//abstract
DoublePendulum_Solver::DoublePendulum_Solver(sf::RenderWindow* window):Solver(window),data_(new simdata::SimulationData(3,3)),drawer_(new draw::DoublePendulum_SimulationDrawer(window))
{
    data_->setLabelText("First body",0,0);
    data_->setLabelText("Second body",0,1);
    data_->show();
}
DoublePendulum_Solver::~DoublePendulum_Solver(){
    delete drawer_;
    data_->close();
    delete data_;
}
void DoublePendulum_Solver::setParameters(const double mass1,const double length1,const double mass2,const double length2,const double theta1,const double theta2)
{
    mass1_ = mass1;
    length1_ = length1;
    mass2_ = mass2;
    length2_ = length2;
    initial_theta1_ = theta1;
    initial_theta2_ = theta2;
}

double DoublePendulum_Solver::Theta1Acc(const double theta1,const double theta2,const double theta1vel,const double theta2vel) const
{
    return (mass2_ * length1_ * theta1vel * theta1vel * sin(theta2 - theta1) * cos(theta2 - theta1) +
            mass2_ * g * sin(theta2) * cos(theta2 - theta1)                                         +
            mass2_ * length2_ * theta2vel * theta2vel * sin(theta2 - theta1)                        -
           (mass1_ + mass2_) * g * sin(theta1))                                                     /
           ((mass1_ + mass2_) * length1_ - mass2_ * length1_ * cos(theta2 - theta1) * cos(theta2 - theta1));
}
double DoublePendulum_Solver::Theta2Acc(const double theta1,const double theta2,const double theta1vel,const double theta2vel) const
{
    return (-mass2_ * length2_ * theta2vel * theta2vel * sin(theta2-theta1) * cos(theta2 - theta1)                                                       +
           (mass1_ + mass2_) * (g * sin(theta1) * cos(theta2 - theta1)  - length1_ * theta1vel * theta1vel * sin (theta2 - theta1)  - g * sin(theta2) )) /
           ((mass1_ + mass2_) * length2_ - mass2_ * length2_ * cos(theta2 - theta1) * cos(theta2 - theta1));
}
void DoublePendulum_Solver::setDrawer(const draw::DrawType draw)
{
    if(draw != drawer_->getDrawType())
    {
        delete drawer_;
        switch(draw)
        {
            case draw::Simulation: drawer_ = new draw::DoublePendulum_SimulationDrawer(window_);break;
            case draw::Trajectory: drawer_ = new draw::DoublePendulum_TrajectoryDrawer(window_);break;
        }
    }
    drawer_->reset(length1_,length2_);
}
//Implicit Euler solver
DoublePendulum_ImplicitEulerSolver::DoublePendulum_ImplicitEulerSolver(sf::RenderWindow* window):DoublePendulum_Solver(window){}
DoublePendulum_ImplicitEulerSolver::~DoublePendulum_ImplicitEulerSolver(){}
void DoublePendulum_ImplicitEulerSolver::draw()
{
    sf::Time time_now = clock_.getElapsedTime();

    double dt = (time_now - told_).asSeconds();

    theta1_ += theta1vel_ * dt;
    theta2_ += theta2vel_ * dt;

    theta1vel_ +=dt * Theta1Acc(theta1_,theta2_,theta1vel_,theta2vel_);

    theta2vel_ +=dt * Theta2Acc(theta1_,theta2_,theta1vel_,theta2vel_);

    drawer_->draw(theta1_,theta2_);

    data_->setLabelText("Θ = " + QString::number(theta1_ / M_PI,'f',3) + " π",1,0);
    data_->setLabelText("Θ = " + QString::number(theta2_ / M_PI,'f',3) + " π",1,1);

    data_->setLabelText("Θ velocity = " + QString::number(theta1vel_ / M_PI,'f',3) + " π / s",2,0);
    data_->setLabelText("Θ velocity = " + QString::number(theta2vel_ / M_PI,'f',3) + " π / s",2,1);

    told_ = time_now;
}
void DoublePendulum_ImplicitEulerSolver::restartSimulation()
{
    told_ = sf::seconds(0);

    theta1_ = initial_theta1_;
    theta2_ = initial_theta2_;

    theta1vel_ = Theta1Acc(theta1_,theta2_,0,0);
    theta2vel_ = Theta2Acc(theta1_,theta2_,0,0);

    drawer_->reset(length1_,length2_);

    clock_.restart();
}
DiffEqSolver DoublePendulum_ImplicitEulerSolver::getSolverType() const
{
    return IMPLICIT_EULER;
}


// RK4 Solver

DoublePendulum_RK4Solver::DoublePendulum_RK4Solver(sf::RenderWindow* window):DoublePendulum_Solver(window){}
DoublePendulum_RK4Solver::~DoublePendulum_RK4Solver(){}


void DoublePendulum_RK4Solver::restartSimulation()
{
    told_ = sf::seconds(0);

    theta1_ = initial_theta1_;
    theta2_ = initial_theta2_;

    theta1vel_ = Theta1Acc(theta1_,theta2_,0,0);
    theta2vel_ = Theta2Acc(theta1_,theta2_,0,0);

    drawer_->reset(length1_,length2_);

    clock_.restart();
}

void DoublePendulum_RK4Solver::draw()
{
    sf::Time time_now = clock_.getElapsedTime();
    double dt = (time_now - told_).asSeconds();
    double theta1vel_tmp = theta1vel_,theta2vel_tmp = theta2vel_;


    //1st step
    double k11 = Theta1Acc(theta1_,theta2_,theta1vel_,theta2vel_);
    double k12 = Theta2Acc(theta1_,theta2_,theta1vel_,theta2vel_);

    //2nd step

    theta1_ += theta1vel_ * dt / 2.0;
    theta2_ += theta2vel_ * dt / 2.0;

    theta1vel_ += k11 * dt / 2.0;
    theta2vel_ += k12 * dt / 2.0;

    double k21 = Theta1Acc(theta1_,theta2_,theta1vel_tmp + dt * k11 / 2.0,theta2vel_);
    double k22 = Theta2Acc(theta1_,theta2_,theta1vel_,theta2vel_tmp + dt * k12 / 2.0);

    //3rd step
    double k31 = Theta1Acc(theta1_,theta2_,theta1vel_tmp + dt * k21 / 2.0,theta2vel_);
    double k32 = Theta2Acc(theta1_,theta2_,theta1vel_,theta2vel_tmp + dt * k22 / 2.0);

    //4th step

    theta1_ += theta1vel_ * dt / 2.0;
    theta2_ += theta2vel_ * dt / 2.0;

    theta1vel_ += k11 * dt / 2.0;
    theta2vel_ += k12 * dt / 2.0;

    double k41 = Theta1Acc(theta1_,theta2_,theta1vel_tmp + dt * k31,theta2vel_);
    double k42 = Theta2Acc(theta1_,theta2_,theta1vel_,theta2vel_tmp + dt * k32);


    theta1vel_ = theta1vel_tmp + dt * (k11 + 2.0 * k21 + 2.0 * k31 + k41) / 6.0;
    theta2vel_ = theta2vel_tmp +  dt * (k12 + 2.0 * k22 + 2.0 * k32 + k42) / 6.0;

    drawer_->draw(theta1_,theta2_);
    data_->setLabelText("Θ = " + QString::number(theta1_ / M_PI,'f',3) + " π",1,0);
    data_->setLabelText("Θ = " + QString::number(theta2_ / M_PI,'f',3) + " π",1,1);

    data_->setLabelText("Θ velocity = " + QString::number(theta1vel_ / M_PI,'f',3) + " π",2,0);
    data_->setLabelText("Θ velocity = " + QString::number(theta2vel_ / M_PI,'f',3) + " π / s",2,1);

    told_ = time_now;

}

DiffEqSolver DoublePendulum_RK4Solver::getSolverType() const{return RK4;}


}
