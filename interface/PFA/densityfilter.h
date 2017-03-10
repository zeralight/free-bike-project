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

class DensityFilter : public QWidget
{
    Q_OBJECT
public:
    explicit DensityFilter(QWidget *parent = 0);
    QRadioButton * oui;
    QRadioButton * non;
    QWidget * densityChoice;
    QRadioButton * weaker;
    QRadioButton * stronger;
    QSpinBox * percentage;


signals:

public slots:
    void validation();};

#endif // DENSITYFILTER_H
