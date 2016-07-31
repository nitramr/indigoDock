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
    setFixedSize(1000,700);
    bool_clicked = false;
    bool_dblclick = false;

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(20);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor(Qt::black);

    this->setGraphicsEffect(effect);


}


void TextBoxSimulator::paintEvent(QPaintEvent *){


    int frameWidth = 245;
    int frameHeight = 195;
    int margin = 0;
    int innerMargin = 40;
    int offsetV = height() / 2 - frameHeight / 2;
    int offsetH = width() / 2 - frameWidth / 2;


    QPainter painter(this);

    QColor col_Frame = QColor(this->palette().color(QPalette::Dark));
    QColor col_Backdrop = QColor(this->palette().color(QPalette::Dark));
    QColor col_Document = QColor(255,255,255);
    QColor col_Guides = QColor(255, 85, 153);

    painter.fillRect(QRect(0,0,width(),height()), col_Backdrop);
    painter.fillRect(QRect(margin,margin,width() - margin*2,height() - margin*2), col_Document);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(col_Guides);
    painter.drawRect(QRect(margin + innerMargin,margin + innerMargin, width() - (margin + innerMargin) *2, height() - (margin + innerMargin) *2));


    if(bool_clicked) col_Frame = QColor(this->palette().color(QPalette::Highlight));


    painter.setBrush(Qt::NoBrush);
    painter.setPen(col_Frame);
    painter.drawRect(QRect(offsetH + 2,offsetV +2,frameWidth,frameHeight));

    if(bool_clicked){
        painter.drawRect(QRect(offsetH,offsetV,5,5));
        painter.fillRect(QRect(offsetH + 1,offsetV + 1,4,4), QColor(this->palette().color(QPalette::Light)));

        painter.drawRect(QRect(offsetH + frameWidth -1,offsetV,5,5));
        painter.fillRect(QRect(offsetH + frameWidth, offsetV + 1,4,4), QColor(this->palette().color(QPalette::Light)));

        painter.drawRect(QRect(offsetH,offsetV + frameHeight-1,5,5));
        painter.fillRect(QRect(offsetH + 1,offsetV + frameHeight,4,4), QColor(this->palette().color(QPalette::Light)));

        painter.drawRect(QRect(offsetH + frameWidth-1,offsetV + frameHeight-1,5,5));
        painter.fillRect(QRect(offsetH + frameWidth,offsetV + frameHeight,4,4), QColor(this->palette().color(QPalette::Light)));
    }

    if(bool_dblclick){

        painter.fillRect(QRect(offsetH + 110,offsetV + 34,2,14), col_Frame);
    }


    QPen pen(col_Frame);
    painter.setPen(pen);

    QFont font=painter.font() ;
    font.setPointSize ( 10 );
    //font.setWeight(QFont::DemiBold);
    painter.setFont(font);
    painter.drawText(offsetH + 15, offsetV + 30, "Click here to edit frame, double click");
    painter.drawText(offsetH + 15, offsetV + 45, "to edit content.");


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

