//
// Created by leo on 16/03/2017.
//

void launchInterface(){
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

int returnDensityFilter(bool yes=0, bool weak = 1, int percentage){

    return 1;
}

int returnPeriodFilter(int dayBegin, int monthBegin, int yearBegin, int hourBegin, int minuteBegin,
                       int dayEnd, int monthEnd, int yearEnd, int hourEnd, int minuteEnd,
                       bool normal = 1, bool slots[24]){
    return 1;
}

int returnTripsFilter(int maxLength, int minLength, int maxDensity, int minDensity){
    return 1;
}

int returnUsersFilter(bool men, bool women, int minAge, int maxAge, bool subscriber, bool nonSubscriber){

    return 1;
}