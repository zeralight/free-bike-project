#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMenuBar>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>


#include "heatmapsurvey.hpp"

/*
 * @brief This class is a widget creating the main window of the software.
 */
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
