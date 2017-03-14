#include "densityfilter.h"

DensityFilter::DensityFilter(QWidget *parent) : QWidget(parent),
    oui(new QRadioButton("Oui")),
    non(new QRadioButton("Non")),
    densityChoice(new QWidget),
    weaker(new QRadioButton("moins utilisés")),
    stronger(new QRadioButton("plus utilisés")),
    percentage(new QSpinBox())
  {
      setWindowTitle("Filtre de densité");
      resize(300,300);
      QGridLayout * lay = new QGridLayout;
      percentage->setRange(1,100);
      lay->addWidget(new QLabel("Cette page permet d'ajouter des filtre de densité de trajets. "),0,0,1,5);
      lay->addWidget(new QLabel("C'est à dire ne selectionner que les trajets les plus utilisés ou les moins utilisés."),1,0,1,5);

      lay->addWidget(new QLabel("Voulez-vous filtrer par densité ?"),2,0,1,5);
      lay->addWidget(oui,3,0);
      lay->addWidget(non,3,1);
      QObject::connect(non, SIGNAL(clicked(bool)), densityChoice, SLOT(hide()));
      QObject::connect(oui, SIGNAL(clicked(bool)), densityChoice, SLOT(show()));
      densityChoice->hide();
      lay->addWidget(densityChoice,4,0);
      QPushButton * validate = new QPushButton("Valider");
      lay->addWidget(validate,5,0);
      QObject::connect(validate, SIGNAL(clicked(bool)), this, SLOT(validation())) ;

      QGridLayout * layDensity = new QGridLayout;
      layDensity->addWidget(weaker,0,0);
      layDensity->addWidget(stronger,0,1);
      stronger->setChecked(true);
      layDensity->addWidget(new QLabel("Pourcentage de tout les trajets sélectionné par les autres filtres que vous voulez afficher :"),1,0,1,5);
      layDensity->addWidget(percentage,2,0);


      densityChoice->setLayout(layDensity);

      this->setLayout(lay);
  }

  void DensityFilter::validation(){

      this->close();
  }
