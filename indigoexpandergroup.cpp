#include "indigoexpandergroup.h"

IndigoExpanderLabel::IndigoExpanderLabel(QWidget *parent) : QLabel(parent),collapse(false)
{
    //this->setStyleSheet("QLabel{background-color:#99cdef;}");

    margin_left = 3;
    spacing = 4;
    icon_size = 8;

}


void IndigoExpanderLabel::mousePressEvent(QMouseEvent* event)
{
   if (event->buttons() & Qt::LeftButton)
   {
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

void IndigoExpanderLabel::paintEvent(QPaintEvent *e)
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

     if (collapse)
     {
        painter.drawImage(QRect(margin_left, iconY, icon_size,icon_size), QImage(":/icons/icons/close.png"));
     }
     else
     {
        painter.drawImage(QRect(margin_left, iconY, icon_size,icon_size), QImage(":/icons/icons/open.png"));
     }


     painter.setBrush(QBrush(QColor(this->palette().color(QPalette::WindowText)/*Qt::black*/)));
     painter.setFont(font);
     painter.drawText( QRect(labelX, 0, lbl_width, h), Qt::AlignVCenter, text );
     painter.drawLine(lineX, lineY, this->width()- spacing, lineY);
   }

   //QLabel::paintEvent(e);
}



IndigoExpanderGroup::IndigoExpanderGroup(QWidget *parent) : QWidget(parent)
{
    //this->setStyleSheet("QWidget{background-color:#efcd99;}");

    setAutoFillBackground( true );

    // set handleBar
    handle = new IndigoExpanderLabel(this);
    handle->installEventFilter(this);
    handle->setFixedHeight(22);
    connect(handle,SIGNAL(stateSwitch(bool)),this,SLOT(stateSwitch(bool)));

    // Content Widget
    contentArea = new QVBoxLayout;
    contentArea->setContentsMargins(15,0,0,0);
    contentArea->setSpacing(0);

    // Main LayoutContainer
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    mainLayout->addWidget(handle);
    mainLayout->addLayout(contentArea);
    mainLayout->addStretch(1);

    m_widget = NULL;


    // Add dummy content
    QFont font;
    font.setPointSize(8);

    QLabel * lbl = new QLabel("Place Widgets here!");
    lbl->setFont(font);

    addWidget(lbl);
    setCaption("Label");



}


void IndigoExpanderGroup::addWidget(QWidget * widget){

    if (m_widget) return;

    m_widget = widget;
    m_widget->setParent(this);
    contentArea->addWidget(m_widget,0, Qt::AlignTop);
}


void IndigoExpanderGroup::setCaption(const QString &text){

    handle->setText(text);
}


void IndigoExpanderGroup::stateSwitch(bool collapse){

    if(!m_widget) return;

    if(!collapse){
        m_widget->show();
        handle->collapsed(false);
    }else{
        m_widget->hide();
        handle->collapsed(true);
    }

}

