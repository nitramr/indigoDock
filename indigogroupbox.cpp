#include "indigogroupbox.h"
#include <QLabel>

IndigoGroupBox::IndigoGroupBox(QWidget *parent) : QGroupBox(parent)
{
    installEventFilter(this);
    this->setTitle("ExpanderGroup");
    this->setCheckable(true);
    this->setFocusPolicy(Qt::NoFocus);

    this->setObjectName("indigoGroup");
    this->setStyleSheet("QGroupBox#indigoGroup {"
                            "/*background-color: rgb(255,153,153);*/"
                            "border-top: 1px solid black; "
                            "margin-top: 0.5em;"
                            "margin-left:5px;"
                            "margin-right:5px;"
                            "font-size:10pt;"
                        "}"
                        "QGroupBox#indigoGroup::indicator {"
                            "width: 8px;"
                            "height: 8px;"
                            "image: url(:/icons/icons/open.png);"
                        "}"
                        "QGroupBox#indigoGroup::indicator:unchecked {"
                            "image: url(:/icons/icons/close.png);"
                        "}"
                        "QGroupBox#indigoGroup::title {"
                            "subcontrol-origin: margin; "
                            "margin-right:4px;"
                            "margin-left:3px;"
                        " } "

                       );

    // Setup Layout Container
    mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(12,15,0,6);
    this->setLayout(mainLayout);

    minHeight = 22;

    // Add dummy content
    QFont font;
    font.setPointSize(8);

    QLabel * lbl = new QLabel("Place Widgets here!");
    lbl->setFont(font);


    mainLayout->addWidget(lbl,0, Qt::AlignTop);

}

bool IndigoGroupBox::eventFilter(QObject *o, QEvent *e)
{
    if(e->type()==QEvent::MouseButtonRelease &&  static_cast<QMouseEvent*>(e)->pos().y()<minHeight )
    {
        // BUG: if not clicked on title the icon is not updated

        const char* collapsed = "collapsed";
        IndigoGroupBox* gb = (IndigoGroupBox*)o;
        bool b = o->property(collapsed).toBool();
        if(b)
        {
            gb->setFixedHeight(QWIDGETSIZE_MAX);
            gb->adjustSize();
            gb->setProperty(collapsed,false);
        }
        else
        {
            gb->setFixedHeight(minHeight);
            gb->setProperty(collapsed,true);
        }
    }
    return false;
}
