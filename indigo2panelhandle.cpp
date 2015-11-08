#include "indigo2panelhandle.h"


/* TODO:
 *
 * - add functional close button
 *
 */

Indigo2PanelHandle::Indigo2PanelHandle(QWidget *parent) :
    QWidget(parent)
{

    setAutoFillBackground( true );

    lblTitle = new QLabel("");
    btnClose = new QPushButton("");
    btnClose->setFixedSize(16,16);

    // Main LayoutContainer
    QHBoxLayout * mainLayout = new QHBoxLayout;
    mainLayout->setMargin(4);
    setLayout(mainLayout);

    mainLayout->addWidget(lblTitle);
    mainLayout->addStretch(1);
    mainLayout->addWidget(btnClose);

}

void Indigo2PanelHandle::setTitle(const QString &title){
    lblTitle->setText(title);
}

void Indigo2PanelHandle::setBackgroundColor(const QColor &bgColor){
     palette.setColor( QPalette::Background, bgColor );
     setPalette( palette );
}
