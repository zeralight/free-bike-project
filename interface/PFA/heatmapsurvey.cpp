
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

#include "heatmapsurvey.hpp"



HeatMapSurvey::HeatMapSurvey(ControllerInterface * controller, QWidget *parent) : QWidget(parent),
                                                                                      periodFilter(new PeriodFilter(controller)),
                                                                                      usersFilter(new UsersFilter(controller)),
                                                                                      tripsFilter(new TripsFilter(controller)),
										  densityFilter(new DensityFilter(controller)),
                                                                                     controller(controller)
{
    QGroupBox *groupbox = new QGroupBox("Recherche :", this);
    QComboBox *citiesList = new QComboBox(this);

    citiesList->addItem("New-York");
    citiesList->addItem("San Francisco");
    citiesList->addItem("Washington");
    citiesList->addItem("Chattanooga");
    citiesList->addItem("Chicago");
    citiesList->addItem("Minneapolis");

    QObject::connect(citiesList, SIGNAL(activated(const QString &)), this, SLOT(cityChanged(const QString &)));

    QPushButton *period = new QPushButton("Periode");
    QObject::connect(period, SIGNAL(clicked(bool)), periodFilter, SLOT(show())) ;
    QPushButton *users = new QPushButton("Utilisateurs");
    QObject::connect(users, SIGNAL(clicked(bool)), usersFilter, SLOT(show())) ;
    QPushButton *bikes = new QPushButton("Vélos");
    QObject::connect(bikes, SIGNAL(clicked(bool)), densityFilter, SLOT(show()));
    QPushButton  *trips = new QPushButton ("Type trajets");
    QObject::connect(trips, SIGNAL(clicked(bool)), tripsFilter, SLOT(show()));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(citiesList);
    vbox->addWidget(period);
    vbox->addWidget(users);
    vbox->addWidget(bikes);
    vbox->addWidget(trips);

    groupbox->setLayout(vbox);

}
void HeatMapSurvey::cityChanged(const QString & cityName){
  controller->cityChanged(cityName.toStdString());
}
