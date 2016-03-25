#include "indigolabelcontrol.h"

IndigoLabelControl::IndigoLabelControl(QWidget *parent)
    : QWidget(parent)
{
    setAutoFillBackground( true );
    m_widget = NULL;
    m_label = NULL;

    int padding = 5;

    m_labelLayout = new QHBoxLayout();
    m_labelLayout->setContentsMargins(0,0,padding,0);

    m_widgetLayout = new QHBoxLayout();
    m_widgetLayout->setMargin(0);

    QHBoxLayout * mainLayout = new QHBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    mainLayout->addLayout(m_labelLayout);
    mainLayout->addLayout(m_widgetLayout);


}



void IndigoLabelControl::setWidget(QWidget *widget, int width/*, Qt::Alignment alignment*/){

    if(!m_widget)
        m_widgetLayout->removeWidget(m_widget);

    m_widget = widget;

    if(width > -1)
        m_widget->setFixedWidth(width);

    m_widgetLayout->addWidget(m_widget);
   // m_widgetLayout->setAlignment(m_widget, alignment);
}



QWidget* IndigoLabelControl::Widget(){
    return m_widget;
}



void IndigoLabelControl::setLabel(QIcon icon, int iconSize, Qt::Alignment alignment){

    if(!m_label)
        m_labelLayout->removeWidget(m_label);

    m_icon = icon;
    m_iconSize = iconSize;

    QPixmap pixmap = icon.pixmap(icon.actualSize(QSize(iconSize, iconSize)));

    QLabel *label = new QLabel();
    label->setPixmap( pixmap );

    m_label = label;
    m_label->setFixedSize(iconSize,iconSize);

    m_labelLayout->addWidget(m_label);
    m_labelLayout->setAlignment(m_label, alignment);

}



void IndigoLabelControl::setLabel(QString string, int width, Qt::Alignment alignment){

    if(!m_label)
        m_labelLayout->removeWidget(m_label);

    QLabel *label = new QLabel(string);
    label->adjustSize();
    label->setAlignment(Qt::AlignRight);
    m_label = label;
    m_label->setFixedSize(width, label->height());

    m_labelLayout->addWidget(m_label);
    m_labelLayout->setAlignment(m_label, alignment);

}



void IndigoLabelControl::setLabel(QWidget *widget, int width, Qt::Alignment alignment){

    if(!m_label)
        m_labelLayout->removeWidget(m_label);

    m_label = widget;
    m_label->setFixedSize(width, widget->height());

    m_labelLayout->addWidget(m_label);
    m_labelLayout->setAlignment(m_label, alignment);
}



QIcon IndigoLabelControl::Icon(){
    return m_icon;
}



QWidget *IndigoLabelControl::Label(){
    return m_label;
}



