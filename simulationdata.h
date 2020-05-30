#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H
#include <QWidget>
#include <QVector>
#include <QGridLayout>
#include <QLabel>

namespace simdata{

class SimulationData : public QWidget
{
    Q_OBJECT
public:
    SimulationData(const int row_size, const int column_size,QWidget *parent = nullptr);
    void setLabelText(const QString& str,const int row,const int column);
    void pause();
    void unpause();
private:
    QVector<QVector<QLabel*>> labels_;
    QGridLayout* mainLayout_;
    bool pause_;
};
}

#endif // SIMULATIONDATA_H
