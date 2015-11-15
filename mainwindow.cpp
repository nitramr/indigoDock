#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include "indigopanel.h"
#include "indigodropzone.h"
#include "indigodock.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);

    /*******************
     *
     * QDockWidget Setup
     *
     ******************/

    // add right dock container
    m_dockright = new QDockWidget(this);
    m_dockright->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
   // dockright->setStyleSheet("background-color: lightgrey");
    this->addDockWidget(Qt::RightDockWidgetArea, m_dockright);



    /*******************
     *
     * IndigoDock Setup
     *
     ******************/


    // TabWidget
    IndigoDock *indigoDock = new IndigoDock;

    // Container
    m_mainLayout = new QGridLayout();
    m_mainLayout->setMargin(0);
    m_mainLayout->addWidget(indigoDock, 0, 0);
    QWidget *containerRight = new QWidget;
    containerRight->setLayout(m_mainLayout);

    // set Layouted Widget to DockPanel
    m_dockright->setWidget(containerRight);


}


MainWindow::~MainWindow()
{
    delete ui;
}
