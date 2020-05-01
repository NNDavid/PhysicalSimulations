#include "simulationdata.h"
namespace simdata {

SimulationData::SimulationData(const int row_size, const int column_size,QWidget* parent):QWidget(parent)
{
    labels_.resize(row_size);
    for(int i = 0 ;i < labels_.size();i++)
    {
        labels_[i].resize(column_size);
        for(int j = 0; j < labels_[i].size(); j++) labels_[i][j] = new QLabel(this);
    }
}

void SimulationData::setLabelText(const QString& str,const int row,const int column)
{
    if(row >= labels_.size()) std::runtime_error("Runtime error!");
    else if(column >= labels_[row - 1].size()) std::runtime_error("Runtime error!");
    else labels_[row][column]->setText(str);
}

}

