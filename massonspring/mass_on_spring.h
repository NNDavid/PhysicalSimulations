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
#include <QCheckBox>
#include <QPushButton>
namespace massonspring {


class Mass_On_Spring : public QWidget
{
    Q_OBJECT
public:
    explicit Mass_On_Spring(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent*) override;

signals:
    void widgetClosed();


private slots:
    void startSimulation();
    void stopSimulation();
    void DiffEqSolverChanged();
    void drawChanged();
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

    QDoubleSpinBox* thetaSpinBox_;
    QLabel* thetaLabel_;
    QLabel* piLabel_;

    QDoubleSpinBox* lSpinBox_;
    QLabel* lLabel_;
    QLabel* mLabel_;


    QDoubleSpinBox* xSpinBox_;
    QLabel* xLabel_;
    QLabel* mLabel2_;


    QGridLayout* solverSwapLayout_;
    QRadioButton* modifiedEulerSolver_;

    QCheckBox* trajectory_;

    QPushButton* startSimulation_;
    QPushButton* stopSimulation_;

    QSFML_MassOnSpring* canvas_;


};
}

#endif // MASS_ON_SPRING_H
