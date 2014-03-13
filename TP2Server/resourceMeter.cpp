
///
/// This class implements just
/// a graphical meter to show
/// the currently available resources
///
/// You really wont need to change
/// this class, but if you do
/// state it in your report
///

#include "resourceMeter.h"
#include <QHBoxLayout>

ResourceMeter::ResourceMeter(QString name, int min, int max, int current, QWidget *parent) :
    QWidget(parent)
{
    nameLabel = new QLabel(name);
    bar = new QProgressBar(this);
    bar->setMinimum(min);
    bar->setMaximum(max);
    if (current == -1)
        bar->setValue(min);
    else
        bar->setValue(current);
    bar->setFormat("%v / %m");
    bar->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");

    QHBoxLayout *progressBarLayout = new QHBoxLayout;
    progressBarLayout->addWidget(nameLabel);
    progressBarLayout->addWidget(bar);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(progressBarLayout);
    mainLayout->setContentsMargins(1,1,1,1);
    mainLayout->setSpacing(1);
    setLayout(mainLayout);
}

void ResourceMeter::addResources(int n)
{
    bar->setValue(bar->value()+n);
}
