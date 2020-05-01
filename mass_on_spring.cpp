#include "mass_on_spring.h"
namespace massonspring {


Mass_On_Spring::Mass_On_Spring(QWidget *parent) :
    QWidget(parent),
    mainLayout_(new QVBoxLayout(this)),
    commandLayout_(new QHBoxLayout(this)),
    gridLayout_(new QGridLayout(this)),
    massSpinBox_(new QDoubleSpinBox(this)),
    massLabel_(new QLabel(this)),
    kgLabel_(new QLabel(this)),
    springConstantSpinBox_(new QDoubleSpinBox(this)),
    springConstantLabel_(new QLabel(this)),
    NmLabel_(new QLabel(this)),
    thetaSpinBox_(new QDoubleSpinBox(this)),
    thetaLabel_(new QLabel(this)),
    piLabel_(new QLabel(this)),
    lSpinBox_(new QDoubleSpinBox(this)),
    lLabel_(new QLabel(this)),
    mLabel_(new QLabel(this)),
    xSpinBox_(new QDoubleSpinBox(this)),
    xLabel_(new QLabel(this)),
    mLabel2_(new QLabel(this)),
    solverSwapLayout_(new QGridLayout(this)),
    modifiedEulerSolver_(new QRadioButton(this)),
    trajectory_(new QCheckBox(this)),
    startSimulation_(new QPushButton(this)),
    restartSimulation_(new QPushButton(this)),
    canvas_(new QSFML_MassOnSpring(this, QPoint(20, 20), QSize(360, 360)))
{
    massSpinBox_->setRange(0.1,50);
    massSpinBox_->setSingleStep(0.5);
    massSpinBox_->setValue(25.0);

    massLabel_->setText("m = ");
    kgLabel_->setText("kg");

    springConstantSpinBox_->setRange(50,500);
    springConstantSpinBox_->setSingleStep(5.0);
    springConstantSpinBox_->setValue(200.0);

    springConstantLabel_->setText("K = ");
    NmLabel_->setText("N/m");

    thetaSpinBox_->setRange(-0.5,0.5);
    thetaSpinBox_->setSingleStep(0.1);
    thetaSpinBox_->setValue(0);

    thetaLabel_->setText("Θ = ");
    piLabel_->setText("π");

    lSpinBox_->setRange(1,10);
    lSpinBox_->setSingleStep(0.5);
    lSpinBox_->setValue(10);

    lLabel_->setText("l = ");
    mLabel_->setText("m");

    xSpinBox_->setRange(1,10);
    xSpinBox_->setSingleStep(0.5);
    xSpinBox_->setValue(5);

    xLabel_->setText("x = ");
    mLabel2_->setText("m");

    trajectory_->setText("Draw trajectory");
    connect(trajectory_,SIGNAL(clicked()),this,SLOT(drawChanged()));

    modifiedEulerSolver_->setText("Modified Euler");
    modifiedEulerSolver_->setChecked(true);
    connect(modifiedEulerSolver_,SIGNAL(clicked()),this,SLOT(DiffEqSolverChanged()));

    startSimulation_->setText("Start simulation");
    connect(startSimulation_,SIGNAL(clicked()),this,SLOT(startSimulation()));

    restartSimulation_->setText("Restart simulation");
    connect(restartSimulation_,SIGNAL(clicked()),this,SLOT(restartSimulation()));



    gridLayout_->addWidget(massLabel_,0,0);
    gridLayout_->addWidget(massSpinBox_,0,1);
    gridLayout_->addWidget(kgLabel_,0,2);

    gridLayout_->addWidget(springConstantLabel_,1,0);
    gridLayout_->addWidget(springConstantSpinBox_,1,1);
    gridLayout_->addWidget(NmLabel_,1,2);


    gridLayout_->addWidget(thetaLabel_,2,0);
    gridLayout_->addWidget(thetaSpinBox_,2,1);
    gridLayout_->addWidget(piLabel_,2,2);

    gridLayout_->addWidget(lLabel_,3,0);
    gridLayout_->addWidget(lSpinBox_,3,1);
    gridLayout_->addWidget(mLabel_,3,2);

    gridLayout_->addWidget(xLabel_,4,0);
    gridLayout_->addWidget(xSpinBox_,4,1);
    gridLayout_->addWidget(mLabel2_,4,2);

    solverSwapLayout_->addWidget(modifiedEulerSolver_,0,0);
    solverSwapLayout_->addWidget(trajectory_,1,0);
    solverSwapLayout_->addWidget(startSimulation_,0,1);
    solverSwapLayout_->addWidget(restartSimulation_,1,1);

    commandLayout_->addLayout(gridLayout_);
    commandLayout_->addLayout(solverSwapLayout_);

    mainLayout_->addLayout(commandLayout_);
    mainLayout_->addWidget(canvas_);
    setLayout(mainLayout_);








}
void Mass_On_Spring::restartSimulation()
{
   canvas_->restartSimulation();
}

void Mass_On_Spring::startSimulation()
{
    canvas_->startSimulation(massSpinBox_->value(),springConstantSpinBox_->value(),thetaSpinBox_->value() * M_PI,lSpinBox_->value(),xSpinBox_->value());
}

void Mass_On_Spring::DiffEqSolverChanged()
{
    QObject* send = sender();

    if(send == modifiedEulerSolver_) canvas_->setDiffEqSolver(solver::MODIFIED_EULER);
}

void Mass_On_Spring::closeEvent(QCloseEvent *)
{
    emit widgetClosed();
    close();
}
void Mass_On_Spring::drawChanged()
{
    canvas_->changeDraw(trajectory_->isChecked());
}

}
