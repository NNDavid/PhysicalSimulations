#ifndef OSCILLATINGSUPPORTPENDULUM_SOLVER_H
#define OSCILLATINGSUPPORTPENDULUM_SOLVER_H
#include "solver.h"
#include "drawer.h"
#include "simulationdata.h"
#include <deque>
namespace draw{

 class OscillatingSupportPendulum_Drawer:public Drawer
 {
   public:
     OscillatingSupportPendulum_Drawer(sf::RenderWindow* window);
     virtual ~OscillatingSupportPendulum_Drawer(){window_->clear(sf::Color::Black);}
     virtual void draw(const double support_position, const double theta) = 0;
     virtual DrawType getDrawType() const override = 0;
     virtual void reset() = 0;

    protected:
     sf::CircleShape body_;

 };

 class OscillatingSupportPendulum_SimulationDrawer: public OscillatingSupportPendulum_Drawer
 {
 public:

     OscillatingSupportPendulum_SimulationDrawer(sf::RenderWindow* window);
     ~OscillatingSupportPendulum_SimulationDrawer(){}
     void draw(const double support_position, const double theta) override;
     DrawType getDrawType() const override;
     void reset() override;
 private:
     sf::RectangleShape support_;
     sf::RectangleShape rod_;



 };

 class OscillatingSupportPendulum_TrajectoryDrawer: public OscillatingSupportPendulum_Drawer
 {
 public:

     OscillatingSupportPendulum_TrajectoryDrawer(sf::RenderWindow* window);
     ~OscillatingSupportPendulum_TrajectoryDrawer(){}
     void draw(const double support_position, const double theta) override;
     DrawType getDrawType() const override;
     void reset() override;
 private:
     sf::RectangleShape support_;
     sf::RectangleShape rod_;
     bool first;
          std::deque<sf::CircleShape> trajectory;


 };
}

namespace solver {

class OscillatingSupportPendulum_Solver:public Solver
{
public:
    OscillatingSupportPendulum_Solver(sf::RenderWindow* window);
    virtual ~OscillatingSupportPendulum_Solver();
    virtual void draw() override = 0;
    virtual void restartSimulation() override = 0;
    virtual DiffEqSolver getSolverType() const override = 0;
    void setParameters(const double length,const double amplitude,const double period,const double theta_initial);
    void setDrawer(const draw::DrawType draw);
protected:
    simdata::SimulationData* data_;
    draw::OscillatingSupportPendulum_Drawer* drawer_;
    double length_;
    double amplitude_;
    double period_;
    double omega_;
    double theta_initial_;
    double theta_;
    double thetavel_;
    double thetaacc_;
    const double g = 9.81;
    double getSupportAcceleration(const double time);
    double getBodyAcceleration(const double theta,const double support_acceleration);
    double getBodyCanvasPosition(const double time);
    double getSupportPosition(const double time);

};

class OscillatingSupportPendulum_ImplicitEulerSolver:public OscillatingSupportPendulum_Solver
{
public:
   OscillatingSupportPendulum_ImplicitEulerSolver(sf::RenderWindow* window);
    virtual ~OscillatingSupportPendulum_ImplicitEulerSolver();
    void draw() override;
    void restartSimulation() override;
    DiffEqSolver getSolverType() const override;
private:
    const double h = 0.001;


};

}

#endif // OSCILLATINGSUPPORTPENDULUM_SOLVER_H
