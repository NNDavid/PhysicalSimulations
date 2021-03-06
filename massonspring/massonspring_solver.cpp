#include "massonspring_solver.h"
#include <QMessageBox>
#include <math.h>
#include <iostream>
namespace draw
{
MassOnSpring_Drawer::MassOnSpring_Drawer(sf::RenderWindow* window):Drawer(window){}
MassOnSpring_Drawer::~MassOnSpring_Drawer(){}


MassOnSpring_SimulationDrawer::MassOnSpring_SimulationDrawer(sf::RenderWindow* window):MassOnSpring_Drawer(window),spring_(sf::Vector2f(0,0),sf::Vector2f(0,0),5,50)
{
    body_.setFillColor(sf::Color::Red);
    body_.setRadius(50);
    body_.setOrigin(body_.getRadius(),body_.getRadius());
}
MassOnSpring_SimulationDrawer::~MassOnSpring_SimulationDrawer(){}
void MassOnSpring_SimulationDrawer::draw(const MassOnSpring_DrawData& data)
{
    Drawer::draw(data);
    if(msgbox == nullptr && draw_data.theta != draw_data.theta)
    {
        msgbox = new QMessageBox(QMessageBox::Icon::Critical,"Simulation has crashed","We are sorry to inform you that the differential equation solver has crashed!",QMessageBox::Button::Yes);
        msgbox->show();
    }
    double canvas_x = (draw_data.x * window_->getSize().y / 2.0) / draw_data.l;
    sf::Vector2f position(window_->getSize().x / 2.0 + (canvas_x + window_->getSize().y / 2.0) * sin(draw_data.theta) ,(canvas_x + window_->getSize().y / 2.0) * cos(draw_data.theta));
    body_.setPosition(position);
    spring_.draw(window_,sf::Vector2f(window_->getSize().x / 2.0,0),position);
    window_->draw(body_);
}
DrawType MassOnSpring_SimulationDrawer::getDrawType() const{return Simulation;}


MassOnSpring_TrajectoryDrawer::MassOnSpring_TrajectoryDrawer(sf::RenderWindow* window):MassOnSpring_Drawer(window)
{
    body_.setFillColor(sf::Color::Red);
    body_.setRadius(5);
    body_.setOrigin(body_.getRadius(),body_.getRadius());
}
MassOnSpring_TrajectoryDrawer::~MassOnSpring_TrajectoryDrawer(){}
void MassOnSpring_TrajectoryDrawer::draw(const MassOnSpring_DrawData& data)
{
    Drawer::draw(data);
    if(msgbox == nullptr && draw_data.theta != draw_data.theta)
    {
        msgbox = new QMessageBox(QMessageBox::Icon::Critical,"Simulation has crashed","We are sorry to inform you that the differential equation solver has crashed!",QMessageBox::Button::Yes);
        msgbox->show();
    }
    double canvas_x = (draw_data.x * window_->getSize().y / 2.0) / draw_data.l;
    sf::Vector2f position(window_->getSize().x / 2.0 + (canvas_x + window_->getSize().y / 2.0) * sin(draw_data.theta) ,(canvas_x + window_->getSize().y / 2.0) * cos(draw_data.theta));
    body_.setPosition(position);

    if(trajectory_.size() > 500) trajectory_.pop_back();
    trajectory_.push_front(body_);

    for(std::deque<sf::CircleShape>::iterator it = trajectory_.begin();it != trajectory_.end();it++) window_->draw(*it);

}
DrawType MassOnSpring_TrajectoryDrawer::getDrawType() const{return Trajectory;}
}




namespace solver {


//Abstract

MassOnSpring_Solver::MassOnSpring_Solver(sf::RenderWindow* window,const int rows, const int cols):Solver(window,new draw::MassOnSpring_SimulationDrawer(window),rows, cols)
{
    data_->setLabelText("Body data",0,0);
    data_->show();
}
MassOnSpring_Solver::~MassOnSpring_Solver()
{
}

void MassOnSpring_Solver::setParameters(const double mass, const double elastic_constant, const double theta_initial,const double l,const double x)
{
    mass_ = mass;
    elastic_constant_ = elastic_constant;
    theta_initial_ = theta_initial;
    l_ = l;
    x_initial_ = x;
}

double MassOnSpring_Solver::ThetaAcc(const double x,const double vel,const double theta,const double theta_vel)
{
    return -(g * sin(theta) + 2.0 * vel * theta_vel) / (l_ + x);
}


double MassOnSpring_Solver::XAcc(const double x,const double theta,const double theta_vel)
{
    return (l_ + x) * theta_vel * theta_vel + g * cos(theta) - (elastic_constant_ / mass_) * x;
}

void MassOnSpring_Solver::setDrawer(const draw::DrawType draw)
{
    if(draw != drawer_->getDrawType())
    {
        switch(draw)
        {
            case draw::Simulation: drawer_ = new draw::MassOnSpring_SimulationDrawer(window_);break;
            case draw::Trajectory: drawer_ = new draw::MassOnSpring_TrajectoryDrawer(window_);break;
        }
    }
}

MassOnSpring_ModifiedEulerSolver::MassOnSpring_ModifiedEulerSolver(sf::RenderWindow* window):MassOnSpring_Solver(window){}

MassOnSpring_ModifiedEulerSolver::~MassOnSpring_ModifiedEulerSolver(){}

void  MassOnSpring_ModifiedEulerSolver::restartSimulation()
{
        told_ = sf::seconds(0);

        theta_ = theta_initial_;
        thetavel_ = 0;

        x_ = x_initial_;
        xvel_ = 0;
        data_->raise();
        clock_.restart();

}
void  MassOnSpring_ModifiedEulerSolver::draw()
{

     double xvel_tmp = xvel_;
        double thetavel_tmp = thetavel_;
        sf::Time time_now = clock_.getElapsedTime();

        double dt = (time_now - told_).asSeconds();

        double k1theta = ThetaAcc(x_,xvel_,theta_,thetavel_);

        theta_ += dt * thetavel_tmp / 2.0;
        x_ += dt * xvel_tmp / 2.0;

        double k2theta = ThetaAcc(x_,xvel_,theta_,thetavel_ + dt * k1theta / 2.0);

        thetavel_ += dt * k2theta / 2.0;

        xvel_ += dt * XAcc(x_,theta_,thetavel_);

        thetavel_ += dt * k2theta / 2.0;
        theta_ += dt * thetavel_tmp / 2.0;
        x_ += dt * xvel_tmp / 2.0;

        drawer_->draw(draw::MassOnSpring_DrawData(theta_,x_,l_));

        data_->setLabelText("Θ  = " + QString::number(theta_ / M_PI,'f',3) + " π",1,0);
        data_->setLabelText("Θ velocity = " + QString::number(thetavel_ / M_PI,'f',3) + " π / s",2,0);
        data_->setLabelText("x  = " + QString::number(x_,'f',3) + " m",3,0);
        data_->setLabelText("x velocity = " + QString::number(xvel_,'f',3) + " m / s",4,0);

        told_ = time_now;
}
DiffEqSolver MassOnSpring_ModifiedEulerSolver::getSolverType() const {return MODIFIED_EULER;}


}

