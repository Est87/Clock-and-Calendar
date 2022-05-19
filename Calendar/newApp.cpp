#include<QDebug>
#include<QIcon>
#include<QPalette>
#include<QPixmap>
#include<QSize>
#include<QVector>
#include <QCalendarWidget>
#include <QGroupBox>
#include <QSizePolicy>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTimeEdit>
#include <QCheckBox>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QMap>
#include <QString>
#include "newApp.h"
#include "ui_newApp.h"

//Global Variables (global variables for this app only)
const QString program_name = "Calendar";             //Change "Desktop" to your app name
//start below
static QLineEdit *eventTitle;
static QTimeEdit *eventTime;
static QTextEdit *eventDetail;
static QListWidget *eventList;
static QCalendarWidget *cal;
static QPushButton *delButton;
static QMultiMap<QDate,QMap<QString,QString>> storeEvent = {
};

newApp::newApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::newApp)
{
    ui->setupUi(this);
//    openedApps[program_name] = this;              //don't delete
//    appname = openedApps.keys();

//Setup (initialization for picture, color, etc)
    QIcon applist_icon(":/img/a.png");
    //start below

//Widgets (initialization for widget)
    //start below
    appFeatures.append(new QAction("Close", this));                 //add features (please modify)

//Widgets setup (set the widget properties)
    //start below
    appFeatures[0]->setStatusTip("Close application");              //set explaination for feature 0 (please modify)

    QMenu *app_list = menuBar()->addMenu("");
    app_list->setIcon(applist_icon);
//    appname = openedApps.keys();                                  //don't delete
//    for(int i = 0; i<appname.size(); i++){
//        appList.append(new QAction(appname[i], this));
//        app_list->addAction(appList[i]);
//    }
    QMenu *app_name = menuBar()->addMenu(program_name);
    //here add app features (e.g. copy, close, etc)
    app_name->addAction(appFeatures[0]);                            //add feature 0 to layout (please modify)


//Layouts (set the display layout)
    QWidget *file_space = new QWidget;
    QHBoxLayout *main = new QHBoxLayout(file_space);
    main->setAlignment(Qt::AlignLeft);
    //here add app name                                             //main content of your app
    cal = new QCalendarWidget;
    cal->setMaximumDate(QDate(2200,1,1));
    cal->setMinimumDate(QDate(1900,1,1));
    cal->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    main->addWidget(cal);

    QVBoxLayout *right = new QVBoxLayout;
    eventList = new QListWidget;
    QLabel *label = new QLabel("Events On Date");
    right->addWidget(label);
    right->addWidget(eventList);
    main->addLayout(right);
    eventList->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QGroupBox *eventForm = new QGroupBox("Event");
    right->addWidget(eventForm);
    QGridLayout *formLayout = new QGridLayout;
    eventForm->setLayout(formLayout);

    eventTitle = new QLineEdit;
    eventTime = new QTimeEdit(QTime(7,0));
    eventDetail = new QTextEdit();
    QPushButton *addButton = new QPushButton("Add / Update");
    delButton = new QPushButton("Delete");

    QLabel *label2 = new QLabel("Note");
    formLayout->addWidget(eventTitle,1,1,1,3);
    formLayout->addWidget(eventTime,2,1);
    formLayout->addWidget(label2,3,1);
    formLayout->addWidget(eventDetail,4,1,1,3);
    formLayout->addWidget(addButton,5,2);
    formLayout->addWidget(delButton,5,3);

    ui->main_layout->addWidget(file_space);
    //don't add code here

//Connection (set signal and slot)
//    for(int i = 0; i<appname.size(); i++){                                        //don't delete
//        connect(appList[i], &QAction::triggered, this, &newApp::switchApps);
//    }
//    connect(appFeatures[5], &QAction::triggered, this, &newApp::close_app);
    //start below
    checkDeleteButton();
    connect(cal,&QCalendarWidget::selectionChanged,this,&newApp::showEvent);
    connect(cal,&QCalendarWidget::selectionChanged,this,&newApp::checkDeleteButton);
    connect(addButton,&QPushButton::clicked,this,&newApp::saveEvent);
    connect(addButton,&QPushButton::clicked,this,&newApp::checkDeleteButton);
    connect(delButton,&QPushButton::clicked,this,&newApp::deleteEvent);
    connect(eventList,&QListWidget::itemSelectionChanged,this,&newApp::checkDeleteButton);
    connect(eventList,&QListWidget::itemPressed,this,&newApp::showDetails);
    connect(eventTitle,&QLineEdit::editingFinished,this,&newApp::clearDetails);
}

newApp::~newApp()
{
    delete ui;
}

void newApp::switchApps(){
    QAction *app = (QAction*) sender();

//    if(openedApps[app->text()] != this){                  //don't delete
//        openedApps[app->text()]->show();
//        this->hide();
//    }
}

void newApp::close_app(){
//    appname.removeOne(program_name);                      //don't delete
//    openedApps.remove(program_name);
    this->close();
}

//add function below
void newApp::clearForm(){
    eventTitle->clear();
    eventTime->setTime(QTime(7,0));
    eventDetail->setPlainText("");
}

void newApp::showEvent(){
    eventList->clear();
    clearForm();
    QDate date = cal->selectedDate();
    QList<QMap<QString,QString>> temp = storeEvent.values(date);
    for(int i=0; i<temp.size(); i++){
        QString title = temp[i].value("Title");
        QString time = temp[i].value("Time");
        QString combined = time + " : " + title;
        eventList->addItem(combined);
    }
}

void newApp::saveEvent(){
    QMap<QString,QString> event = {
      {"Title",eventTitle->text()},
      {"Time",eventTime->time().toString()},
      {"Details",eventDetail->toPlainText()}
    };
    QDate date = cal->selectedDate();
    storeEvent.insert(date,event);
    showEvent();
}

void newApp::deleteEvent(){
    QDate date = cal->selectedDate();
    int row = eventList->currentRow();
    QList<QMap<QString,QString>> temp = storeEvent.values(date);
    QMap<QString,QString> idx = temp[row];
    storeEvent.erase(storeEvent.find(date,idx));
    eventList->setCurrentRow(-1);
    clearForm();
    showEvent();
}

void newApp::showDetails(){
    clearForm();
    QDate date = cal->selectedDate();
    int row = eventList->currentRow();
    if(row == -1){
        return;
    }
    QList<QMap<QString,QString>> temp = storeEvent.values(date);
    QMap<QString,QString> idx = temp[row];
    eventDetail->setPlainText(idx["Details"]);
}

void newApp::clearDetails(){
    eventDetail->setPlainText("");
}

void newApp::checkDeleteButton(){
    delButton->setDisabled(eventList->currentRow()==-1);
}






