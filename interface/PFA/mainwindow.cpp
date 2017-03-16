#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), heatMapSurvey(new HeatMapSurvey), osm(new QWidget)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF_8"));
    resize(600,300);
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QAction *actionQuitter = new QAction("&Quitter", this);

    menuFichier->addAction(actionQuitter);


    QMenu *menuEdition = menuBar()->addMenu("&Edition");
    QMenu *menuMAJ = menuBar()->addMenu("&Mise a jour");
    QAction * updateAll = menuMAJ->addAction("Tout mettre à jour");
    QMenu * majOneCity = menuMAJ->addMenu("Maj rapide 1 ville");
    QAction * majNewYork = majOneCity->addAction("New York");
    QAction * majSanFrancisco = majOneCity->addAction("San Francisco");
    QAction * majWashington = majOneCity->addAction("Washington");
    QAction * majChattanooga = majOneCity->addAction("Chattanooga");
    QAction * majChicago = majOneCity->addAction("Chicago");
    QAction * majMinneapolis = majOneCity->addAction("Minneapolis");

    QMenu *menuAide = menuBar()->addMenu("&Aide");
    QWidget * mainWidget = new QWidget();
    QGridLayout *lay = new QGridLayout;
    QPushButton *bouton1 = new QPushButton("Bonjour",osm);
    lay->addWidget(osm, 0, 0);
    lay->addWidget(heatMapSurvey, 0, 1);
    mainWidget->setLayout(lay);
    setCentralWidget(mainWidget);

    }

MainWindow::~MainWindow()
{

}
