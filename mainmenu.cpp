#include "mainmenu.h"
#include "harmonic_oscillation.h"
#include <QSizePolicy>
#include "mass_on_spring.h"
#include "oscillating_support_pendulum.h"
#include "doublependulum.h"
#include <iostream>
typedef QVector<QPushButton*>::size_type vec_size;
MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    gridLayout_ = new QGridLayout();
    simulations_.push_back(new QPushButton("Help"));
    simulations_.push_back(new QPushButton("Harmonic oscillation"));
    simulations_.push_back(new QPushButton("Mass on spring"));
    simulations_.push_back(new QPushButton("Oscillating support pendulum"));
    simulations_.push_back(new QPushButton("Double pendulum"));

    simulations_[0]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy ::Minimum);
    gridLayout_->addWidget(simulations_[0]);

    for(vec_size i = 1; i < simulations_.size(); i++)
    {
        simulations_[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy ::Expanding);
        gridLayout_->addWidget(simulations_[i]);
        connect(simulations_[i],SIGNAL(clicked()),this,SLOT(simulationCalled()));
    }
    QWidget::setLayout(gridLayout_);
}
MainMenu::~MainMenu()
{
    for(vec_size i = 0; i < simulations_.size(); i++) delete simulations_[i];
    delete gridLayout_;
}

void MainMenu::simulationCalled()
{
    QPushButton* sender_button=dynamic_cast<QPushButton*>(QObject::sender());
    int location = gridLayout_->indexOf(sender_button);

    switch (location)
    {
        case 0:/*help*/break;
        case 1:
        {
            harmonicoscillation::Harmonic_Oscillation* sim = new harmonicoscillation::Harmonic_Oscillation();
            connect(sim,SIGNAL(widgetClosed()),this,SLOT(widgetClosed()));
            sim->show();
            break;
        }
         case 2:
        {
            massonspring::Mass_On_Spring* sim = new massonspring::Mass_On_Spring();
           sim->show();
            break;
        }
    case 3:
        {
            oscillatingsupportpendulum::Oscillating_Support_Pendulum* sim = new oscillatingsupportpendulum::Oscillating_Support_Pendulum();
            connect(sim,SIGNAL(widgetClosed()),this,SLOT(widgetClosed()));
            sim->show();
            break;
        }
    case 4:
        {
        doublependulum::DoublePendulum* sim = new doublependulum::DoublePendulum();
        connect(sim,SIGNAL(widgetClosed()),this,SLOT(widgetClosed()));
        sim->show();
        break;
    }

    }

    for(vec_size i = 0; i < simulations_.size(); i++) simulations_[i]->setEnabled(false);
}

void MainMenu::widgetClosed()
{
    for(vec_size i = 0; i < simulations_.size(); i++) simulations_[i]->setEnabled(true);
}
