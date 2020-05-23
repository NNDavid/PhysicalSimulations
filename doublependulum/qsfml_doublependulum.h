#ifndef QSFML_DOUBLEPENDULUM_H
#define QSFML_DOUBLEPENDULUM_H
#include "qsfmlcanvas.h"
#include "doublependulum_solver.h"
#include "solver.h"
namespace doublependulum {


class QSFML_DoublePendulum: public QSFML_Canvas
{
    Q_OBJECT
public:
    QSFML_DoublePendulum(QWidget* parent, const QPoint& position, const QSize& size);
    ~QSFML_DoublePendulum();
    void setDiffEqSolver(const solver::DiffEqSolver diff);
    void stopSimulation();
    void startSimulation(const double mass1,const double length1,const double mass2,const double length2,const double theta1, const double theta2);
    void changeDraw(const bool is_checked);

 private:
     void onInit() override;
     void onUpdate() override;
     solver::DoublePendulum_Solver* solver_;
     solver::DiffEqSolver diff_;
     bool pause_;
};
}

#endif // QSFML_DOUBLEPENDULUM_H
