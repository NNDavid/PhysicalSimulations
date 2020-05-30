#ifndef QSFML_HARMONICOSCILLATION_H
#define QSFML_HARMONICOSCILLATION_H

#include "qsfmlcanvas.h"
#include "harmonicoscillator_solver.h"
#include <SFML/Graphics.hpp>
#include <QLabel>
#include <QVBoxLayout>
#include <math.h>
#include <iomanip>
#include <iostream>
namespace harmonicoscillation  {


class QSFML_HarmonicOscillation: public QSFML_Canvas
{
   Q_OBJECT
public:
   QSFML_HarmonicOscillation(QWidget* parent, const QPoint& position, const QSize& size);
   ~QSFML_HarmonicOscillation();
   void setDiffEqSolver(const solver::DiffEqSolver diff);
   void stopSimulation();
   void startSimulation(const double mass, const double elastic_constant, const double amplitude);

private:
    void onInit() override;
    void onUpdate() override;
    solver::DiffEqSolver diff_;
    solver::HarmonicOscillator_Solver* solver_;
};
}

#endif // QSFML_HARMONICOSCILLATION_H
