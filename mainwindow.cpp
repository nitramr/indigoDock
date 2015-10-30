#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <indigodock.h>
#include <indigotabwidget.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // add right dock container
    dockright = new QDockWidget(this);
    dockright->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
   // dockright->setStyleSheet("background-color: lightgrey");
    this->addDockWidget(Qt::RightDockWidgetArea, dockright);


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


    IndigoDock *indigoContainer = new IndigoDock(0);
    IndigoDock *indigoContainer2 = new IndigoDock(0);
    IndigoDock *indigoContainer3 = new IndigoDock(0);

    indigoTab->addTab(indigoContainer, QIcon(":/icons/icons/placeholder.png"), "");
    indigoTab->addTab(indigoContainer2, QIcon(":/icons/icons/placeholder.png"), "");
    indigoTab->addTab(indigoContainer3, QIcon(":/icons/icons/placeholder.png"), "");


}

MainWindow::~MainWindow()
{
    delete ui;
}
