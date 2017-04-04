#ifndef QUESTIONNAIRECHALEUR_H
#define QUESTIONNAIRECHALEUR_H

#include <QCheckBox>
#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QPushButton>
#include "periodfilter.hpp"
#include "usersfilter.hpp"
#include "tripsfilter.hpp"
#include "densityfilter.hpp"

#include "controllerInterface.hpp"
/*
 * @brief This class is a the widget for generating the interface for the heatmap's settings.
 */
class HeatMapSurvey  : public QWidget
{
public:
    HeatMapSurvey(ControllerInterface * controller, QWidget *parent = 0);
    PeriodFilter * periodFilter;
    UsersFilter * usersFilter;
    TripsFilter * tripsFilter;
    DensityFilter * densityFilter;
private:
    ControllerInterface * controller;
};

#endif // QUESTIONNAIRECHALEUR_H
