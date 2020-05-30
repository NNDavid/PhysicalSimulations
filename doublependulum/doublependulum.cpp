

#include "doublependulum.h"
#include <cmath>
namespace doublependulum {


DoublePendulum::DoublePendulum(QWidget *parent) :
    QWidget(parent),
    mainLayout_(new QVBoxLayout(this)),
    commandLayout_(new QHBoxLayout(this)),
    gridLayout_(new QGridLayout(this)),
    solverSwapLayout_(new QGridLayout(this)),
    mass1SpinBox_(new QDoubleSpinBox(this)),
    mass1Label_(new QLabel(this)),
    kg1Label_(new QLabel(this)),
    length1SpinBox_(new QDoubleSpinBox(this)),
    length1Label_(new QLabel(this)),
    m1Label_(new QLabel(this)),
    mass2SpinBox_(new QDoubleSpinBox(this)),
    mass2Label_(new QLabel(this)),
    kg2Label_(new QLabel(this)),
    length2SpinBox_(new QDoubleSpinBox(this)),
    length2Label_(new QLabel(this)),
    m2Label_(new QLabel(this)),
    theta1SpinBox_(new QDoubleSpinBox(this)),
    theta1Label_(new QLabel(this)),
    pi1Label_(new QLabel(this)),
    theta2SpinBox_(new QDoubleSpinBox(this)),
    theta2Label_(new QLabel(this)),
    pi2Label_(new QLabel(this)),
    startSimulation_(new QPushButton(this)),
    stopSimulation_(new QPushButton(this)),
    RK4_Solver(new QRadioButton(this)),
    ImplicitEuler_Solver(new QRadioButton(this)),
    trajectoryDraw_(new QCheckBox(this)),
    canvas_(new QSFML_DoublePendulum(this, QPoint(20, 20), QSize(360, 360)))
{
    startSimulation_->setText("Start simulation");
    stopSimulation_->setText("Stop simulation");
    mass1SpinBox_->setRange(0.1,10.0);
    mass1SpinBox_->setSingleStep(0.5);
    mass1SpinBox_->setValue(5.0);

    mass1Label_->setText("m1 = ");

    kg1Label_->setText("kg");

    length1SpinBox_->setRange(0.1,10);
    length1SpinBox_->setSingleStep(0.1);
    length1SpinBox_->setValue(5.0);

    length1Label_->setText("l1 = ");

    m1Label_->setText("m");

    mass2SpinBox_->setRange(0.1,10.0);
    mass2SpinBox_->setSingleStep(0.5);
    mass2SpinBox_->setValue(5.0);

    mass2Label_->setText("m2 = ");

    kg2Label_->setText("kg");

    length2SpinBox_->setRange(0.1,10);
    length2SpinBox_->setSingleStep(0.1);
    length2SpinBox_->setValue(5.0);

    length2Label_->setText("l2 = ");

    m2Label_->setText("m");

    theta1SpinBox_->setRange(-1,1);
    theta1SpinBox_->setValue(0);

    theta1Label_ -> setText("Θ1 = ");

    pi1Label_ ->setText("π");

    theta2SpinBox_->setRange(-1,1);
    theta2SpinBox_->setValue(0);

    theta2Label_ -> setText("Θ2 = ");

    pi2Label_ ->setText("π");

    RK4_Solver->setText("Runge Kutta 4th order");
    RK4_Solver->setChecked(true);
    connect(RK4_Solver,SIGNAL(clicked()),this,SLOT(DiffEqSolverChanged()));

    ImplicitEuler_Solver->setText("Implicit Euler");
    connect(ImplicitEuler_Solver,SIGNAL(clicked()),this,SLOT(DiffEqSolverChanged()));

    trajectoryDraw_->setText("Draw trajectory");
    trajectoryDraw_->setChecked(false);
    connect(trajectoryDraw_,SIGNAL(clicked()),this,SLOT(drawChanged()));

    connect(startSimulation_,SIGNAL(clicked()),this,SLOT(startSimulation()));
    connect(stopSimulation_,SIGNAL(clicked()),this,SLOT(stopSimulation()));


    connect(RK4_Solver,SIGNAL(clicked()),this,SLOT(DiffEqSolverChanged()));

    gridLayout_->addWidget(mass1Label_,0,0);
    gridLayout_->addWidget(mass1SpinBox_,0,1);
    gridLayout_->addWidget(kg1Label_,0,2);

    gridLayout_->addWidget(length1Label_,1,0);
    gridLayout_->addWidget(length1SpinBox_,1,1);
    gridLayout_->addWidget(m1Label_,1,2);


    gridLayout_->addWidget(mass2Label_,2,0);
    gridLayout_->addWidget(mass2SpinBox_,2,1);
    gridLayout_->addWidget(kg2Label_,2,2);

    gridLayout_->addWidget(length2Label_,3,0);
    gridLayout_->addWidget(length2SpinBox_,3,1);
    gridLayout_->addWidget(m2Label_,3,2);

    gridLayout_->addWidget(theta1Label_,4,0);
    gridLayout_->addWidget(theta1SpinBox_,4,1);
    gridLayout_->addWidget(pi1Label_,4,2);

    gridLayout_->addWidget(theta2Label_,5,0);
    gridLayout_->addWidget(theta2SpinBox_,5,1);
    gridLayout_->addWidget(pi2Label_,5,2);

    solverSwapLayout_->addWidget(RK4_Solver,0,0);
    solverSwapLayout_->addWidget(ImplicitEuler_Solver,1,0);
    solverSwapLayout_->addWidget(trajectoryDraw_,2,0);
    solverSwapLayout_->addWidget(startSimulation_,0,1);
    solverSwapLayout_->addWidget(stopSimulation_,1,1);

    commandLayout_->addLayout(gridLayout_);
    commandLayout_->addLayout(solverSwapLayout_);

    mainLayout_->addLayout(commandLayout_);
    mainLayout_->addWidget(canvas_);
    setLayout(mainLayout_);
    showMaximized();
    setAttribute(Qt::WA_ShowWithoutActivating);


}

void DoublePendulum::closeEvent(QCloseEvent*)
{
    emit widgetClosed();
    close();
}

void DoublePendulum::DiffEqSolverChanged()
{
    QObject* send = sender();
    if(send == RK4_Solver) canvas_->setDiffEqSolver(solver::RK4);
    else if(send == ImplicitEuler_Solver) canvas_->setDiffEqSolver(solver::IMPLICIT_EULER);
}


void DoublePendulum::startSimulation()
{
   canvas_->startSimulation(mass1SpinBox_->value(),length1SpinBox_->value(),mass2SpinBox_->value(),length2SpinBox_->value(),theta1SpinBox_->value() * M_PI,theta2SpinBox_->value() * M_PI);
   mass1SpinBox_->setEnabled(false);
   mass2SpinBox_->setEnabled(false);
   length1SpinBox_->setEnabled(false);
   length2SpinBox_->setEnabled(false);
   theta1SpinBox_->setEnabled(false);
   theta2SpinBox_->setEnabled(false);
   ImplicitEuler_Solver->setEnabled(false);
   RK4_Solver->setEnabled(false);
}
void DoublePendulum::stopSimulation()
{

    canvas_->stopSimulation();
    mass1SpinBox_->setEnabled(true);
    mass2SpinBox_->setEnabled(true);
    length1SpinBox_->setEnabled(true);
    length2SpinBox_->setEnabled(true);
    theta1SpinBox_->setEnabled(true);
    theta2SpinBox_->setEnabled(true);
    ImplicitEuler_Solver->setEnabled(true);
    RK4_Solver->setEnabled(true);
}

void DoublePendulum::drawChanged()
{
    canvas_->changeDraw(trajectoryDraw_->isChecked());
}

} //namespace doublependulum
