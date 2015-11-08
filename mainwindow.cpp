#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <indigodropzone.h>
#include <indigotabwidget.h>
#include <indigo2panel.h>
#include <indigo2dropzone.h>
#include <indigo2dock.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);



    // add right dock container
    dockright = new QDockWidget(this);
    dockright->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
   // dockright->setStyleSheet("background-color: lightgrey");
    this->addDockWidget(Qt::RightDockWidgetArea, dockright);


    /*******************
     *
     * Version 1 based on standard widgets
     *
     ******************/

/*
    // TabWidget
    IndigoTabWidget *indigoTab = new IndigoTabWidget;
    indigoTab->setTabPosition(IndigoTabWidget::East);
    indigoTab->setMovable(true);

    // Container
    mainLayout = new QGridLayout();
    mainLayout->addWidget(indigoTab, 0, 0);
    QWidget *containerRight = new QWidget;
    containerRight->setLayout(mainLayout);

    // set Layouted Widget to DockPanel
    dockright->setWidget(containerRight);


    IndigoDropZone *indigoContainer = new IndigoDropZone(0);
    IndigoDropZone *indigoContainer2 = new IndigoDropZone(0);
    IndigoDropZone *indigoContainer3 = new IndigoDropZone(0);

    //Indigo2DropZone *indigoContainer = new Indigo2DropZone(0);
    //Indigo2DropZone *indigoContainer2 = new Indigo2DropZone(0);
    //Indigo2DropZone *indigoContainer3 = new Indigo2DropZone(0);



    indigoTab->addTab(indigoContainer, QIcon(":/icons/icons/placeholder.png"), "");
    indigoTab->addTab(indigoContainer2, QIcon(":/icons/icons/placeholder.png"), "");
    indigoTab->addTab(indigoContainer3, QIcon(":/icons/icons/placeholder.png"), "");
*/



    /*******************
     *
     * Version 2 based on custom widgets
     *
     ******************/


    // TabWidget
    Indigo2Dock *indigoDock = new Indigo2Dock;

    // Container
    mainLayout = new QGridLayout();
    mainLayout->setMargin(0);
    mainLayout->addWidget(indigoDock, 0, 0);
    QWidget *containerRight = new QWidget;
    containerRight->setLayout(mainLayout);

    // set Layouted Widget to DockPanel
    dockright->setWidget(containerRight);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
        emit close(true);
        event->accept();
}
