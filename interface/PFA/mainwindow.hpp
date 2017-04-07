#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMenuBar>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>

class MainWindow;

#include "controllerInterface.hpp"
#include "heatmapsurvey.hpp"

/**
 * @brief This class is a widget creating the main window of the software.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ControllerInterface * controller, QWidget *parent = 0);
    void createMenus();
    HeatMapSurvey *heatMapSurvey;
    QWidget * osm;
    ~MainWindow();

private:
    ControllerInterface * controller;
};

#endif // MAINWINDOW_H
