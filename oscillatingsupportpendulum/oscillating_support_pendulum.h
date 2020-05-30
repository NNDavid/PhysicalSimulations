#ifndef OSCILLATING_SUPPORT_PENDULUM_H
#define OSCILLATING_SUPPORT_PENDULUM_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QCheckBox>
#include "qsfml_oscillatingsupportpendulum.h"
namespace oscillatingsupportpendulum {
class Oscillating_Support_Pendulum : public QWidget
{
    Q_OBJECT
public:
    explicit Oscillating_Support_Pendulum(QWidget *parent = nullptr);
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

    QDoubleSpinBox* lengthSpinBox_;
    QLabel* lengthLabel_;
    QLabel* mLabel_;

    QDoubleSpinBox* amplitudeSpinBox_;
    QLabel* amplitudeLabel_;
    QLabel* mLabel2_;

    QDoubleSpinBox* periodSpinBox_;
    QLabel* periodLabel_;
    QLabel* sLabel_;

    QDoubleSpinBox* initialThetaSpinBox_;
    QLabel* initialThetaLabel_;
    QLabel* piLabel_;

    QGridLayout* solverSwapLayout_;
    QRadioButton* implicitEulerSolver_;

    QPushButton* startSimulation_;
    QPushButton* stopSimulation_;
    QCheckBox* drawTrajectory_;

    QSFML_OscillatingSupportPendulum* canvas_;


};
}
#endif // OSCILLATING_SUPPORT_PENDULUM_H
