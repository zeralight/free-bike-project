#include "usersfilter.h"

UsersFilter::UsersFilter(QWidget *parent) : QWidget(parent),men(new QCheckBox("Homme")), women(new QCheckBox("Femme")), minimumAge(new QSpinBox),maximumAge(new QSpinBox),subscriber(new QCheckBox("Abonnés")),nonSubscriber(new QCheckBox("Non abonnés"))
{
    setWindowTitle("Filtre utilisateurs");
    resize(300,300);
    QGridLayout * lay = new QGridLayout;
    lay->addWidget(new QLabel("Sexe :"),0,0,1,2);
    lay->addWidget(women,1,0,1,2);
    lay->addWidget(men,1,1,1,2);
    lay->addWidget(new QLabel("Age :"),2,0,1,2);
    lay->addWidget(new QLabel("De"),3,0);
    lay->addWidget(minimumAge,3,1);
    lay->addWidget(new QLabel("à"),3,2);
    lay->addWidget(maximumAge,3,3);
    lay->addWidget(new QLabel("Abonné ou non :"),4,0,1,2);
    lay->addWidget(subscriber,5,0,1,2);
    lay->addWidget(nonSubscriber,5,2,1,2);
    QPushButton * validate = new QPushButton("Valider");
    lay->addWidget(validate,7,0);
    QObject::connect(validate, SIGNAL(clicked(bool)), this, SLOT(validation())) ;


    this->setLayout(lay);
}


void UsersFilter::validation(){
    this->close();
}


