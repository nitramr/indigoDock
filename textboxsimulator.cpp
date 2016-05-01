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


#include "textboxsimulator.h"

TextBoxSimulator::TextBoxSimulator(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(250,200);
    bool_clicked = false;
    bool_dblclick = false;

}


void TextBoxSimulator::paintEvent(QPaintEvent *){

    QPainter painter(this);


    QColor color = QColor(this->palette().color(QPalette::Dark));

    if(bool_clicked) color = QColor(this->palette().color(QPalette::Highlight));


    painter.setBrush(Qt::NoBrush);
    painter.setPen(color);
    painter.drawRect(QRect(2,2,245,195));

    if(bool_clicked){
        painter.drawRect(QRect(0,0,5,5));
        painter.fillRect(QRect(1,1,4,4), QColor(this->palette().color(QPalette::Light)));

        painter.drawRect(QRect(244,0,5,5));
        painter.fillRect(QRect(245,1,4,4), QColor(this->palette().color(QPalette::Light)));

        painter.drawRect(QRect(0,194,5,5));
        painter.fillRect(QRect(1,195,4,4), QColor(this->palette().color(QPalette::Light)));

        painter.drawRect(QRect(244,194,5,5));
        painter.fillRect(QRect(245,195,4,4), QColor(this->palette().color(QPalette::Light)));
    }

    if(bool_dblclick){

        painter.fillRect(QRect(110,34,2,14), QColor(this->palette().color(QPalette::Dark)));
    }


    QPen pen(QColor(this->palette().color(QPalette::Dark)));
    painter.setPen(pen);

    QFont font=painter.font() ;
    font.setPointSize ( 10 );
    //font.setWeight(QFont::DemiBold);
    painter.setFont(font);
    painter.drawText(15, 30, "Click here to edit frame, double click");
    painter.drawText(15, 45, "to edit content.");


}

void TextBoxSimulator::mousePressEvent(QMouseEvent *){

    bool_clicked = true;
    bool_dblclick= false;
    update();
    emit mousePressed();

}

void TextBoxSimulator::mouseDoubleClickEvent(QMouseEvent * ){

    bool_clicked = false;
    bool_dblclick = true;
    update();
    emit mouseDoubleClick();
}

