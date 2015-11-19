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
    m_dockright = new QDockWidget(this);
    m_dockright->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
   // dockright->setStyleSheet("background-color: lightgrey");
    this->addDockWidget(Qt::RightDockWidgetArea, m_dockright);

    // add left dock container
    m_dockleft = new QDockWidget(this);
    m_dockleft->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
   // dockright->setStyleSheet("background-color: lightgrey");
    this->addDockWidget(Qt::LeftDockWidgetArea, m_dockleft);



    /*******************
     *
     * IndigoDock Setup
     *
     ******************/


    // TabWidget
    IndigoDock *indigoDock_r = new IndigoDock;


    // Container
    m_mainLayout_r = new QGridLayout();
    m_mainLayout_r->setMargin(0);
    m_mainLayout_r->addWidget(indigoDock_r, 0, 0);
    QWidget *containerRight = new QWidget;
    containerRight->setLayout(m_mainLayout_r);

    // set Layouted Widget to DockPanel
    m_dockright->setWidget(containerRight);
    connect(m_dockright, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), indigoDock_r, SLOT(updateTabWidget(Qt::DockWidgetArea)));



    // TabWidget
    IndigoDock *indigoDock_l = new IndigoDock;
    indigoDock_l->m_indigoTab->setTabPosition(IndigoTabbar::West);

    // Container
    m_mainLayout_l = new QGridLayout();
    m_mainLayout_l->setMargin(0);
    m_mainLayout_l->addWidget(indigoDock_l, 0, 0);
    QWidget *containerLeft = new QWidget;
    containerLeft->setLayout(m_mainLayout_l);

    // set Layouted Widget to DockPanel
    m_dockleft->setWidget(containerLeft);
    connect(m_dockleft, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), indigoDock_l, SLOT(updateTabWidget(Qt::DockWidgetArea)));



    IndigoMenuBar *menuBar = new IndigoMenuBar();
    setMenuBar(menuBar);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
 
    // right dock
    IndigoPanel *panel = new IndigoPanel(this);
    panel->setCaption("Properties");
    panel->setIcon(QIcon(":/icons/icons/placeholder.png"));
    indigoDock_r->addIndigoPanel(panel);

    IndigoPanel *panel2 = new IndigoPanel(this);
    panel2->setCaption("Page");
    panel2->setIcon(QIcon(":/icons/icons/placeholder.png"));
    indigoDock_r->addIndigoPanel(panel2, 0);


    // left dock
    IndigoPanel *panel3 = new IndigoPanel(this);
    panel3->setCaption("Preflight");
    panel3->setIcon(QIcon(":/icons/icons/placeholder.png"));
    indigoDock_l->addIndigoPanel(panel3);

    IndigoPanel *panel4 = new IndigoPanel(this);
    panel4->setCaption("Text");
    panel4->setIcon(QIcon(":/icons/icons/placeholder.png"));
    indigoDock_l->addIndigoPanel(panel4);
}


MainWindow::~MainWindow()
{
    delete ui;
}
