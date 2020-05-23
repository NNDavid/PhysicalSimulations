#ifndef HARMONIC_OSCILLATION_H
#define HARMONIC_OSCILLATION_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QPushButton>
#include "qsfml_harmonicoscillation.h"
namespace harmonicoscillation {
class Harmonic_Oscillation : public QWidget
{
    Q_OBJECT
public:
    explicit Harmonic_Oscillation(QWidget *parent = nullptr);
    ~Harmonic_Oscillation();
    void closeEvent(QCloseEvent*) override;

signals:
    void widgetClosed();


private slots:
    void startSimulation();
    void stopSimulation();
    void DiffEqSolverChanged();

private:

    QVBoxLayout* mainLayout_;

    QHBoxLayout* commandLayout_;

    QSFML_HarmonicOscillation* canvas_;

    QGridLayout* gridLayout_;

    QDoubleSpinBox* massSpinBox_;
    QLabel* massLabel_;
    QLabel* kgLabel_;

    QDoubleSpinBox* elasticConstantSpinBox_;
    QLabel* elasticConstantLabel_;
    QLabel* NmLabel_;

    QDoubleSpinBox* amplitudeSpinBox_;
    QLabel* amplitudeLabel_;
    QLabel* mLabel_;


    QGridLayout* solverSwapLayout_;
    QRadioButton* exactSolver_;
    QRadioButton* eulerSolver_;
    QRadioButton* compareEulerSolver_;
    QPushButton* startSimulation_;
    QPushButton* stopSimulation_;



};
}

#endif // HARMONIC_OSCILLATION_H
