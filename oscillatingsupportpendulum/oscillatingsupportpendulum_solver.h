#ifndef OSCILLATINGSUPPORTPENDULUM_SOLVER_H
#define OSCILLATINGSUPPORTPENDULUM_SOLVER_H
#include "solver.h"
#include "drawer.h"
#include "simulationdata.h"
#include <deque>
#include <climits>
namespace draw{

struct OscillatingSupportPendulum_DrawData{
    double support_position;
    double theta;
    OscillatingSupportPendulum_DrawData(const double sup_pos = std::numeric_limits<double>::max(),const double th = 0):support_position(sup_pos),theta(th){}


};

 class OscillatingSupportPendulum_Drawer:public Drawer<OscillatingSupportPendulum_DrawData>
 {
   public:
     OscillatingSupportPendulum_Drawer(sf::RenderWindow* window);
     virtual ~OscillatingSupportPendulum_Drawer(){}
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
     void draw(const OscillatingSupportPendulum_DrawData& data) override;
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
     void draw(const OscillatingSupportPendulum_DrawData& data) override;
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

class OscillatingSupportPendulum_Solver:public Solver<draw::OscillatingSupportPendulum_Drawer>
{
public:
    OscillatingSupportPendulum_Solver(sf::RenderWindow* window,const int rows = 3, const int cols = 2);
    virtual ~OscillatingSupportPendulum_Solver();
    virtual void restartSimulation() override = 0;
    virtual DiffEqSolver getSolverType() const override = 0;
    void setParameters(const double length,const double amplitude,const double period,const double theta_initial);
    void setDrawer(const draw::DrawType draw);
protected:
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
};

}

#endif // OSCILLATINGSUPPORTPENDULUM_SOLVER_H
