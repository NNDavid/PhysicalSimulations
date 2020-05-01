#ifndef MASS_ON_SPRING_H
#define MASS_ON_SPRING_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QRadioButton>
#include "qsfml_massonspring.h"
namespace massonspring {


class Mass_On_Spring : public QWidget
{
    Q_OBJECT
public:
    explicit Mass_On_Spring(QWidget *parent = nullptr);

private slots:
    void simulationRestarted();

private:
    QVBoxLayout* mainLayout_;
    QHBoxLayout* commandLayout_;

    QGridLayout* gridLayout_;

    QDoubleSpinBox* massSpinBox_;
    QLabel* massLabel_;
    QLabel* kgLabel_;

    QDoubleSpinBox* springConstantSpinBox_;
    QLabel* springConstantLabel_;
    QLabel* NmLabel_;

    QGridLayout* solverSwapLayout_;
    QRadioButton* exactSolver_;
    QRadioButton* eulerSolver_;
    QRadioButton* compareEulerSolver_;
    QSFML_MassOnSpring* canvas_;


};
}

#endif // MASS_ON_SPRING_H
