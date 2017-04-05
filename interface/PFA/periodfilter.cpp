
#include <QWidget>
#include <QDateTimeEdit>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <stdlib.h>
#include "controllerInterface.hpp"
#include "periodfilter.hpp"
#include <stdio.h>

PeriodFilter::PeriodFilter(ControllerInterface * controller, QWidget *parent) : QWidget(parent),
    beginning(new QDateTimeEdit),
    end(new QDateTimeEdit),
    normal(new QRadioButton("Normale")),
    slot(new QRadioButton("Créneaux")),
    slotsChoice(new QWidget),
    controller(controller)
{
    setWindowTitle("Filtre periode");
    resize(300,300);
    QGridLayout * lay = new QGridLayout;
    lay->addWidget(new QLabel("Selectionnez la date et l'heure de début de période :"),0,0,1,2);
    lay->addWidget(beginning,1,0);
    lay->addWidget(new QLabel("Selectionnez la date et l'heure de fin de période :"),2,0,1,2);
    lay->addWidget(end,3,0);
    lay->addWidget(new QLabel("Selectionnez le type de pèriode que vous souhaitez :"),4,0,1,2);
    lay->addWidget(normal,5,0);
    lay->addWidget(slot,5,1);
    slotsChoice->hide();
    lay->addWidget(slotsChoice,6,0);
    QObject::connect(normal, SIGNAL(clicked(bool)), slotsChoice, SLOT(hide()));
    QObject::connect(slot, SIGNAL(clicked(bool)), slotsChoice, SLOT(show())) ;
    QPushButton * validate = new QPushButton("Valider");
    lay->addWidget(validate,7,0);
    QObject::connect(validate, SIGNAL(clicked(bool)), this, SLOT(validation())) ;

    QGridLayout * laySlots = new QGridLayout;
    laySlots->setSpacing(0);
    //aySlots->setAlignement(Qt::AlignLeft);
    int i = 0;
    char * name;
    for(i=0;i<24;i++){
        asprintf(&name,"%d",i+1);

     hours[i]= new QPushButton(name);
        free(name);
     hours[i]->setCheckable(true);
     hours[i]->setFixedSize(25,25);
     laySlots->addWidget(hours[i],i/12,i%12);
    }
    slotsChoice->setLayout(laySlots);

    this->setLayout(lay);
}

void PeriodFilter::validation(){
    this->close();
    bool slots[24];
    int i = 0;
    for(i;i++;i<24){
        slots[i] = this->hours[i]->isChecked();
    }
    controller->returnPeriodFilter(beginning->date().day(),beginning->date().month(),beginning->date().year,beginning->time().hour(),beginning->time().minute(),
                           end->date().day(),end->date().month(),end->date().year,end->time().hour(),end->time().minute(),
                           normal->isChecked(), slots);
}
