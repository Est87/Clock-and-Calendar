#ifndef NEWAPP_H
#define NEWAPP_H

#include <QMainWindow>
#include <QMap>
#include <QLCDNumber>
//#include"Global.h"            //don't delete

QT_BEGIN_NAMESPACE
namespace Ui { class newApp; }
QT_END_NAMESPACE

class newApp : public QMainWindow
{
    Q_OBJECT

public:
    newApp(QWidget *parent = nullptr);
    ~newApp();
    //add below

protected:
    void timerEvent(QTimerEvent *event);

private:
    Ui::newApp *ui;
    QVector<QAction*> appFeatures;
    QVector<QAction*> appList;
    void switchApps();
    void close_app();
    //add below
    void stopwatchStart();
    void stopwatchPause();
    void stopwatchReset();
    void updateCountdown();
    void timerStart();
    void timerPause();
    void timerReset();
    void updateTimer();
};

class analogClock : public QWidget
{
    Q_OBJECT

public:
    analogClock(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void showTime();
};

class digitalClock : public QLCDNumber
{
    Q_OBJECT

public:
    digitalClock(QWidget *parent = 0);
private slots:
    void showTime();
};






#endif // NEWAPP_H
