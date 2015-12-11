#include "indigoexpandergroup.h"

IndigoExpanderLabel::IndigoExpanderLabel(QWidget *parent) : QLabel(parent),collapse(false)
{
    margin_left = 3; // left margin of icon
    spacing = 4; // space around text label
    icon_size = 8; // icon dimensions
    b_collapsable = true;

}


void IndigoExpanderLabel::mousePressEvent(QMouseEvent* event)
{
   if (event->buttons() & Qt::LeftButton)
   {

     if(!b_collapsable) return;

     event->accept();
     collapse = !collapse;
     emit stateSwitch(collapse);
   }
   else
   {
     event->ignore();
   }
}


void IndigoExpanderLabel::collapsed(bool collapsed){
    collapse = collapsed;
}

void IndigoExpanderLabel::isCollapsable(bool collapsable){

    b_collapsable = collapsable;
}

void IndigoExpanderLabel::paintEvent(QPaintEvent *)
{

   QPainter painter(this);

   int h = this->height();
   int lineY = h / 2;
   int iconY = (h - icon_size) / 2;
   int fontSize = 10;
   QFont font = painter.font() ;
   font.setPointSize ( fontSize );
   //font.setWeight(QFont::DemiBold);

   QString text = this->text();

   QFontMetrics fm(this->font());

   int lbl_width = fm.width(text);


   if (h > 0)
   {

       // label start
       int labelX = margin_left + icon_size + spacing;

       // line start
       int lineX = labelX + lbl_width + spacing;


     if(b_collapsable){

         if (collapse)
         {
            painter.drawImage(QRect(margin_left, iconY, icon_size,icon_size), QImage(":/icons/icons/close.png"));
         }
         else
         {
            painter.drawImage(QRect(margin_left, iconY, icon_size,icon_size), QImage(":/icons/icons/open.png"));
         }
     }

     painter.setBrush(QBrush(QColor(this->palette().color(QPalette::WindowText)/*Qt::black*/)));
     painter.setFont(font);
     painter.drawText( QRect(labelX, 0, lbl_width, h), Qt::AlignVCenter, text );
     painter.drawLine(lineX, lineY, this->width()- spacing, lineY);
   }

   //QLabel::paintEvent(e);
}

/********************************************************************************************/

IndigoExpanderGroup::IndigoExpanderGroup(bool collapsable, QWidget *parent) : QWidget(parent)
{
    //this->setStyleSheet("QWidget{background-color:#efcd99;}");

    setAutoFillBackground( true );

    // set handleBar
    m_handle = new IndigoExpanderLabel(this);
    m_handle->installEventFilter(this);
    m_handle->setFixedHeight(22);
    m_handle->isCollapsable(collapsable);
    connect(m_handle,SIGNAL(stateSwitch(bool)),this,SLOT(stateSwitch(bool)));

    // Content Widget
    m_contentArea = new QVBoxLayout;
    m_contentArea->setContentsMargins(15,0,0,0);
    m_contentArea->setSpacing(0);

    // Main LayoutContainer
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    mainLayout->addWidget(m_handle);
    mainLayout->addLayout(m_contentArea);
    mainLayout->addStretch(1);

    m_widget = NULL;

}


void IndigoExpanderGroup::addWidget(QWidget * widget){

    if (m_widget) return;

    m_widget = widget;
    m_widget->setParent(this);
    m_contentArea->addWidget(m_widget,0, Qt::AlignTop);
}


void IndigoExpanderGroup::setCaption(const QString text){

    m_handle->setText(text);
}

void IndigoExpanderGroup::isCollapsable(bool collapsable){

    m_handle->isCollapsable(collapsable);
}

void IndigoExpanderGroup::stateSwitch(bool collapse){

    if(!m_widget) return;

    if(!collapse){
        m_widget->show();
        m_handle->collapsed(false);
    }else{
        m_widget->hide();
        m_handle->collapsed(true);
    }

}

