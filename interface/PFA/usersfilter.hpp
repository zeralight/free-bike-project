#ifndef USERSFILTER_H
#define USERSFILTER_H

#include <QWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
class UsersFilter : public QWidget
{
    Q_OBJECT
public:
    explicit UsersFilter(QWidget *parent = 0);
    QCheckBox * men;
    QCheckBox * women;
    QSpinBox * minimumAge;
    QSpinBox * maximumAge;
    QCheckBox * subscriber;
    QCheckBox * nonSubscriber;
signals:

public slots:
    void validation();

};

#endif // USERSFILTER_H
