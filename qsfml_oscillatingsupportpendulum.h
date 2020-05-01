#ifndef QSFML_OSCILLATINGSUPPORTPENDULUM_H
#define QSFML_OSCILLATINGSUPPORTPENDULUM_H
#include "qsfmlcanvas.h"
#include "oscillatingsupportpendulum_solver.h"
#include <QObject>
#include <QWidget>
#include <cmath>
#include <iostream>
#include <tgmath.h>

namespace oscillatingsupportpendulum{

class QSFML_OscillatingSupportPendulum:public QSFML_Canvas
{
    Q_OBJECT
public:
    QSFML_OscillatingSupportPendulum(QWidget* parent, const QPoint& position, const QSize& size);
    ~QSFML_OscillatingSupportPendulum(){delete solver_;}
    void setDiffEqSolver(const solver::DiffEqSolver diff);
    void restartSimulation();
    void startSimulation( const double length, const double amplitude,const double period,const double initialTheta);
    void changeDraw(const bool is_checked);
 private:
     void onInit() override;
     void onUpdate() override;
     solver::OscillatingSupportPendulum_Solver* solver_;
     solver::DiffEqSolver diff_;
     bool pause_;
};


}


#endif // QSFML_OSCILLATINGSUPPORTPENDULUM_H
