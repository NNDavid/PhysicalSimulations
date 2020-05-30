#include "simulationdata.h"
#include <cassert>
namespace simdata {

SimulationData::SimulationData(const int row_size, const int column_size,QWidget* parent):QWidget(parent),mainLayout_(new QGridLayout(this)),pause_(true)
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
    assert(row < labels_.size());
    assert(column < labels_[row].size());
    if(!pause_) labels_[row][column]->setText(str);
}

void SimulationData::pause()
{
    pause_ = true;
}

void SimulationData::unpause()
{
    pause_ = false;
}

}

