#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include "indigodropzone.h"
#include "indigomenubar.h"
#include "indigodock.h"
#include "indigoexpandergroup.h"

#include "colorswatch.h"
#include "anglepicker.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Style start
    qApp->setStyle(QStyleFactory::create("Fusion"));
    //"Fusion" "Windows". Depending on the platform, "WindowsXP" or "Macintosh" may be available.

    // Style: https://gist.github.com/QuantumCD/6245215

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, Qt::darkGray);
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::darkGray);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette);
    invert = true;
    // Style End



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
    IndigoPanel *pan_page = new IndigoPanel("PanPage", this);
    pan_page->setCaption("Page");
    pan_page->setIcon(iconInvert(QIcon(iconPath + "pan-page.png"), invert));
    indigoDock->addIndigoPanel(pan_page);

    IndigoPanel *pan_image = new IndigoPanel("PanImage", this);
    pan_image->setCaption("Image");
    pan_image->setIcon(iconInvert(QIcon(iconPath + "pan-image.png"), invert));
    indigoDock->addIndigoPanel(pan_image);

    IndigoPanel *pan_text = new IndigoPanel("PanText",this);
    pan_text->setCaption("Text");
    pan_text->setIcon(iconInvert(QIcon(iconPath + "pan-text.png"),invert));
    indigoDock->addIndigoPanel(pan_text);



    // Add panel content
    textPanel(pan_text);
}

QIcon MainWindow::iconInvert(const QIcon &icon, bool invert){

    QSize sz;

    for (int var = 0; var < icon.availableSizes().count(); ++var) {
        if (icon.availableSizes().at(var).width() > sz.width())
        sz = icon.availableSizes().at(var);
    }
    QPixmap pix = icon.pixmap(sz);

    if(invert){
        QImage image = pix.toImage();
        image.invertPixels();
        pix = pix.fromImage(image);
    }

    return pix;

}

void MainWindow::textPanel(IndigoPanel *parent){

    IndigoExpanderGroup *grFont = new IndigoExpanderGroup();
    IndigoExpanderGroup *grAlignment = new IndigoExpanderGroup();
    IndigoExpanderGroup *grStyles = new IndigoExpanderGroup();
    IndigoExpanderGroup *grChars = new IndigoExpanderGroup();
    IndigoExpanderGroup *grParagraph = new IndigoExpanderGroup();
    IndigoExpanderGroup *grLists = new IndigoExpanderGroup();
    IndigoExpanderGroup *grColumns = new IndigoExpanderGroup();

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


    parent->addWidget(grFont);
    parent->addWidget(grAlignment);
    parent->addWidget(grStyles);
    parent->addWidget(grChars);
    parent->addWidget(grParagraph);
    parent->addWidget(grLists);
    parent->addWidget(grColumns);

}


MainWindow::~MainWindow()
{
    delete ui;
}
