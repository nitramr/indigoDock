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


#include "colorswatch.h"


ColorSwatch::ColorSwatch(QWidget *parent)
    : QWidget(parent)
{


    setAutoFillBackground(true);


    int_conWidth = 9; // countour thickness
    int_spacer = 1; // spacer between countour and fill
    int_valveWidth = 4; // valve width
    int_valveHeight = 4; // valve height
    int_btnSize = 22; // button dimensions

    setMinimumHeight(int_btnSize*2);

    setFixedHeight(44);
    setMinimumWidth(height() + int_valveWidth + int_btnSize);

    int_conSize = this->height(); // square width and height without valves

    // Placeholder Buttons
    btn_Contour = new QPushButton(this);
    btn_Fill = new QPushButton(this);

    // place buttons
    placeContourButton();
    placeFillButton();

    // set default brush
    brsh_fill = QBrush(Qt::black);
    brsh_contour = QBrush(Qt::black);



    // Dummy brush (please remove)
    QLinearGradient gradient(0,0,this->height(),this->height());
        gradient.setColorAt(0, QColor(110,110,110));
        gradient.setColorAt(0.27, QColor(230,230,230));
        gradient.setColorAt(0.44, QColor(110,110,110));
        gradient.setColorAt(0.76, QColor(230,230,230));
        gradient.setColorAt(1, QColor(110,110,110));

    setFillBrush(QBrush(gradient));


}



void ColorSwatch::paintEvent(QPaintEvent*) {

    QPainter painter(this);



    // Contour Points
    int conX1 = 0;
    int conY1 = 0;

    int conX2   = int_conSize;
    int conY2   = 0;

    int conX3   = int_conSize;
    int conY3   = int_conWidth;

    int conX4   = int_conWidth;
    int conY4   = int_conWidth;

    int conX5   = int_conWidth;
    int conY5   = int_conSize - int_conWidth ;

    int conX6   = conY5; //conSize - conWidth;
    int conY6   = conY5; //conSize - conWidth;

    int conX7   = conY5; //conSize - conWidth;
    int conY7   = int_conWidth + (int_spacer*2) + int_valveHeight;

    int conX8   = int_conSize;
    int conY8   = conY7; //conWidth + (spacer*2) + valveHeight;

    int conX9   = int_conSize;
    int conY9   = int_conSize - int_spacer - int_conWidth - int_valveHeight;

    int conX10   = int_conSize + int_valveWidth;
    int conY10   = conY9; //conSize - spacer - conWidth - valveHeight;

    int conX11   = int_conSize + int_valveWidth;
    int conY11   = int_conSize - int_spacer - int_conWidth;

    int conX12   = int_conSize;
    int conY12   = conY11; //conSize - spacer - conWidth;

    int conX13   = int_conSize;
    int conY13   = int_conSize;

    int conX14   = 0;
    int conY14   = int_conSize;


    // Fill Points
    int fillX1 = conX4 + int_spacer;
    int fillY1 = conY4 + int_spacer;

    int fillX2 = conX10;
    int fillY2 = fillY1;

    int fillX3 = conX10;
    int fillY3 = int_conWidth + int_spacer + int_valveHeight;

    int fillX4 = conY11;
    int fillY4 = fillY3; //conWidth + spacer + valveHeight;

    int fillX5 = conX6 - int_spacer;
    int fillY5 = conY6 - int_spacer;

    int fillX6 = fillX1;
    int fillY6 = fillY5;

    QPainterPath countour;
    countour.moveTo (conX1, conY1);
    countour.lineTo (conX2, conY2);
    countour.lineTo (conX3, conY3);
    countour.lineTo (conX4, conY4);
    countour.lineTo (conX5, conY5);
    countour.lineTo (conX6, conY6);
    countour.lineTo (conX7, conY7);
    countour.lineTo (conX8, conY8);
    countour.lineTo (conX9, conY9);
    countour.lineTo (conX10, conY10);
    countour.lineTo (conX11, conY11);
    countour.lineTo (conX12, conY12);
    countour.lineTo (conX13, conY13);
    countour.lineTo (conX14, conY14);
    countour.lineTo (conX1, conY1);

    QPainterPath fill;
    fill.moveTo (fillX1, fillY1);
    fill.lineTo (fillX2, fillY2);
    fill.lineTo (fillX3, fillY3);
    fill.lineTo (fillX4, fillY4);
    fill.lineTo (fillX5, fillY5);
    fill.lineTo (fillX6, fillY6);
    fill.lineTo (fillX1, fillY1);

    painter.setPen (Qt :: NoPen);
    painter.fillPath (countour, brsh_contour);
    painter.fillPath (fill, brsh_fill);


}



void ColorSwatch::setContourBrush(QBrush brush){
    brsh_contour = brush;
    update();
}



void ColorSwatch::setFillBrush(QBrush brush){
    brsh_fill = brush;
    update();
}



void ColorSwatch::setContourButton(QPushButton *btnContour){
    btn_Contour = btnContour;
    placeContourButton();
}



void ColorSwatch::setFillButton(QPushButton *btnFill){
    btn_Fill = btnFill;
    placeFillButton();
}



void ColorSwatch::placeContourButton(){
    if (!btn_Contour) return;

    btn_Contour->setFixedSize(int_btnSize,int_btnSize);
    btn_Contour->move(int_conSize + int_valveWidth, 0);

}



void ColorSwatch::placeFillButton(){
    if(!btn_Fill) return;

    btn_Fill->setFixedSize(int_btnSize,int_btnSize);
    btn_Fill->move(int_conSize + int_valveWidth, int_conSize - btn_Fill->height());
}

