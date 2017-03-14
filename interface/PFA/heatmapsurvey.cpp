#include "heatmapsurvey.h"



    HeatMapSurvey::HeatMapSurvey(QWidget *parent) : QWidget(parent),periodFilter(new PeriodFilter),usersFilter(new UsersFilter),tripsFilter(new TripsFilter),densityFilter(new DensityFilter)
    {
    QGroupBox *groupbox = new QGroupBox("Recherche :", this);
    QComboBox *citiesList = new QComboBox(this);

    citiesList->addItem("New-York");
    citiesList->addItem("San Francisco");
    citiesList->addItem("Washington");
    citiesList->addItem("Chattanooga");
    citiesList->addItem("Chicago");
    citiesList->addItem("Minneapolis");
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
