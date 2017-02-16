#include "periodfilter.h"

PeriodFilter::PeriodFilter(QWidget *parent) : QWidget(parent),beginning(new QDateTimeEdit),end(new QDateTimeEdit)
,normal(new QRadioButton("Normale")),slot(new QRadioButton("Créneaux")),toImplement(new QLabel("Pas encore implémenté !"))
{
    setWindowTitle("Filtre periode");
    resize(300,300);
    QGridLayout * lay = new QGridLayout;
    lay->addWidget(new QLabel("Selectionnez la date et l'heure de début de pèriode :"),0,0,1,2);
    lay->addWidget(beginning,1,0);
    lay->addWidget(new QLabel("Selectionnez la date et l'heure de fin de pèriode :"),2,0,1,2);
    lay->addWidget(end,3,0);
    lay->addWidget(new QLabel("Selectionnez le type de pèriode que vous souhaitez :"),4,0,1,2);
    lay->addWidget(normal,5,0);
    lay->addWidget(slot,5,1);
    toImplement->hide();
    lay->addWidget(toImplement,6,0);
    QObject::connect(normal, SIGNAL(clicked(bool)), toImplement, SLOT(hide()));
    QObject::connect(slot, SIGNAL(clicked(bool)), toImplement, SLOT(show())) ;
    QPushButton * validate = new QPushButton("Valider");
    lay->addWidget(validate,7,0);
    QObject::connect(validate, SIGNAL(clicked(bool)), this, SLOT(validation())) ;


    this->setLayout(lay);
}

void PeriodFilter::validation(){
    this->close();
}
