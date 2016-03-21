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
    indigoDock = new IndigoDock;

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
    IndigoPanel *pan_geometry = new IndigoPanel("PanGeometry",indigoDock);
    pan_geometry ->setCaption("Geometry");
    pan_geometry ->setIcon(QIcon(str_iconPath + "pan-frame.png"));
    indigoDock->addIndigoPanel(pan_geometry );

    IndigoPanel *pan_content = new IndigoPanel("PanContent",indigoDock);
    pan_content->setCaption("Content");
    pan_content->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_content);

    IndigoPanel *pan_alignment = new IndigoPanel("PanAlignment",indigoDock);
    pan_alignment->setCaption("Alignment");
    pan_alignment->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_alignment);

    IndigoPanel *pan_colours = new IndigoPanel("PanColours",indigoDock);
    pan_colours->setCaption("Colours");
    pan_colours->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_colours);

    IndigoPanel *pan_page = new IndigoPanel("PanPage",indigoDock);
    pan_page->setCaption("Page");
    pan_page->setIcon(QIcon(str_iconPath + "pan-page.png"));
    indigoDock->addIndigoPanel(pan_page);

    IndigoPanel *pan_group = new IndigoPanel("PanGroup",indigoDock);
    pan_group->setCaption("Group");
    pan_group->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_group);

    IndigoPanel *pan_line = new IndigoPanel("PanLine",indigoDock);
    pan_line->setCaption("Line");
    pan_line->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_line);

    IndigoPanel *pan_transparency = new IndigoPanel("PanTransparency",indigoDock);
    pan_transparency ->setCaption("Transparency");
    pan_transparency ->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_transparency);

    IndigoPanel *pan_table = new IndigoPanel("PanTable",indigoDock);
    pan_table ->setCaption("Table");
    pan_table ->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_table);

    IndigoPanel *pan_layers = new IndigoPanel("PanLayer",indigoDock);
    pan_layers ->setCaption("Layers");
    pan_layers ->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_layers);

    IndigoPanel *pan_outlines = new IndigoPanel("PanOutlines",indigoDock);
    pan_outlines ->setCaption("Outlines");
    pan_outlines ->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_outlines);

    IndigoPanel *pan_bookmarks = new IndigoPanel("PanBookmarks",indigoDock);
    pan_bookmarks ->setCaption("Bookmarks");
    pan_bookmarks ->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_bookmarks);

    IndigoPanel *pan_scrapbook = new IndigoPanel("PanScrapbook",indigoDock);
    pan_scrapbook ->setCaption("Scrapbook");
    pan_scrapbook ->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_scrapbook);

    IndigoPanel *pan_symbols = new IndigoPanel("PanSymbols",indigoDock);
    pan_symbols ->setCaption("Symbols");
    pan_symbols ->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_symbols);

    IndigoPanel *pan_inlineitems = new IndigoPanel("PanInlineItems",indigoDock);
    pan_inlineitems ->setCaption("Inline Items");
    pan_inlineitems ->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock->addIndigoPanel(pan_inlineitems);




    // Add panel content
    textPanel(pan_content);

   /* QLabel *lbl1 = new QLabel("Image stuff normal");
    QLabel *lbl3 = new QLabel("Image stuff extended");
    pan_group->addWidgetNormal(lbl1);
    pan_group->addWidgetExtend(lbl3);

    QLabel *lbl2 = new QLabel("Page stuff extended");
    pan_page->addWidgetExtend(lbl2);*/


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

    ui->mainToolBar->addSeparator();


    QAction *tb_img = new QAction("Geometry",this);
    ui->mainToolBar->addAction(tb_img);
    connect(tb_img, SIGNAL(triggered()), pan_geometry, SLOT(show()));
    connect(tb_img, SIGNAL(triggered()), this, SLOT(scrollToGeometry()));

    QAction *tb_text = new QAction("Content",this);
    ui->mainToolBar->addAction(tb_text);
    connect(tb_text, SIGNAL(triggered()), pan_content, SLOT(show()));
    connect(tb_text, SIGNAL(triggered()), this, SLOT(scrollToContent()));


    QAction *tb_page = new QAction("Page",this);
    ui->mainToolBar->addAction(tb_page);
    connect(tb_page, SIGNAL(triggered()), pan_page, SLOT(show()));
    connect(tb_page, SIGNAL(triggered()), this, SLOT(scrollToPage()));

}


void MainWindow::scrollToGeometry(){
    indigoDock->scrollToPanel("PanGeometry");
}

void MainWindow::scrollToContent(){
    indigoDock->scrollToPanel("PanContent");
}

void MainWindow::scrollToPage(){
    indigoDock->scrollToPanel("PanPage");
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::textPanel(IndigoPanel *parent){

    IndigoExpanderGroup *grFont = new IndigoExpanderGroup();
    IndigoExpanderGroup *grAlignment = new IndigoExpanderGroup();
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

    grFont->addWidget(comboFont);
    grAlignment->addWidget(anglePicker);
    grStyles->addWidget(colorSwatch);

    // Spacer
    /* QWidget * spacer = new QWidget();
    QVBoxLayout *layoutSpacer = new QVBoxLayout();
    layoutSpacer->addStretch(1);
    spacer->setLayout(layoutSpacer);*/


    parent->addWidgetNormal(grFont);
    parent->addWidgetNormal(grAlignment);
    parent->addWidgetNormal(grStyles);
    parent->addWidgetNormal(grChars);
    parent->addWidgetNormal(grParagraph);
    parent->addWidgetNormal(grLists);
    parent->addWidgetNormal(grColumns);
    //parent->addWidgetNormal(spacer);

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
