#ifndef PERIODFILTER_H
#define PERIODFILTER_H

#include <QWidget>
#include <QDateTimeEdit>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <stdlib.h>

class PeriodFilter;

#include "controllerInterface.hpp"
/**
 * This class is a small window offering the possibility to the user to fill a survey to filter the trips with the period.
 */
class PeriodFilter : public QWidget
{
    Q_OBJECT
public:
    explicit PeriodFilter(ControllerInterface * controller, QWidget *parent = 0);
    QDateTimeEdit * beginning;
    QDateTimeEdit * end;
    QRadioButton * normal;
    QRadioButton * slot;
    QWidget * slotsChoice;
    QPushButton * hours [24];
private:
    ControllerInterface * controller;

signals:

public slots:
    void validation();
};

#endif // PERIODFILTER_H
