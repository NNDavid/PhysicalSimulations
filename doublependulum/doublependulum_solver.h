#ifndef DOUBLEPENDULUM_SOLVER_H
#define DOUBLEPENDULUM_SOLVER_H
#include "solver.h"
#include "drawer.h"
#include "simulationdata.h"
#include <climits>
#include <queue>
#include <SFML/Graphics.hpp>
namespace draw {

struct DoublePendulum_DrawData
{
  double theta1;
  double theta2;
  DoublePendulum_DrawData(const double th1 = 0,const double th2 = 0):theta1(th1),theta2(th2){}
};

class DoublePendulum_Drawer:public Drawer<DoublePendulum_DrawData>
{
public:
    DoublePendulum_Drawer(sf::RenderWindow* window);
    virtual ~DoublePendulum_Drawer();
    virtual DrawType getDrawType() const override = 0;
    virtual void draw(const DoublePendulum_DrawData& data) override = 0;
    virtual void reset(const double length1,const double length2);

protected:
    sf::CircleShape body1_;
    sf::CircleShape body2_;
    double canvas_length1_;
    double canvas_length2_;


};


class DoublePendulum_SimulationDrawer:public DoublePendulum_Drawer
{
public:
    DoublePendulum_SimulationDrawer(sf::RenderWindow* window);
    ~DoublePendulum_SimulationDrawer();
    DrawType getDrawType() const override;
    void draw(const DoublePendulum_DrawData& data) override;
    void reset(const double length1,const double length2) override;

private:
    sf::RectangleShape rod1_;
    sf::RectangleShape rod2_;

};


class DoublePendulum_TrajectoryDrawer:public DoublePendulum_Drawer
{
public:
    DoublePendulum_TrajectoryDrawer(sf::RenderWindow* window);
    ~DoublePendulum_TrajectoryDrawer();
    DrawType getDrawType() const override;
    void draw(const DoublePendulum_DrawData& data) override;
    void reset(const double length1,const double length2) override;
private:
    std::deque<sf::CircleShape> trajectory1_;
    std::deque<sf::CircleShape> trajectory2_;

};

}




namespace solver {

class DoublePendulum_Solver:public Solver<draw::DoublePendulum_Drawer>
{
public:
    DoublePendulum_Solver(sf::RenderWindow* window,const int rows = 3,const int cols = 3);
    virtual ~DoublePendulum_Solver();
    virtual void draw() override = 0;
    virtual void restartSimulation() override = 0;
    virtual DiffEqSolver getSolverType() const override = 0;
    void setParameters(const double mass1,const double length1,const double mass2,const double length2,const double theta1,const double theta2);
    void setDrawer(const draw::DrawType draw);

protected:
    double mass1_;
    double length1_;
    double mass2_;
    double length2_;
    double initial_theta1_;
    double initial_theta2_;
    double theta1_;
    double theta2_;
    double theta1vel_;
    double theta2vel_;
    const double g = 9.81;
    double Theta1Acc(const double theta1,const double theta2,const double theta1vel,const double theta2vel) const;
    double Theta2Acc(const double theta1,const double theta2,const double theta1vel,const double theta2vel) const;
};



class DoublePendulum_ImplicitEulerSolver:public DoublePendulum_Solver
{
public:
    DoublePendulum_ImplicitEulerSolver(sf::RenderWindow* window);
    ~DoublePendulum_ImplicitEulerSolver();
    void draw() override;
    void restartSimulation() override;
    DiffEqSolver getSolverType() const override;

};


class DoublePendulum_RK4Solver:public DoublePendulum_Solver
{
public:
    DoublePendulum_RK4Solver(sf::RenderWindow* window);
    ~DoublePendulum_RK4Solver();
    void draw() override;
    void restartSimulation() override;
    DiffEqSolver getSolverType() const override;

};
}

#endif // DOUBLEPENDULUM_SOLVER_H
