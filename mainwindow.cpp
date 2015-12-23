#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include "indigodropzone.h"
#include "indigomenubar.h"
#include "indigodock.h"
#include "indigoexpandergroup.h"

#include "colorswatch.h"
#include "anglepicker.h"
#include "stylefactory.h"
#include "configmanager.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qApp->setStyle(QStyleFactory::create("Fusion"));

    loadTheme();



    setMouseTracking(true);

    IndigoMenuBar *menuBar = new IndigoMenuBar();
    menuBar->setNativeMenuBar(true);
    setMenuBar(menuBar);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));

    /******************
     *
     * toolBar
     *
     * ***************/

    //ui->mainToolBar->addAction("Light");

    QAction *tb_light = new QAction("Light",this);
    ui->mainToolBar->addAction(tb_light);
    connect(tb_light, SIGNAL(triggered()), this, SLOT(loadLightTheme()));

    QAction *tb_dark = new QAction("Dark",this);
    ui->mainToolBar->addAction(tb_dark);
    connect(tb_dark, SIGNAL(triggered()), this, SLOT(loadDarkTheme()));


    /*******************
     *
     * QDockWidget Setup
     *
     ******************/

    // add right dock container
    m_dockright = new QDockWidget(this);
    m_dockright->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    this->addDockWidget(Qt::RightDockWidgetArea, m_dockright);


    /*******************
     *
     * IndigoDock Setup
     *
     ******************/


    // TabWidget
    IndigoDock *indigoDock = new IndigoDock;

    // Container
    m_mainLayout_r = new QGridLayout();
    m_mainLayout_r->setMargin(0);
    m_mainLayout_r->addWidget(indigoDock, 0, 0);
    QWidget *containerRight = new QWidget;
    containerRight->setLayout(m_mainLayout_r);

    // set Layouted Widget to DockPanel
    m_dockright->setWidget(containerRight);
    connect(m_dockright, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), indigoDock, SLOT(updateTabPosition(Qt::DockWidgetArea)));


    // Panel Setup
    IndigoPanel *pan_page = new IndigoPanel("PanPage",indigoDock);
    pan_page->setCaption("Page");
    pan_page->setIcon(QIcon(str_iconPath + "pan-page.png"));
    indigoDock->addIndigoPanel(pan_page);

    IndigoPanel *pan_image = new IndigoPanel("PanImage",indigoDock);
    pan_image->setCaption("Image");
    pan_image->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_image);

    IndigoPanel *pan_text = new IndigoPanel("PanText", indigoDock);
    pan_text->setCaption("Text");
    pan_text->setIcon(QIcon(str_iconPath + "pan-text.png"));
    indigoDock->addIndigoPanel(pan_text);



    // Add panel content
    textPanel(pan_text);

    QLabel *lbl1 = new QLabel("Image stuff normal");
    QLabel *lbl3 = new QLabel("Image stuff extended");
    pan_image->addWidgetNormal(lbl1);
    pan_image->addWidgetExtend(lbl3);

    QLabel *lbl2 = new QLabel("Page stuff extended");
    pan_page->addWidgetExtend(lbl2);
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::textPanel(IndigoPanel *parent){

    IndigoExpanderGroup *grFont = new IndigoExpanderGroup();
    IndigoExpanderGroup *grAlignment = new IndigoExpanderGroup(false);
    IndigoExpanderGroup *grStyles = new IndigoExpanderGroup(false);
    IndigoExpanderGroup *grChars = new IndigoExpanderGroup(false);
    IndigoExpanderGroup *grParagraph = new IndigoExpanderGroup(false);
    IndigoExpanderGroup *grLists = new IndigoExpanderGroup(false);
    IndigoExpanderGroup *grColumns = new IndigoExpanderGroup(false);

    grFont->setCaption("Font");
    grAlignment->setCaption("Alignment");
    grStyles->setCaption("Styles");
    grChars->setCaption("Character");
    grParagraph->setCaption("Paragraph");
    grLists->setCaption("Lists & Effects");
    grColumns->setCaption("Columns & Distances");

    // Font
    QComboBox *comboFont = new QComboBox(0);
    comboFont->addItem("Ubuntu");

    AnglePicker * anglePicker = new AnglePicker();
    ColorSwatch * colorSwatch = new ColorSwatch();


    QHBoxLayout *layoutFont = new QHBoxLayout();
    layoutFont->addWidget(comboFont);


    grFont->addWidget(comboFont);
    grAlignment->addWidget(anglePicker);
    grStyles->addWidget(colorSwatch);


    parent->addWidgetNormal(grFont);
    parent->addWidgetNormal(grAlignment);
    parent->addWidgetNormal(grStyles);
    parent->addWidgetNormal(grChars);
    parent->addWidgetNormal(grParagraph);
    parent->addWidgetNormal(grLists);
    parent->addWidgetNormal(grColumns);

}



void MainWindow::loadTheme(){

    ConfigManager *fm = new ConfigManager();

    str_iconPath = fm->getIconPath();

    QFile f(fm->getThemePath());

    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);

        QString style = ts.readAll();

        StyleFactory *sf = new StyleFactory();
        sf->parseString(style);

        qApp->setPalette(sf->palette());
        qApp->setStyleSheet(style);



    }
}



void MainWindow::saveTheme(Theme theme){

    ConfigManager *cm = new ConfigManager();

    switch(theme){
        case Dark:
            cm->setIconPath(":/data/icons/dark/");
            cm->setThemePath(":/data/qss/scribus-dark.qss");
            break;
        case Light:
            cm->setIconPath(":/data/icons/light/");
            cm->setThemePath(":/data/qss/scribus-light.qss");
            break;
    }

}


void MainWindow::loadDarkTheme(){
    saveTheme(MainWindow::Dark);
    loadTheme();
}

void MainWindow::loadLightTheme(){
    saveTheme(MainWindow::Light);
    loadTheme();
}
