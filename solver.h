#ifndef SOLVER_H
#define SOLVER_H

#include <SFML/Graphics.hpp>

namespace solver {
enum DiffEqSolver{EXACT,EULER,IMPLICIT_EULER,MODIFIED_EULER,RK4};
    class Solver
    {
    public:
        Solver(sf::RenderWindow* window);
        virtual ~Solver();
        virtual void draw() = 0;
        virtual void restartSimulation() = 0;
        virtual DiffEqSolver getSolverType() const = 0;

    protected:
        sf::RenderWindow* window_;
        sf::Time told_;
        sf::Clock clock_;

};
}

#endif // SOLVER_H
