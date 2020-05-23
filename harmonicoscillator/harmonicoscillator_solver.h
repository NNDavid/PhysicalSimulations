#ifndef HARMONICOSCILLATOR_SOLVER_H
#define HARMONICOSCILLATOR_SOLVER_H

#include "solver.h"
#include "spring.h"
#include "simulationdata.h"

namespace solver {

class HarmonicOscillator_Solver:public Solver
{
public:
    HarmonicOscillator_Solver(sf::RenderWindow* window);
    virtual ~HarmonicOscillator_Solver();
    virtual void draw() override = 0;
    virtual void restartSimulation() override = 0;
    virtual DiffEqSolver getSolverType() const override = 0;
    void setParameters(const double mass, const double elastic_constant,const double amplitude);

protected:
    simdata::SimulationData* data_;
    sf::CircleShape body_;
    Spring spring_;
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
    const double h_ = 0.00001;

};



}

#endif // HARMONICOSCILLATOR_SOLVER_H
