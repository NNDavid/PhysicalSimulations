#include "harmonic_oscillation.h"
#include <QSizePolicy>
#include <QCloseEvent>
#include <QIntValidator>
#include <QDoubleValidator>
namespace harmonicoscillation{
Harmonic_Oscillation::Harmonic_Oscillation(QWidget *parent) : QWidget(parent)
{
    startSimulation_ = new QPushButton(this);
    startSimulation_->setText("Start simulation");
    connect(startSimulation_,SIGNAL(clicked()),this,SLOT(startSimulation()));

    stopSimulation_ = new QPushButton(this);
    stopSimulation_ ->setText("Stop simulation");
    connect(stopSimulation_,SIGNAL(clicked()),this,SLOT(stopSimulation()));

    mainLayout_ = new QVBoxLayout(this);

    commandLayout_ = new QHBoxLayout(this);

    gridLayout_ = new QGridLayout(this);

    massSpinBox_ = new QDoubleSpinBox(this);
    massSpinBox_->setRange(0.1,100.0);
    massSpinBox_->setSingleStep(0.5);
    massSpinBox_->setValue(50.0);


    massLabel_ = new QLabel(this);
    massLabel_->setText("m = ");

    massLabel_->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

    kgLabel_ = new QLabel(this);
    kgLabel_->setText("kg");




    elasticConstantSpinBox_ = new QDoubleSpinBox(this);
    elasticConstantSpinBox_->setRange(0.1,1000.0);
    elasticConstantSpinBox_->setSingleStep(5.0);
    elasticConstantSpinBox_->setValue(500.0);

    elasticConstantLabel_ = new QLabel(this);
    elasticConstantLabel_->setText("K = ");

    NmLabel_ = new QLabel(this);
    NmLabel_->setText("N/m");


    amplitudeSpinBox_ = new QDoubleSpinBox(this);
    amplitudeSpinBox_->setRange(1,5);
    amplitudeSpinBox_->setSingleStep(0.1);
    amplitudeSpinBox_->setValue(1);

    amplitudeLabel_ = new QLabel(this);
    amplitudeLabel_->setText("amplitude = ");

    mLabel_ = new QLabel(this);
    mLabel_->setText("m");


    solverSwapLayout_ = new QGridLayout(this);

    exactSolver_ = new QRadioButton(this);
    exactSolver_->setText("Exact solution");
    exactSolver_->setChecked(true);
    connect(exactSolver_,SIGNAL(clicked()),this,SLOT(DiffEqSolverChanged()));

    eulerSolver_ = new QRadioButton(this);
    eulerSolver_->setText("Euler solver");
    connect(eulerSolver_,SIGNAL(clicked()),this,SLOT(DiffEqSolverChanged()));

    compareEulerSolver_ = new QRadioButton(this);
    compareEulerSolver_->setText("Compare Euler solver to Exact solution");
    connect(compareEulerSolver_,SIGNAL(clicked()),this,SLOT(DiffEqSolverChanged()));



    solverSwapLayout_->addWidget(exactSolver_,0,0);
    solverSwapLayout_->addWidget(eulerSolver_,1,0);
    solverSwapLayout_->addWidget(startSimulation_,0,1);
    solverSwapLayout_->addWidget(stopSimulation_,1,1);
    solverSwapLayout_->addWidget(compareEulerSolver_,2,0);

    canvas_ = new QSFML_HarmonicOscillation(this, QPoint(20, 20), QSize(360, 360));

    gridLayout_->addWidget(massLabel_,0,0);
    gridLayout_->addWidget(massSpinBox_,0,1);
    gridLayout_->addWidget(kgLabel_,0,2);

    gridLayout_->addWidget(elasticConstantLabel_,1,0);
    gridLayout_->addWidget(elasticConstantSpinBox_,1,1);
    gridLayout_->addWidget(NmLabel_,1,2);

    gridLayout_->addWidget(amplitudeLabel_,2,0);
    gridLayout_->addWidget(amplitudeSpinBox_,2,1);
    gridLayout_->addWidget(mLabel_,2,2);

    commandLayout_->addLayout(gridLayout_);
    commandLayout_->addLayout(solverSwapLayout_);
    mainLayout_->addLayout(commandLayout_);
    mainLayout_->addWidget(canvas_);
    QWidget::setLayout(mainLayout_);

    canvas_->show();
    showMaximized();
    setAttribute(Qt::WA_ShowWithoutActivating);
}
Harmonic_Oscillation::~Harmonic_Oscillation()
{
}
void Harmonic_Oscillation::stopSimulation()
{
    canvas_->stopSimulation();
    massSpinBox_->setEnabled(true);
    elasticConstantSpinBox_->setEnabled(true);
    amplitudeSpinBox_->setEnabled(true);
    exactSolver_->setEnabled(true);
    eulerSolver_->setEnabled(true);
    compareEulerSolver_->setEnabled(true);
}

void Harmonic_Oscillation::startSimulation()
{
    canvas_->startSimulation(massSpinBox_->value(),elasticConstantSpinBox_->value(),amplitudeSpinBox_->value());
    massSpinBox_->setEnabled(false);
    elasticConstantSpinBox_->setEnabled(false);
    amplitudeSpinBox_->setEnabled(false);
    exactSolver_->setEnabled(false);
    eulerSolver_->setEnabled(false);
    compareEulerSolver_->setEnabled(false);
}

void Harmonic_Oscillation::DiffEqSolverChanged()
{
    QObject* send = sender();
    if(send == exactSolver_) canvas_->setDiffEqSolver(solver::EXACT);
    else if(send == eulerSolver_) canvas_->setDiffEqSolver(solver::EULER);
    else if(send == compareEulerSolver_) canvas_->setDiffEqSolver(solver::COMPARE_EULER);
}
void Harmonic_Oscillation::closeEvent(QCloseEvent*)
{
    emit widgetClosed();
    close();
}

} //namespace harmonicoscillation


