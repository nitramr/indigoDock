//
// C++ Implementation: titlebar
//
// Description:
//
//
// Author: Peter <marcusk@i.ua>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "titlebar.h"
#include <QSize>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QDockWidget>
#include <QPainter>
#include <iostream>

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
 ,bpress(false) ,but_press(false)
{
        //titleTxt = title;
    if(parent)
    {
        QDockWidget *w = static_cast<QDockWidget*>(parent);
        titleTxt = w->windowTitle();
    }
    create_pixmap();

}

void TitleBar::setTitleText(const QString& title)
{
    titleTxt = title;
}

TitleBar::~TitleBar()
{
}

QSize TitleBar::sizeHint() const
{
    return minimumSizeHint();
}

QSize TitleBar::minimumSizeHint() const
{
   QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
    Q_ASSERT(dw != 0);
    QSize result(rightPm.width(), centerPm.height());
    if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar)
        result.transpose();
    return result;
}

void TitleBar::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect rect = this->rect();

    QBrush brush(centerPm);
    painter.fillRect(rect.left(), rect.top(),
                     rect.width(),
                                centerPm.height(), centerPm);
    painter.save();
    QPen pen(QColor(255,255,255));
    painter.setPen(pen);
    painter.drawText(rect.left()+4,rect.bottom()-5,titleTxt);
    painter.restore();

    draw_close_btn();
    painter.drawPixmap(rect.topRight() - QPoint(rightPm.width(), -2), rightPm);
    painter.end();
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{

    std::cout << "mouse down" << std::endl;
    emit panelMove(true);

    QPoint pos = event->pos();
    but_press = true;

    QRect rect = this->rect();

    const int buttonRight = 7;
    const int buttonWidth = 20;
    int right = rect.right() - pos.x();
    int button = (right - buttonRight)/buttonWidth;
    if(!button){
            event->accept();
            bpress = true;
            //dw->close();
    }
    else
        event->ignore();
    repaint();
}


void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    std::cout << "mouse up" << std::endl;
    emit panelMove(false);

    if(!bpress)
    {
        event->ignore();
        return;
    }

    but_press = false;

    QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
    Q_ASSERT(dw != 0);

    QPoint pos = event->pos();

    QRect rect = this->rect();

    const int buttonRight = 7;
    const int buttonWidth = 20;
    int right = rect.right() - pos.x();
    int button = (right - buttonRight)/buttonWidth;
    if(!button){
        event->accept();
        dw->close();
    }
    else
        event->accept();

    bpress = false;

    repaint();
}


/*!
    \fn TitleBar::create_pixmaps()
 */
void TitleBar::create_pixmap()
{
    int ih = 20;
    int iw = 10;

    centerPm = QPixmap(iw, ih);
    centerPm.fill(Qt::transparent);

    QLinearGradient gradient(0,ih,0,0);
    gradient.setColorAt(0, QColor::fromRgb(10, 1, 1));
    gradient.setColorAt(0.5, QColor::fromRgb(87, 87, 89));
    gradient.setColorAt(1, QColor::fromRgb(142, 143, 146));
    QPainter painter(&centerPm);
    painter.fillRect(0, 0, iw, ih, QBrush(gradient));
}


/*!
    \fn TitleBar::draw_close_btn()
 */
void TitleBar::draw_close_btn()
{
    //draw close button
    int ih1 = 13;
    int iw1 = 30;
        QPainter painter;
        QPen pen;
    QLinearGradient gradient1(0, ih1, 0, 0);
    gradient1.setColorAt(0, QColor::fromRgb(131, 3, 3));
    rightPm = QPixmap(iw1, ih1);
    painter.begin(&rightPm);

    if(bpress)
    {
        gradient1.setColorAt(1, QColor::fromRgb(237, 26, 86));
        painter.fillRect(0, 0, iw1, ih1, QBrush(gradient1));
        //draw frame close button
        painter.setPen(QColor(0,0,0));
        painter.drawLine(0,0,iw1,0);
        painter.drawLine(0,ih1,0,0);
                painter.drawLine(0, ih1-1, iw1,ih1-1);
                pen.setColor(QColor(83,31,31));

    }
    else
    {

        gradient1.setColorAt(1, QColor::fromRgb(243, 115, 115));
        painter.fillRect(0, 0, iw1, ih1, QBrush(gradient1));
        //draw frame close button
        painter.setPen(QColor(66,67,70));
        painter.drawLine(0,0,iw1,0);
        painter.setPen(QColor(71,71,74));
        painter.drawLine(0,ih1,0,0);
        painter.setPen(QColor(88,88,90));
            painter.drawLine(0, ih1-1, iw1,ih1-1);
            pen.setColor(QColor(255,255,255));
    }

    //draw line close button
    painter.setPen(pen);
    QVector<QLine> lines;
    lines << QLine(iw1-16,ih1-10,iw1-11,ih1-5) << QLine(iw1-11,ih1-10,iw1-16,ih1-5);
    painter.drawLines(lines);

    update();
    painter.end();
}


/*!
    \fn TitleBar::mouseMoveEvent ( QMouseEvent * event )
 */
void TitleBar::mouseMoveEvent ( QMouseEvent * event )
{
    QPoint pos = event->pos();

    QRect rect = this->rect();
    const int buttonRight = 15;
    const int buttonWidth = 15;
    int right = rect.right() - pos.x();
    int button1 = (right - buttonRight)/buttonWidth;

    const int buttonhi = 10;
    int h = rect.height() - pos.y();
    int button2 = (h-10)/buttonhi;

    int button = button1 | button2;

    if((button != 0) && (but_press))
    {
        bpress = false;
        event->ignore();

    }
    else if((button == 0) && (but_press))
    {
       bpress = true;
       event->accept();

    }
    else
        event->ignore();


    repaint();
}
