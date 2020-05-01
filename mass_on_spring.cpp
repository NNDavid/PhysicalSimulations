#include "mass_on_spring.h"
namespace massonspring {


Mass_On_Spring::Mass_On_Spring(QWidget *parent) : QWidget(parent)
{
    mainLayout_ = new QVBoxLayout();

        commandLayout_ = new QHBoxLayout();

        gridLayout_ = new QGridLayout();

        massSpinBox_ = new QDoubleSpinBox();
        massSpinBox_->setRange(0.1,100.0);
        massSpinBox_->setSingleStep(0.5);
        massSpinBox_->setValue(50.0);


        massLabel_ = new QLabel("m = ");

        massLabel_->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

        kgLabel_ = new QLabel("kg");


        springConstantSpinBox_ = new QDoubleSpinBox();
        springConstantSpinBox_->setRange(0.1,1000.0);
        springConstantSpinBox_->setSingleStep(5.0);
        springConstantSpinBox_->setValue(500.0);

        springConstantLabel_ = new QLabel("K = ");

        NmLabel_ = new QLabel("N/m");

        solverSwapLayout_ = new QGridLayout();

        exactSolver_ = new QRadioButton("Exact solution");
        exactSolver_->setChecked(true);
        connect(exactSolver_,SIGNAL(clicked()),this,SLOT(DiffEqSolverChanged()));

        eulerSolver_ = new QRadioButton("Euler diffeq solver");
        connect(eulerSolver_,SIGNAL(clicked()),this,SLOT(DiffEqSolverChanged()));

        compareEulerSolver_ = new QRadioButton("Compare Euler diffeq solver");
        connect(compareEulerSolver_,SIGNAL(clicked()),this,SLOT(DiffEqSolverChanged()));


        solverSwapLayout_->addWidget(exactSolver_,0,0);
        solverSwapLayout_->addWidget(eulerSolver_,1,0);
        solverSwapLayout_->addWidget(compareEulerSolver_,2,0);

        canvas_ = new QSFML_MassOnSpring(this, QPoint(20, 20), QSize(360, 360));
        connect(canvas_,SIGNAL(simulationRestarted()),this,SLOT(simulationRestarted()));

        gridLayout_->addWidget(massLabel_,0,0);
        gridLayout_->addWidget(massSpinBox_,0,1);
        gridLayout_->addWidget(kgLabel_,0,2);

        gridLayout_->addWidget(springConstantLabel_,1,0);
        gridLayout_->addWidget(springConstantSpinBox_,1,1);
        gridLayout_->addWidget(NmLabel_,1,2);

        commandLayout_->addLayout(gridLayout_);
        commandLayout_->addLayout(solverSwapLayout_);
        mainLayout_->addLayout(commandLayout_);
        mainLayout_->addWidget(canvas_);
        QWidget::setLayout(mainLayout_);


        canvas_->show();
    }
    /*Mass_On_Spring::~Mass_On_Spring()
    {
       // emit widgetClosing();
        delete mainLayout_;
        delete canvas_;
        delete gridLayout_;

        delete massSpinBox_;
        delete massLabel_;
        delete kgLabel_;

        delete springConstantSpinBox_;
        delete springConstantLabel_;
        delete NmLabel_;
    }*/
    void Mass_On_Spring::simulationRestarted()
    {
        canvas_->setSystemValues(massSpinBox_->value(),springConstantSpinBox_->value());
    }

}
