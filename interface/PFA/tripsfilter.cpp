#include "tripsfilter.h"

TripsFilter::TripsFilter(QWidget * parent) : QWidget(parent),
    beginStation(new QCheckBox("Stations début à implémenter")),
    endStation(new QCheckBox("Stations arrivee à implémenter")),
    minLengthTrip(new QSpinBox),
    maxLengthTrip(new QSpinBox),
    minDensityTrip(new QSpinBox),
    maxDensityTrip(new QSpinBox)
{
    setWindowTitle("Filtre trajets");
    resize(300,300);
    QGridLayout * lay = new QGridLayout;
    minLengthTrip->setRange(1, 3000);
    maxLengthTrip->setRange(2,1301);
    minDensityTrip->setRange(0,999999998);
    maxDensityTrip->setRange(1,999999999);
    minDensityTrip->setSingleStep(100);
    maxDensityTrip->setSingleStep(100);
    lay->addWidget(new QLabel("Stations de départ :(àfaire)"),0,0,1,5);
    lay->addWidget(beginStation,1,0,1,3);
    lay->addWidget(new QLabel("Sations d'arrrivée :(àfaire)"),2,0,1,5);
    lay->addWidget(endStation,3,0,1,3);
    lay->addWidget(new QLabel("Temps de trajet (en minutes) :"),4,0,1,5);
    lay->addWidget(new QLabel("Min : "),5,0);
    lay->addWidget(minLengthTrip,5,1);
    lay->addWidget(new QLabel("Max : "),5,2);
    lay->addWidget(maxLengthTrip,5,3);
    lay->addWidget(new QLabel("Densité du trajet (en nombre de vélos) :"),6,0,1,5);
    lay->addWidget(new QLabel("Min : "),7,0);
    lay->addWidget(minDensityTrip,7,1);
    lay->addWidget(new QLabel("Max : "),7,2);
    lay->addWidget(maxDensityTrip,7,3);
    QPushButton * validate = new QPushButton("Valider");
    lay->addWidget(validate,8,0);
    QObject::connect(validate, SIGNAL(clicked(bool)), this, SLOT(validation())) ;


    this->setLayout(lay);
}


void TripsFilter::validation(){

    this->close();
    returnTripsFilter(maxLengthTrip->value(),minLengthTrip->value(),maxDensityTrip->value(),minDensityTrip->value());
}




