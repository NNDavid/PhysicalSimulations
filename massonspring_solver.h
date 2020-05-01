#ifndef MASSONSPRING_SOLVER_H
#define MASSONSPRING_SOLVER_H
#include "solver.h"
#include "drawer.h"
#include "spring.h"
#include <queue>
#include <math.h>

namespace draw {
class  MassOnSpring_Drawer:public Drawer
{
  public:
     MassOnSpring_Drawer(sf::RenderWindow* window);
    virtual ~MassOnSpring_Drawer();
    virtual void draw(const double theta, const double x,const double l) = 0;
    virtual DrawType getDrawType() const override = 0;

   protected:
    sf::CircleShape body_;

};

class  MassOnSpring_SimulationDrawer: public  MassOnSpring_Drawer
{
public:

     MassOnSpring_SimulationDrawer(sf::RenderWindow* window);
    ~MassOnSpring_SimulationDrawer();
    void draw(const double theta, const double x,const double l) override;
    DrawType getDrawType() const override;
private:
    Spring spring_;

};

class  MassOnSpring_TrajectoryDrawer: public MassOnSpring_Drawer
{
public:

     MassOnSpring_TrajectoryDrawer(sf::RenderWindow* window);
    ~ MassOnSpring_TrajectoryDrawer();
    void draw(const double theta, const double x,const double l) override;
    DrawType getDrawType() const override;
private:
   std::deque<sf::CircleShape> trajectory_;


};
}




namespace solver {

class MassOnSpring_Solver:public Solver
{
public:
    MassOnSpring_Solver(sf::RenderWindow* window);
    virtual ~MassOnSpring_Solver();
    virtual void draw() = 0;
    void setParameters(const double mass, const double elastic_constant, const double theta_initial,const double l,const double x);
    virtual DiffEqSolver getSolverType() const = 0;
    void setDrawer(const draw::DrawType draw);

    protected:
    draw::MassOnSpring_Drawer* drawer_;
    double mass_;
    double elastic_constant_;
    double theta_initial_;
    double x_initial_;
    double l_;
    sf::CircleShape body_;
    sf::Time told_;
    sf::Clock clock_;
    const double g = 9.81;
    double ThetaAcc(const double x,const double vel,const double theta,const double theta_vel);
    double XAcc(const double x,const double theta,const double theta_vel);
};


class MassOnSpring_ModifiedEulerSolver:public MassOnSpring_Solver
{
public:
    MassOnSpring_ModifiedEulerSolver(sf::RenderWindow* window);
    ~MassOnSpring_ModifiedEulerSolver();
    void restartSimulation() override;
    void draw() override;
    DiffEqSolver getSolverType() const override;

private:
    double theta_;
    double thetavel_;
    double x_;
    double xvel_;



};


}

#endif // MASSONSPRING_SOLVER_H
