#include "indigodock.h"

IndigoDock::IndigoDock(QWidget *parent) : QWidget(parent)
{
    init();

}

void IndigoDock::init(){

    // Setup Tabbar
    indigoTab = new IndigoTabbar;
    indigoTab->setTabPosition(IndigoTabbar::East);
    indigoTab->setMovable(true);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    setLayout(layout);


    layout->addWidget(indigoTab);


    // Demo Content
    QWidget * widget = new QWidget;

    // Demo Tabs
    QIcon theIcon = QIcon(":/icons/placeholder.png");
    qDebug() << "is null" << theIcon.isNull();
    qDebug() << "exists" << QFile(":/icons/placeholder.png").exists();
    addTab("Properties", QIcon(":/icons/placeholder.png"),widget);
    addTab("Page", QIcon(":/icons/placeholder.png"),widget);
    addTab("Text", QIcon(":/icons/placeholder.png"),widget);

}

void IndigoDock::addTab(const QString &title, QIcon icon, QWidget *widget){
    IndigoDropZone * dropzone = new IndigoDropZone(0);
    dropzone->createPanel(title, widget);
    indigoTab->addTab(dropzone, icon, "");

}
