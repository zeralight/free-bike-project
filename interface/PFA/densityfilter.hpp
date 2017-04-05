#ifndef DENSITYFILTER_H
#define DENSITYFILTER_H

#include <QWidget>
#include <QDateTimeEdit>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <stdlib.h>
#include "controllerInterface.h"

class DensityFilter : public QWidget
{
    Q_OBJECT
public:
    explicit DensityFilter(ControllerInterface * controller, QWidget *parent = 0);
    QRadioButton * yes;
    QRadioButton * no;
    QWidget * densityChoice;
    QRadioButton * weaker;
    QRadioButton * stronger;
    QSpinBox * percentage;
private:
    ControllerInterface * controller;

    signals:

public slots:
    void validation();
};

#endif // DENSITYFILTER_H
