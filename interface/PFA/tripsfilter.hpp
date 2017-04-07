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
/**
 * This class is a small window offering the possibility to the user to fill a survey to filter the trips with the trips data.
 */
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
