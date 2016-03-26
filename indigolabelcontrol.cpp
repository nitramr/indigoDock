#include "indigolabelcontrol.h"

IndigoLabelControl::IndigoLabelControl(QWidget *parent)
    : QWidget(parent)
{
    setAutoFillBackground( true );
    wdg_widget = NULL;
    wdg_label = NULL;

    int padding = 5;

    lyt_labelLayout = new QHBoxLayout();
    lyt_labelLayout->setContentsMargins(0,0,padding,0);

    lyt_widgetLayout = new QHBoxLayout();
    lyt_widgetLayout->setMargin(0);

    QHBoxLayout * mainLayout = new QHBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    mainLayout->addLayout(lyt_labelLayout);
    mainLayout->addLayout(lyt_widgetLayout);


}



void IndigoLabelControl::setWidget(QWidget *widget, int width/*, Qt::Alignment alignment*/){

    if(!wdg_widget)
        lyt_widgetLayout->removeWidget(wdg_widget);

    wdg_widget = widget;

    if(width > -1)
        wdg_widget->setFixedWidth(width);

    lyt_widgetLayout->addWidget(wdg_widget);
   // m_widgetLayout->setAlignment(m_widget, alignment);
}



QWidget* IndigoLabelControl::Widget(){
    return wdg_widget;
}



void IndigoLabelControl::setLabel(QIcon icon, int iconSize, Qt::Alignment alignment){

    if(!wdg_label)
        lyt_labelLayout->removeWidget(wdg_label);

    ico_icon = icon;
    int_iconSize = iconSize;

    QPixmap pixmap = icon.pixmap(icon.actualSize(QSize(iconSize, iconSize)));

    QLabel *label = new QLabel();
    label->setPixmap( pixmap );

    wdg_label = label;
    wdg_label->setFixedSize(iconSize,iconSize);

    lyt_labelLayout->addWidget(wdg_label);
    lyt_labelLayout->setAlignment(wdg_label, alignment);

}



void IndigoLabelControl::setLabel(QString string, int width, Qt::Alignment alignment){

    if(!wdg_label)
        lyt_labelLayout->removeWidget(wdg_label);

    QLabel *label = new QLabel(string);
    label->adjustSize();
    label->setAlignment(Qt::AlignRight);
    wdg_label = label;
    wdg_label->setFixedSize(width, label->height());

    lyt_labelLayout->addWidget(wdg_label);
    lyt_labelLayout->setAlignment(wdg_label, alignment);

}



void IndigoLabelControl::setLabel(QWidget *widget, int width, Qt::Alignment alignment){

    if(!wdg_label)
        lyt_labelLayout->removeWidget(wdg_label);

    wdg_label = widget;
    wdg_label->setFixedSize(width, widget->height());

    lyt_labelLayout->addWidget(wdg_label);
    lyt_labelLayout->setAlignment(wdg_label, alignment);
}



QIcon IndigoLabelControl::Icon(){
    return ico_icon;
}



QWidget *IndigoLabelControl::Label(){
    return wdg_label;
}



