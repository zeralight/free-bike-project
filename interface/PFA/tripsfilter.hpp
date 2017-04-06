#ifndef TRIPSFILTER_H
#define TRIPSFILTER_H

class TripsFilter;

#include <QWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "controllerInterface.hpp"
class TripsFilter :  public QWidget
{
    Q_OBJECT
public:
    TripsFilter(ControllerInterface * controller, QWidget *parent = 0);
    QCheckBox * beginStation;
    QCheckBox * endStation;
    QSpinBox * minLengthTrip;
    QSpinBox * maxLengthTrip;
    QSpinBox * minDensityTrip;
    QSpinBox * maxDensityTrip;
private:
    ControllerInterface * controller;
signals:

public slots:
    void validation();

};
#endif // TRIPSFILTER_H
