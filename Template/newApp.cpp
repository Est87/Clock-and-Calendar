#include<QDebug>
#include<QIcon>
#include<QPalette>
#include<QPixmap>
#include<QSize>
#include<QVector>
#include "newApp.h"
#include "ui_newApp.h"

//Global Variables (global variables for this app only)
const QString program_name = "Desktop";             //Change "Desktop" to your app name
//start below


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
    QGridLayout *file_layout = new QGridLayout(file_space);
    file_layout->setAlignment(Qt::AlignLeft);
    //here add app name                                             //main content of your app



    ui->main_layout->addWidget(file_space);
    ui->main_layout->addStretch(1);
    //don't add code here

//Connection (set signal and slot)
//    for(int i = 0; i<appname.size(); i++){                                        //don't delete
//        connect(appList[i], &QAction::triggered, this, &newApp::switchApps);
//    }
//    connect(appFeatures[5], &QAction::triggered, this, &newApp::close_app);
    //start below


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





