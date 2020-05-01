#ifndef DOUBLEPENDULUM_H
#define DOUBLEPENDULUM_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include "qsfml_doublependulum.h"
namespace doublependulum {


class DoublePendulum : public QWidget
{
    Q_OBJECT
public:
    explicit DoublePendulum(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent*) override;

signals:
    void widgetClosed();


private slots:
    void startSimulation();
    void restartSimulation();
    void DiffEqSolverChanged();
    void drawChanged();

private:
   QVBoxLayout* mainLayout_;
   QHBoxLayout* commandLayout_;
   QGridLayout* gridLayout_;
   QGridLayout* solverSwapLayout_;

   QDoubleSpinBox* mass1SpinBox_;
   QLabel* mass1Label_;
   QLabel* kg1Label_;



   QDoubleSpinBox* length1SpinBox_;
   QLabel* length1Label_;
   QLabel* m1Label_;


   QDoubleSpinBox* mass2SpinBox_;
   QLabel* mass2Label_;
   QLabel* kg2Label_;


   QDoubleSpinBox* length2SpinBox_;
   QLabel* length2Label_;
   QLabel* m2Label_;

   QDoubleSpinBox* theta1SpinBox_;
   QLabel* theta1Label_;
   QLabel* pi1Label_;

   QDoubleSpinBox* theta2SpinBox_;
   QLabel* theta2Label_;
   QLabel* pi2Label_;


   QPushButton* startSimulation_;
   QPushButton* restartSimulation_;

   QRadioButton* RK4_Solver;
   QRadioButton* ImplicitEuler_Solver;

   QCheckBox* trajectoryDraw_;
   QSFML_DoublePendulum* canvas_;




};
}

#endif // DOUBLEPENDULUM_H
