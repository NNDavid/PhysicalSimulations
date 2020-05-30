#ifndef QSFML_MASSONSPRING_H
#define QSFML_MASSONSPRING_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QVBoxLayout>
#include <cmath>
#include "qsfmlcanvas.h"
#include <iostream>
#include "massonspring_solver.h"


class QSFML_MassOnSpring:public QSFML_Canvas
{
    Q_OBJECT
public:
    QSFML_MassOnSpring(QWidget* parent, const QPoint& position, const QSize& size);
    void setDiffEqSolver(const solver::DiffEqSolver diff);
    void stopSimulation();
    void startSimulation(const double mass, const double elastic_constant, const double theta_initial,const double l,const double x);
    void changeDraw(const bool is_checked);

 private:
     void onInit() override;
     void onUpdate() override;
     solver::DiffEqSolver diff_;
     solver::MassOnSpring_Solver* solver_;
     bool pause_;
};
#endif // QSFML_MASSONSPRING_H
