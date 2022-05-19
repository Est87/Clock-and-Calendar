#ifndef NEWAPP_H
#define NEWAPP_H

#include <QMainWindow>
#include <QMap>
#include <QWidget>
#include <QLineEdit>
#include <QTimeEdit>
#include <QTextEdit>
#include <QPushButton>
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


private:
    Ui::newApp *ui;
    QVector<QAction*> appFeatures;
    QVector<QAction*> appList;
    void switchApps();
    void close_app();
    void clearForm();
    void saveEvent();
    void showEvent();
    void deleteEvent();
    void checkDeleteButton();
    void showDetails();
    void clearDetails();
    //add below


};
#endif // NEWAPP_H
