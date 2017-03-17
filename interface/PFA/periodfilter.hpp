#ifndef PERIODFILTER_H
#define PERIODFILTER_H

#include <QWidget>
#include <QDateTimeEdit>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <stdlib.h>
class PeriodFilter : public QWidget
{
    Q_OBJECT
public:
    explicit PeriodFilter(QWidget *parent = 0);
    QDateTimeEdit * beginning;
    QDateTimeEdit * end;
    QRadioButton * normal;
    QRadioButton * slot;
    QWidget * slotsChoice;
    QPushButton * hours [24];

signals:

public slots:
    void validation();
};

#endif // PERIODFILTER_H
