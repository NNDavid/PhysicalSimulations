#include "simulationdata.h"
#include <cassert>
namespace simdata {

SimulationData::SimulationData(const int row_size, const int column_size,QWidget* parent):QWidget(parent),mainLayout_(new QGridLayout(this))
{
    labels_.resize(row_size);
    for(int i = 0 ;i < labels_.size();i++)
    {
        labels_[i].resize(column_size);
        for(int j = 0; j < labels_[i].size(); j++)
        {
            labels_[i][j] = new QLabel(this);
            mainLayout_->addWidget(labels_[i][j],i,j);
        }
    }
    setLayout(mainLayout_);
}

void SimulationData::setLabelText(const QString& str,const int row,const int column)
{
    if(row >= labels_.size()) assert(false);
    else if(column >= labels_[row].size()) assert(false);
    else labels_[row][column]->setText(str);
}

}

