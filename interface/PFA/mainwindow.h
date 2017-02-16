#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMenuBar>
#include <QMainWindow>
#include "questionnairechaleur.h"
#include <QHBoxLayout>
#include <QPushButton>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void createMenus();
    HeatMapSurvey *heatMapSurvey;
    QWidget * osm;
    ~MainWindow();
};

#endif // MAINWINDOW_H
