#include "indigodock.h"

IndigoDock::IndigoDock(QWidget *parent) : QWidget(parent)
{
    init();

}

void IndigoDock::init(){

    // Setup Tabbar
    m_indigoTab = new IndigoTabbar;
    m_indigoTab->setTabPosition(IndigoTabbar::East);
    m_indigoTab->setMovable(true);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    setLayout(layout);


    layout->addWidget(m_indigoTab);


    // Demo Content
    QWidget * widget = new QWidget;

    // Demo Tabs
    addTab("Properties", QIcon(":/icons/icons/placeholder.png"),widget);
    addTab("Page", QIcon(":/icons/icons/placeholder.png"),widget);
    addTab("Text", QIcon(":/icons/icons/placeholder.png"),widget);

}

void IndigoDock::addTab(const QString &title, QIcon icon, QWidget *widget){
    IndigoDropZone * dropzone = new IndigoDropZone(0);
    dropzone->createPanel(title, widget);
    m_indigoTab->addTab(dropzone, icon, "");

}


