/*******************************************************
 *
 * Copyright (C) 2016  Martin Reininger
 *
 * This file is part of IndigoDock.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *******************************************************/


#include "expandergroup.h"
#include "configmanager.h"


/*#####################
 #
 #
 # ExpanderLabel
 #
 #
 ####################*/


ExpanderLabel::ExpanderLabel(QWidget *parent) : QLabel(parent),collapse(false)
{
    margin_left = 3; // left margin of icon
    spacing = 4; // space around text label
    icon_size = 8; // icon dimensions
    b_collapsable = true;

    iconPath =  ConfigManager().getIconPath();


}


/**********************
 *
 * Events
 *
 * *******************/


void ExpanderLabel::mousePressEvent(QMouseEvent* event)
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



void ExpanderLabel::paintEvent(QPaintEvent *)
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
            painter.drawImage(QRect(margin_left, iconY, icon_size,icon_size), QImage(iconPath +"close.png"));
         }
         else
         {
            painter.drawImage(QRect(margin_left, iconY, icon_size,icon_size), QImage(iconPath +"open.png"));
         }
     }

     painter.setBrush(QBrush(QColor(this->palette().color(QPalette::WindowText)/*Qt::black*/)));
     painter.setFont(font);
     painter.drawText( QRect(labelX, 0, lbl_width, h), Qt::AlignVCenter, text );
     painter.drawLine(lineX, lineY, this->width()- spacing, lineY);
   }

   //QLabel::paintEvent(e);
}


/**********************
 *
 * Properties
 *
 * *******************/


void ExpanderLabel::collapsed(bool collapsed){
    collapse = collapsed;
}



void ExpanderLabel::isCollapsable(bool collapsable){

    b_collapsable = collapsable;
}



/*#####################
 #
 #
 # ExpanderGroup
 #
 #
 ####################*/


ExpanderGroup::ExpanderGroup(bool collapsable, QWidget *parent) : QWidget(parent)
{
    //this->setStyleSheet("QWidget{background-color:#efcd99;}");

    setAutoFillBackground( true );

    // set handleBar
    m_handle = new ExpanderLabel(this);
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



void ExpanderGroup::addWidget(QWidget * widget){

    if (m_widget) return;

    m_widget = widget;
    m_widget->setParent(this);
    m_contentArea->addWidget(m_widget,0, Qt::AlignTop);
}


/**********************
 *
 * Properties
 *
 * *******************/


void ExpanderGroup::setCaption(const QString text){

    m_handle->setText(text);
}



void ExpanderGroup::isCollapsable(bool collapsable){

    m_handle->isCollapsable(collapsable);
}



void ExpanderGroup::stateSwitch(bool collapse){

    if(!m_widget) return;

    if(!collapse){
        m_widget->show();
        m_handle->collapsed(false);
    }else{
        m_widget->hide();
        m_handle->collapsed(true);
    }

}
