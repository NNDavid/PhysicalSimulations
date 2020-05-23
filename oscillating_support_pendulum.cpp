#include "oscillating_support_pendulum.h"
namespace oscillatingsupportpendulum {
Oscillating_Support_Pendulum::Oscillating_Support_Pendulum(QWidget *parent) : QWidget(parent)
{
       mainLayout_ = new QVBoxLayout(this);


       canvas_ = new QSFML_OscillatingSupportPendulum(this, QPoint(20, 20), QSize(360, 360));
       implicitEulerSolver_ = new QRadioButton(this);
       implicitEulerSolver_ -> setText("Implicit Euler");
       implicitEulerSolver_ ->setChecked(true);
       connect(implicitEulerSolver_,SIGNAL(clicked()),this,SLOT(DiffEqSolverChanged()));

        commandLayout_ = new QHBoxLayout(this);

        gridLayout_ = new QGridLayout(this);

        lengthSpinBox_ = new QDoubleSpinBox(this);
        lengthSpinBox_->setRange(0.1,100);
        lengthSpinBox_->setSingleStep(0.5);
        lengthSpinBox_->setValue(5.0);

        lengthLabel_ = new QLabel(this);
        lengthLabel_->setText("l = ");
        mLabel_ = new QLabel(this);
        mLabel_->setText("m");


        amplitudeSpinBox_ = new QDoubleSpinBox(this);
        amplitudeSpinBox_->setRange(0,10);
        amplitudeSpinBox_->setSingleStep(5.0);
        amplitudeSpinBox_->setValue(5.0);

        amplitudeLabel_ = new QLabel(this);
        amplitudeLabel_->setText("A = ");


        periodSpinBox_ = new QDoubleSpinBox(this);
        periodSpinBox_->setRange(1,10);
        periodSpinBox_->setSingleStep(0.1);
        periodSpinBox_->setValue(5.0);

        periodLabel_ = new QLabel(this);
        periodLabel_ ->setText("T = ");

        sLabel_ = new QLabel(this);
        sLabel_ -> setText("s");

        initialThetaSpinBox_ = new QDoubleSpinBox(this);
        initialThetaSpinBox_->setRange(-1,1);
        initialThetaSpinBox_->setSingleStep(0.01);
        initialThetaSpinBox_->setValue(0);


        initialThetaLabel_ = new QLabel(this);
        initialThetaLabel_ -> setText("Θ = ");

        piLabel_ = new QLabel(this);
        piLabel_ ->setText("π");

        startSimulation_ = new QPushButton(this);
        startSimulation_ -> setText("Start simulation");
        connect(startSimulation_,SIGNAL(clicked()),this,SLOT(startSimulation()));

        stopSimulation_ = new QPushButton(this);
        stopSimulation_ -> setText("Stop simualtion");
        connect(stopSimulation_,SIGNAL(clicked()),this,SLOT(stopSimulation()));

        drawTrajectory_ = new QCheckBox(this);
        drawTrajectory_->setText("Draw only trajectory");
        drawTrajectory_->setChecked(false);
        connect(drawTrajectory_,SIGNAL(clicked()),this,SLOT(drawChanged()));


        solverSwapLayout_ = new QGridLayout(this);
        solverSwapLayout_ ->addWidget(implicitEulerSolver_,0,0);

        solverSwapLayout_ ->addWidget(startSimulation_,0,1);
        solverSwapLayout_ ->addWidget(stopSimulation_,1,1);
        solverSwapLayout_ ->addWidget(drawTrajectory_,2,0);

        gridLayout_->addWidget(lengthLabel_,0,0);
        gridLayout_->addWidget(lengthSpinBox_,0,1);
        gridLayout_->addWidget(mLabel_,0,2);

        gridLayout_->addWidget(amplitudeLabel_,1,0);
        gridLayout_->addWidget(amplitudeSpinBox_,1,1);
        gridLayout_->addWidget(mLabel_,1,2);

        gridLayout_->addWidget(periodLabel_,2,0);
        gridLayout_->addWidget(periodSpinBox_,2,1);
        gridLayout_->addWidget(sLabel_,2,2);

        gridLayout_->addWidget(initialThetaLabel_,3,0);
        gridLayout_->addWidget(initialThetaSpinBox_,3,1);
        gridLayout_->addWidget(piLabel_,3,2);

        commandLayout_->addLayout(gridLayout_);
        commandLayout_->addLayout(solverSwapLayout_);


        mainLayout_->addLayout(commandLayout_);

        mainLayout_->addWidget(canvas_);

        QWidget::setLayout(mainLayout_);

        showMaximized();
        setAttribute(Qt::WA_ShowWithoutActivating);
                canvas_->show();
}
void Oscillating_Support_Pendulum::stopSimulation()
{
    canvas_->stopSimulation();
    lengthSpinBox_->setEnabled(true);
    amplitudeSpinBox_->setEnabled(true);
    periodSpinBox_->setEnabled(true);
    initialThetaSpinBox_->setEnabled(true);
    implicitEulerSolver_->setEnabled(true);
}

void Oscillating_Support_Pendulum::startSimulation()
{
    canvas_->startSimulation(lengthSpinBox_->value(),amplitudeSpinBox_->value(),periodSpinBox_->value(),initialThetaSpinBox_->value());
    lengthSpinBox_->setEnabled(false);
    amplitudeSpinBox_->setEnabled(false);
    periodSpinBox_->setEnabled(false);
    initialThetaSpinBox_->setEnabled(false);
    implicitEulerSolver_->setEnabled(false);
}

void Oscillating_Support_Pendulum::DiffEqSolverChanged()
{
    QObject* send = sender();
    if(send == implicitEulerSolver_) canvas_->setDiffEqSolver(solver::IMPLICIT_EULER);
}

void Oscillating_Support_Pendulum::closeEvent(QCloseEvent*)
{
    emit widgetClosed();
    close();
}
 void Oscillating_Support_Pendulum::drawChanged()
 {
     canvas_->changeDraw(drawTrajectory_->isChecked());
 }
}// namespace oscillatingsupportpendulum
