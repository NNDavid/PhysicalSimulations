#ifndef SOLVER_H
#define SOLVER_H

#include <SFML/Graphics.hpp>
#include "simulationdata.h"
#include "drawer.h"

namespace solver {
enum DiffEqSolver{EXACT,EULER,COMPARE_EULER,IMPLICIT_EULER,MODIFIED_EULER,RK4};


template<class Drawer>
    class Solver
    {
    public:
        Solver(sf::RenderWindow* window,Drawer* d,const int rows, const int cols):
            window_(window), drawer_(d), data_(new simdata::SimulationData(rows,cols)) {data_->show();}
        virtual ~Solver()
        {
            data_->close();
            delete data_;
        }
        virtual void draw() = 0;
        virtual void restartSimulation() = 0;
        virtual DiffEqSolver getSolverType() const = 0;
        virtual void pause()
        {
            drawer_->pause();
            data_->pause();
        }
        virtual void unpause()
        {
            drawer_->unpause();
            data_->unpause();
        }
    protected:
        sf::RenderWindow* window_;
        sf::Time told_;
        sf::Clock clock_;
        Drawer* drawer_;
        simdata::SimulationData* data_;
};
}

#endif // SOLVER_H
