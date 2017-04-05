#ifndef USERSFILTER_H
#define USERSFILTER_H

#include <QWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "controllerInterface.hpp"
class UsersFilter : public QWidget
{
    Q_OBJECT
public:
    explicit UsersFilter(ControllerInterface * controller, QWidget *parent = 0);
    QCheckBox * men;
    QCheckBox * women;
    QSpinBox * minimumAge;
    QSpinBox * maximumAge;
    QCheckBox * subscriber;
    QCheckBox * nonSubscriber;
private:
    ControllerInterface * controller;
signals:

public slots:
    void validation();

};

#endif // USERSFILTER_H
