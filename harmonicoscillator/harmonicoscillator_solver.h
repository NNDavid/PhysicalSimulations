#ifndef HARMONICOSCILLATOR_SOLVER_H
#define HARMONICOSCILLATOR_SOLVER_H

#include "solver.h"
#include "spring.h"
#include "simulationdata.h"
#include "drawer.h"


namespace draw {

class HarmonicOscillator_SimulationDrawer:public Drawer<double>
{

   public:
         HarmonicOscillator_SimulationDrawer(sf::RenderWindow* window);
        virtual ~HarmonicOscillator_SimulationDrawer();
        virtual void draw(const double& data) override;
        virtual DrawType getDrawType() const override;

       protected:
        sf::CircleShape body_;
        Spring spring_;

};


class HarmonicOscillator_CompareSimulationDrawer:public Drawer<std::pair<double,double>>
{

   public:
         HarmonicOscillator_CompareSimulationDrawer(sf::RenderWindow* window);
        virtual ~HarmonicOscillator_CompareSimulationDrawer();
        virtual void draw(const std::pair<double,double>& data) override;
        virtual DrawType getDrawType() const override;

       protected:
        sf::CircleShape body1_;
        sf::CircleShape body2_;
        Spring spring1_;
        Spring spring2_;

};

}
namespace solver {

class HarmonicOscillator_Solver:public Solver<draw::HarmonicOscillator_SimulationDrawer>
{
public:
    HarmonicOscillator_Solver(sf::RenderWindow* window, const int rows = 3, const int cols = 1);
    virtual ~HarmonicOscillator_Solver();
    virtual void draw() override = 0;
    virtual void restartSimulation() override = 0;
    virtual DiffEqSolver getSolverType() const override = 0;
    void setParameters(const double mass, const double elastic_constant,const double amplitude);

protected:
    double mass_;
    double elastic_constant_;
    double amplitude_;
    double x_;
    double v_;
};


class HarmonicOscillator_ExactSolver:public HarmonicOscillator_Solver
{
public:
    HarmonicOscillator_ExactSolver(sf::RenderWindow* window);
    ~HarmonicOscillator_ExactSolver();
    void draw() override;
    void restartSimulation() override;
    DiffEqSolver getSolverType() const override;

private:
    double circular_frequency_;
};


class HarmonicOscillator_EulerSolver:public HarmonicOscillator_Solver
{
public:
    HarmonicOscillator_EulerSolver(sf::RenderWindow* window);
    ~HarmonicOscillator_EulerSolver();
    void draw() override;
    void restartSimulation() override;
    DiffEqSolver getSolverType() const override;
private:
    double xold_;
    double vold_;

};

class HarmonicOscillator_CompareEulerSolver:public HarmonicOscillator_Solver
{
public:
    HarmonicOscillator_CompareEulerSolver(sf::RenderWindow* window,int rows=5, int cols=5);
    ~HarmonicOscillator_CompareEulerSolver();
    void draw() override;
    void restartSimulation() override;
    DiffEqSolver getSolverType() const override;
    void pause() override;
    void unpause() override;
private:
    double xold_;
    double vold_;
    double circular_frequency_;
    draw::HarmonicOscillator_CompareSimulationDrawer* drawernew_;

};


}

#endif // HARMONICOSCILLATOR_SOLVER_H
