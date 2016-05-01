/*******************************************************
 *
 * Copyright (C) 2016  Martin Reininger
 *
 * This file is part of IndigoDock.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *******************************************************/


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include "indigodock/indigodock.h"

#include "uiwidgets/indigomenubar.h"
#include "uiwidgets/expandergroup.h"
#include "uiwidgets/colorswatch.h"
#include "uiwidgets/anglepicker.h"

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
     * IndigoDock Setup
     *
     ******************/


    // Setup Indigo Hub

    wdg_indigoDockManager = new IndigoDockManager(this);



    wdg_indigoDock_r = new IndigoDock;
    wdg_indigoDock_r->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    this->addDockWidget(Qt::RightDockWidgetArea, wdg_indigoDock_r);

    wdg_indigoDock_l = new IndigoDock;
    wdg_indigoDock_l->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    this->addDockWidget(Qt::LeftDockWidgetArea, wdg_indigoDock_l);


    /* Setup IndigoDocks in Hub */
    wdg_indigoDockManager->addIndigoDock(wdg_indigoDock_r);
    wdg_indigoDockManager->addIndigoDock(wdg_indigoDock_l);



    /*****************
     *
     * Right Dock
     *
     * **************/


    IndigoPanel *pan_content = new IndigoPanel("PanContent",wdg_indigoDock_r);
    pan_content->setCaption("Content");
    pan_content->setIcon(QIcon(str_iconPath + "pan-content.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_content);

    IndigoPanel *pan_alignment = new IndigoPanel("PanAlignment",wdg_indigoDock_r);
    pan_alignment->setCaption("Alignment");
    pan_alignment->setIcon(QIcon(str_iconPath + "pan-alignment.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_alignment);

    IndigoPanel *pan_colours = new IndigoPanel("PanColours",wdg_indigoDock_r);
    pan_colours->setCaption("Colours");
    pan_colours->setIcon(QIcon(str_iconPath + "pan-colour.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_colours);

    IndigoPanel *pan_page = new IndigoPanel("PanPage",wdg_indigoDock_r);
    pan_page->setCaption("Page");
    pan_page->setIcon(QIcon(str_iconPath + "pan-page.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_page);

  /*  IndigoPanel *pan_group = new IndigoPanel("PanGroup",indigoDock_r);
    pan_group->setCaption("Group");
    pan_group->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock_r->addIndigoPanel(pan_group);*/

    IndigoPanel *pan_line = new IndigoPanel("PanLine",wdg_indigoDock_r);
    pan_line->setCaption("Line");
    pan_line->setIcon(QIcon(str_iconPath + "pan-lines.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_line);

    IndigoPanel *pan_transparency = new IndigoPanel("PanTransparency",wdg_indigoDock_r);
    pan_transparency ->setCaption("Transparency");
    pan_transparency ->setIcon(QIcon(str_iconPath + "pan-transparency.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_transparency);

    IndigoPanel *pan_table = new IndigoPanel("PanTable",wdg_indigoDock_r);
    pan_table ->setCaption("Table");
    pan_table ->setIcon(QIcon(str_iconPath + "pan-table.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_table);

    IndigoPanel *pan_layers = new IndigoPanel("PanLayer",wdg_indigoDock_r);
    pan_layers ->setCaption("Layers");
    pan_layers ->setIcon(QIcon(str_iconPath + "pan-layer.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_layers);

    IndigoPanel *pan_outlines = new IndigoPanel("PanOutlines",wdg_indigoDock_r);
    pan_outlines ->setCaption("Outlines");
    pan_outlines ->setIcon(QIcon(str_iconPath + "pan-outline.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_outlines);

   /* IndigoPanel *pan_bookmarks = new IndigoPanel("PanBookmarks",indigoDock_r);
    pan_bookmarks ->setCaption("Bookmarks");
    pan_bookmarks ->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock_r->addIndigoPanel(pan_bookmarks);

    IndigoPanel *pan_scrapbook = new IndigoPanel("PanScrapbook",indigoDock_r);
    pan_scrapbook ->setCaption("Scrapbook");
    pan_scrapbook ->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock_r->addIndigoPanel(pan_scrapbook);

    IndigoPanel *pan_symbols = new IndigoPanel("PanSymbols",indigoDock_r);
    pan_symbols ->setCaption("Symbols");
    pan_symbols ->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock_r->addIndigoPanel(pan_symbols);

    IndigoPanel *pan_inlineitems = new IndigoPanel("PanInlineItems",indigoDock_r);
    pan_inlineitems ->setCaption("Inline Items");
    pan_inlineitems ->setIcon(QIcon(str_iconPath + "pan-image.png"));
    indigoDock_r->addIndigoPanel(pan_inlineitems);*/



    /*****************
     *
     * Left Dock
     *
     * **************/


    IndigoPanel *pan_test = new IndigoPanel("PanTest",wdg_indigoDock_l);
    pan_test ->setCaption("Test");
    pan_test ->setIcon(QIcon(str_iconPath + "pan-image.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_l,pan_test );

    IndigoPanel *pan_geometry = new IndigoPanel("PanGeometry",wdg_indigoDock_l);
    pan_geometry ->setCaption("Geometry");
    pan_geometry ->setIcon(QIcon(str_iconPath + "pan-frame.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_l,pan_geometry);




    /******************
     *
     * Add Panel Content
     *
     * ***************/


    textPanel(pan_content);





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


    /******************
     *
     * Document simulator
     *
     * ***************/



    wdg_textbox = new TextBoxSimulator;

    connect(wdg_textbox, SIGNAL(mousePressed()), pan_geometry, SLOT(show()));
    connect(wdg_textbox, SIGNAL(mousePressed()), this, SLOT(scrollToGeometry()));
    connect(wdg_textbox, SIGNAL(mouseDoubleClick()), pan_content, SLOT(show()));
    connect(wdg_textbox, SIGNAL(mouseDoubleClick()), this, SLOT(scrollToContent()));


    QHBoxLayout *lyt_tbsim = new QHBoxLayout();
    lyt_tbsim->setMargin(20);
    lyt_tbsim->addWidget(wdg_textbox);

    wdg_document = new QWidget;
    wdg_document->setAutoFillBackground(true);
    wdg_document->setBackgroundRole(QPalette::Light);
    wdg_document->setLayout(lyt_tbsim);
    this->setCentralWidget(wdg_document);

}


// Auto scroll event calls by panel names

void MainWindow::scrollToGeometry(){
    wdg_indigoDockManager->scrollToPanel("PanGeometry");
}



void MainWindow::scrollToContent(){
    wdg_indigoDockManager->scrollToPanel("PanContent");
}



void MainWindow::scrollToPage(){
    wdg_indigoDockManager->scrollToPanel("PanPage");
}



MainWindow::~MainWindow()
{
    delete ui;
}

/*********************************
 *
 * Set Content of IndigoPanel
 *
 * ******************************/

void MainWindow::textPanel(IndigoPanel *parent){

    /*IndigoExpanderGroup *grFont = new IndigoExpanderGroup();
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
     QWidget * spacer = new QWidget();
    QVBoxLayout *layoutSpacer = new QVBoxLayout();
    layoutSpacer->addStretch(1);
    spacer->setLayout(layoutSpacer);*


    parent->addWidgetNormal(grFont);
    parent->addWidgetNormal(grAlignment);
    parent->addWidgetNormal(grStyles);
    parent->addWidgetNormal(grChars);
    parent->addWidgetNormal(grParagraph);
    parent->addWidgetNormal(grLists);
    parent->addWidgetNormal(grColumns);
    //parent->addWidgetNormal(spacer);*/


   /* IndigoLabelControl *ilcTest = new IndigoLabelControl();
    ilcTest->setLabel(QIcon(str_iconPath + "pan-image.png"));
    QLineEdit *textBox = new QLineEdit("Icon Test");
    ilcTest->setWidget(textBox);
    parent->addWidgetNormal(ilcTest);


    IndigoLabelControl *ilcTest2 = new IndigoLabelControl();
    ilcTest2->setLabel("b:");
    QLineEdit *textBox2 = new QLineEdit("String Test");
    ilcTest2->setWidget(textBox2);
    parent->addWidgetNormal(ilcTest2);


    IndigoLabelControl *ilcTest4 = new IndigoLabelControl();
    ilcTest4->setLabel(QIcon(str_iconPath + "pan-image.png"));
    QLineEdit *textBox4 = new QLineEdit("Col left");
    ilcTest4->setWidget(textBox4);
    IndigoLabelControl *ilcTest5 = new IndigoLabelControl();
    ilcTest5->setLabel(QIcon(str_iconPath + "pan-image.png"));
    QLineEdit *textBox5 = new QLineEdit("Col right");
    ilcTest5->setWidget(textBox5);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(ilcTest4);
    hbox->addWidget(ilcTest5);
    hbox->setMargin(0);
    parent->addWidgetNormal(hbox);


    ColorSwatch * cPicker = new ColorSwatch();
    IndigoLabelControl *ilcTest6 = new IndigoLabelControl();
    ilcTest6->setLabel("Rect Colour:", 100);
    ilcTest6->setWidget(cPicker, cPicker->width());
    parent->addWidgetNormal(ilcTest6);*/





    IconWidget *wdg_icon = new IconWidget(str_iconPath + "pan-image.png", 22);

    QLineEdit *textBox = new QLineEdit("Icon Test");
    QLineEdit *textBox2 = new QLineEdit("135 °");
    AnglePicker * aPicker = new AnglePicker(135);


    QFormLayout *qfl1 = new QFormLayout();
    qfl1->setMargin(0);
    qfl1->addRow( wdg_icon, textBox );
    qfl1->addRow( aPicker, textBox2 );


    parent->addWidgetNormal(qfl1);

}





/*************************
 *
 * Theme handling
 *
 * **********************/


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
