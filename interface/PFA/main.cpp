#include "mainwindow.h"
#include "questionnairechaleur.h"
#include <QApplication>
#include <QTextCodec>
#include "periodfilter.h"

int main(int argc, char *argv[])
{
  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF_8"));
    QApplication a(argc, argv);
    MainWindow window;
    QWidget * mainWidget = new QWidget();
    //QuestionnaireChaleur q;
    //window.setCentralWidget(&q);
    QVBoxLayout * lay = new QVBoxLayout;
    //lay->addWidget(q);
    //w.setLayout(lay);
    PeriodFilter aa;
    window.show();

    return a.exec();
}
