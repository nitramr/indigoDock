#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include "indigopanel.h"
#include "indigodropzone.h"
#include "indigomenubar.h"
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
    dockright = new QDockWidget(this);
    dockright->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
   // dockright->setStyleSheet("background-color: lightgrey");
    this->addDockWidget(Qt::RightDockWidgetArea, dockright);



    /*******************
     *
     * IndigoDock Setup
     *
     ******************/


    // TabWidget
    IndigoDock *indigoDock = new IndigoDock;

    // Container
    mainLayout = new QGridLayout();
    mainLayout->setMargin(0);
    mainLayout->addWidget(indigoDock, 0, 0);
    QWidget *containerRight = new QWidget;
    containerRight->setLayout(mainLayout);

    // set Layouted Widget to DockPanel
    dockright->setWidget(containerRight);

    IndigoMenuBar *menuBar = new IndigoMenuBar();
    setMenuBar(menuBar);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
