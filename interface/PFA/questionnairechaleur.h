#ifndef QUESTIONNAIRECHALEUR_H
#define QUESTIONNAIRECHALEUR_H
#include <QCheckBox>
#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QPushButton>
#include "periodfilter.h"
#include "usersfilter.h"
#include "tripsfilter.h"
class HeatMapSurvey  : public QWidget
{
public:
    HeatMapSurvey(QWidget *parent = 0);
    PeriodFilter * periodFilter;
    UsersFilter * usersFilter;
    TripsFilter * tripsFilter;

};

#endif // QUESTIONNAIRECHALEUR_H
