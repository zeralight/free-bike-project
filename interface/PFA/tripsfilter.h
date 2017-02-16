#ifndef TRIPSFILTER_H
#define TRIPSFILTER_H

#include <QWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class TripsFilter :  public QWidget
{
    Q_OBJECT
public:
    TripsFilter(QWidget *parent = 0);
    QCheckBox * beginStation;
    QCheckBox * endStation;
    QSpinBox * minLengthTrip;
    QSpinBox * maxLengthTrip;
    QSpinBox * minDensityTrip;
    QSpinBox * maxDensityTrip;

signals:

public slots:
    void validation();

};
#endif // TRIPSFILTER_H
