#include "indigo2dock.h"

Indigo2Dock::Indigo2Dock(QWidget *parent) : QWidget(parent)
{
    init();

}

void Indigo2Dock::init(){

    // Setup Tabbar
    indigoTab = new Indigo2Tabbar;
    indigoTab->setTabPosition(Indigo2Tabbar::East);
    indigoTab->setMovable(true);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    setLayout(layout);


    layout->addWidget(indigoTab);


    // Demo Content
    QWidget * widget = new QWidget;

    // Demo Tabs
    addTab("Properties", QIcon(":/icons/icons/placeholder.png"),widget);
    addTab("Page", QIcon(":/icons/icons/placeholder.png"),widget);
    addTab("Text", QIcon(":/icons/icons/placeholder.png"),widget);

}

void Indigo2Dock::addTab(const QString &title, QIcon icon, QWidget *widget){
    Indigo2DropZone * dropzone = new Indigo2DropZone(0);
    dropzone->createPanel(title, widget);
    indigoTab->addTab(dropzone, icon, "");

}
