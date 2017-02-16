#ifndef PERIODFILTER_H
#define PERIODFILTER_H

#include <QWidget>
#include <QDateTimeEdit>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
class PeriodFilter : public QWidget
{
    Q_OBJECT
public:
    explicit PeriodFilter(QWidget *parent = 0);
    QDateTimeEdit * beginning;
    QDateTimeEdit * end;
    QRadioButton * normal;
    QRadioButton * slot;
    QLabel * toImplement;
signals:

public slots:
    void validation();
};

#endif // PERIODFILTER_H
