#ifndef USERSFILTER_H
#define USERSFILTER_H

#include <QWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class UsersFilter;

#include "controllerInterface.hpp"
/**
 * This class is a small window offering the possibility to the user to fill a survey to filter the trips with the users data.
 */
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
