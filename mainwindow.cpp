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
#include "uiwidgets/flowlayout.h"

#include "stylefactory.h"
#include "configmanager.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

#ifdef Q_OS_MAC
    qDebug() << "detect Mac OSX" << endl;
#else

    qDebug() << "detect non Mac OS" << endl;
#endif


    ui->setupUi(this);

    qApp->setStyle(QStyleFactory::create("Fusion"));

    loadTheme();


    IndigoMenuBar *menuBar = new IndigoMenuBar();
    menuBar->setNativeMenuBar(true);

    setMenuBar(menuBar);
    setMouseTracking(true);
    setDockOptions(AllowNestedDocks|AnimatedDocks);




    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));


    /*******************
     *
     * IndigoDock Setup
     *
     ******************/

    wdg_indigoDock_r = new IndigoDock();

    // Setup IndigoDockManager

    wdg_indigoDockManager = new IndigoDockManager(this);
    wdg_indigoDockManager->setMinimumPanelSize(QSize(180,100));
    wdg_indigoDockManager->addIndigoDock(wdg_indigoDock_r, Qt::RightDockWidgetArea );


    /*****************
     *
     * Right Dock
     *
     * **************/


    IndigoPanel *pan_content = new IndigoPanel("Content",QIcon(str_iconPath + "pan-content.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r, pan_content);

    IndigoPanel *pan_alignment = new IndigoPanel("Alignment",QIcon(str_iconPath + "pan-alignment.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_alignment);

    IndigoPanel *pan_colours = new IndigoPanel("Colours",QIcon(str_iconPath + "pan-colour.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_colours);

    IndigoPanel *pan_page = new IndigoPanel("Page",QIcon(str_iconPath + "pan-page.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_page);

    IndigoPanel *pan_group = new IndigoPanel("Groups",QIcon(str_iconPath + "pan-image.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_group);

    IndigoPanel *pan_line = new IndigoPanel("Line",QIcon(str_iconPath + "pan-lines.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_line);

    IndigoPanel *pan_transparency = new IndigoPanel("Transparency",QIcon(str_iconPath + "pan-transparency.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_transparency);

    IndigoPanel *pan_table = new IndigoPanel("Table",QIcon(str_iconPath + "pan-table.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_table);

    IndigoPanel *pan_layers = new IndigoPanel("Layer", QIcon(str_iconPath + "pan-layer.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_layers);

    IndigoPanel *pan_outlines = new IndigoPanel("Outlines",QIcon(str_iconPath + "pan-outline.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_outlines);

     IndigoPanel *pan_bookmarks = new IndigoPanel("Bookmarks",QIcon(str_iconPath + "pan-image.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_bookmarks);

    IndigoPanel *pan_scrapbook = new IndigoPanel("Scrapbook",QIcon(str_iconPath + "pan-image.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_scrapbook);

    IndigoPanel *pan_symbols = new IndigoPanel("Symbols",QIcon(str_iconPath + "pan-image.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_symbols);

    IndigoPanel *pan_inlineitems = new IndigoPanel("Inline Items",QIcon(str_iconPath + "pan-image.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_inlineitems);


    IndigoPanel *pan_test = new IndigoPanel("Test",QIcon(str_iconPath + "pan-image.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_test );

    IndigoPanel *pan_geometry = new IndigoPanel("Geometry",QIcon(str_iconPath + "pan-frame.png"));
    wdg_indigoDockManager->addIndigoPanel(wdg_indigoDock_r,pan_geometry);




    /******************
     *
     * Add Panel Content
     *
     * ***************/


    textPanel(pan_content);

    fluidPanel(pan_geometry);





    /******************
     *
     * toolBar
     *
     * ***************/

    QAction *tb_light = new QAction("Light",this);
    ui->mainToolBar->addAction(tb_light);
    connect(tb_light, SIGNAL(triggered()), this, SLOT(loadLightTheme()));

    QAction *tb_dark = new QAction("Dark",this);
    ui->mainToolBar->addAction(tb_dark);
    connect(tb_dark, SIGNAL(triggered()), this, SLOT(loadDarkTheme()));

    ui->mainToolBar->addSeparator();


    QAction *tb_img = new QAction("Geometry",this);
    ui->mainToolBar->addAction(tb_img);
    connect(tb_img, SIGNAL(triggered()), this, SLOT(scrollToGeometry()));

    QAction *tb_text = new QAction("Content",this);
    ui->mainToolBar->addAction(tb_text);
    connect(tb_text, SIGNAL(triggered()), this, SLOT(scrollToContent()));


    QAction *tb_page = new QAction("Page",this);
    ui->mainToolBar->addAction(tb_page);
    connect(tb_page, SIGNAL(triggered()), this, SLOT(scrollToPage()));

    ui->mainToolBar->addSeparator();

    QAction *tb_loadWS = new QAction("Load Workspace",this);
    ui->mainToolBar->addAction(tb_loadWS);
    connect(tb_loadWS, SIGNAL(triggered()), this, SLOT(loadWorkspace()));

    QAction *tb_saveWS = new QAction("Save Workspace",this);
    ui->mainToolBar->addAction(tb_saveWS);
    connect(tb_saveWS, SIGNAL(triggered()), this, SLOT(saveWorkspace()));



    QAction *tb_tool1 = new QAction(QIcon(str_iconPath + "pan-image.png"), "Tool",this);
    ui->toolBar->addAction(tb_tool1);

    QAction *tb_tool2 = new QAction(QIcon(str_iconPath + "pan-image.png"), "Tool",this);
    ui->toolBar->addAction(tb_tool2);

    QAction *tb_tool3 = new QAction(QIcon(str_iconPath + "pan-image.png"), "Tool",this);
    ui->toolBar->addAction(tb_tool3);

    QAction *tb_tool4 = new QAction(QIcon(str_iconPath + "pan-image.png"), "Tool",this);
    ui->toolBar->addAction(tb_tool4);

    QAction *tb_tool5 = new QAction(QIcon(str_iconPath + "pan-image.png"), "Tool",this);
    ui->toolBar->addAction(tb_tool5);

    QAction *tb_tool6 = new QAction(QIcon(str_iconPath + "pan-image.png"), "Tool",this);
    ui->toolBar->addAction(tb_tool6);

    QAction *tb_tool7 = new QAction(QIcon(str_iconPath + "pan-image.png"), "Tool",this);
    ui->toolBar->addAction(tb_tool7);

    QAction *tb_tool8 = new QAction(QIcon(str_iconPath + "pan-image.png"), "Tool",this);
    ui->toolBar->addAction(tb_tool8);


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


    QScrollArea * documentScroll = new QScrollArea();
    documentScroll->setWidget(wdg_textbox);
    documentScroll->setAlignment(Qt::AlignCenter);
    //documentScroll->setWidgetResizable(true);

    QHBoxLayout *lyt_tbsim = new QHBoxLayout();
    lyt_tbsim->setContentsMargins(20,20,0,0);
    lyt_tbsim->addWidget(documentScroll);



    wdg_document = new QWidget;
    wdg_document->setAutoFillBackground(true);
    wdg_document->setBackgroundRole(QPalette::Dark);
    wdg_document->setLayout(lyt_tbsim);
    this->setCentralWidget(wdg_document);

}


// Auto scroll event calls by panel names

void MainWindow::scrollToGeometry(){
    wdg_indigoDockManager->scrollToPanel("Geometry");
}



void MainWindow::scrollToContent(){
    wdg_indigoDockManager->scrollToPanel("Content");
}



void MainWindow::scrollToPage(){
    wdg_indigoDockManager->scrollToPanel("Page");
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


    IconWidget *wdg_icon = new IconWidget(str_iconPath + "pan-image.png", 22);

    QLineEdit *textBox = new QLineEdit("Icon Test");
    QLineEdit *textBox2 = new QLineEdit("135 °");
    QTextEdit *textEdit1 = new QTextEdit("Example");
    AnglePicker * aPicker = new AnglePicker(135);
    QLabel * lbl_ext1 = new QLabel("Extended Features 1");
    QLabel * lbl_ext2 = new QLabel("Extended Features 2");
    lbl_ext1->hide();
    lbl_ext2->hide();

    QFormLayout *qfl1 = new QFormLayout();
    qfl1->setMargin(0);
    qfl1->addRow( lbl_ext1 );
    qfl1->addRow( wdg_icon, textBox );
    qfl1->addRow( aPicker, textBox2 );
    qfl1->addRow( lbl_ext2 );
    qfl1->addRow( textEdit1 );

    parent->addWidget(qfl1);

    connect(parent, SIGNAL(isAdvanced()), lbl_ext1, SLOT(show()));
    connect(parent, SIGNAL(isNormal()), lbl_ext1, SLOT(hide()));
    connect(parent, SIGNAL(isAdvanced()), lbl_ext2, SLOT(show()));
    connect(parent, SIGNAL(isNormal()), lbl_ext2, SLOT(hide()));

}



void MainWindow::fluidPanel(IndigoPanel *panel){


    QLineEdit * edit1 = new QLineEdit();
    QLineEdit * edit2 = new QLineEdit();
    QLineEdit * edit3 = new QLineEdit();
    QLineEdit * edit4 = new QLineEdit();
    QLineEdit * edit5 = new QLineEdit();


    QBoxLayout * lyt_1 = new QBoxLayout(QBoxLayout::TopToBottom);
    lyt_1->setMargin(0);
    lyt_1->addWidget(edit1);
    lyt_1->addWidget(edit2);

    QBoxLayout * lyt_2 = new QBoxLayout(QBoxLayout::TopToBottom);
    lyt_2->setMargin(0);
    lyt_2->addWidget(edit3);

    QBoxLayout * lyt_3 = new QBoxLayout(QBoxLayout::TopToBottom);
    lyt_3->setMargin(0);
    lyt_3->addWidget(edit4);
    lyt_3->addWidget(edit5);


    QWidget * box1 = new QWidget();
    box1->setLayout(lyt_1);

    QWidget * box2 = new QWidget();
    box2->setLayout(lyt_2);

    QWidget * box3 = new QWidget();
    box3->setLayout(lyt_3);


   /* FlowLayout *flowLayout = new FlowLayout(0,2,2);
    flowLayout->setContentsMargins(0,0,0,0);
    flowLayout->setMargin(0);


    flowLayout->addWidget(box1);
    flowLayout->addWidget(box2);
    flowLayout->addWidget(box3);
    flowLayout->addWidget(new QPushButton(tr("Short")));
    flowLayout->addWidget(new QPushButton(tr("Even longer button text")));

    panel->addWidget(flowLayout);*/


    panel->addWidget(box1);
    panel->addWidget(box2);
    panel->addWidget(box3);
    panel->addWidget(new QPushButton(tr("Short")));
    panel->addWidget(new QPushButton(tr("Even longer button text")));


}




/*************************
 *
 * Theme handling
 *
 * **********************/


void MainWindow::loadTheme(){

    ConfigManager *cm = new ConfigManager();

    str_iconPath = cm->getIconPath();

    QFile f(cm->getThemePath());

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



void MainWindow::loadWorkspace(){

    QString m_sSettingsFile = QApplication::applicationDirPath() + "/workspace.ini";
    QSettings settings(m_sSettingsFile, QSettings::IniFormat);


    settings.beginGroup("IndigoDock");
    wdg_indigoDockManager->loadWorkspace(settings.value("Panels").toByteArray());
    settings.endGroup();

    settings.beginGroup("Main");
   // restoreGeometry(settings.value("Geometry").toByteArray());
    restoreState(settings.value("State").toByteArray());
    settings.endGroup();

}



void MainWindow::saveWorkspace(){


    QString m_sSettingsFile = QApplication::applicationDirPath() + "/workspace.ini";  
    QSettings settings(m_sSettingsFile, QSettings::IniFormat);


    settings.beginGroup("Main");
   // settings.setValue("Geometry", saveGeometry());
    settings.setValue("State", saveState());
    settings.endGroup();

    settings.beginGroup("IndigoDock");
    settings.setValue("Panels", wdg_indigoDockManager->saveWorkspace());
    settings.endGroup();

}

