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


#ifndef COLORSWATCH_H
#define COLORSWATCH_H

#include <QWidget>
#include <QtGui>
#include <QPushButton>


class ColorSwatch : public QWidget
{
    Q_OBJECT

public:
    ColorSwatch(QWidget *parent = 0);

    void setContourBrush(QBrush brush);
    void setFillBrush(QBrush brush);
    void setContourButton(QPushButton *btnContour);
    void setFillButton(QPushButton *btnFill);

protected:
    QPushButton *btn_Contour;
    QPushButton *btn_Fill;

private:  
    void paintEvent(QPaintEvent*);
    QBrush brsh_contour;
    QBrush brsh_fill;

    int int_conSize;
    int int_conWidth;
    int int_spacer;
    int int_valveWidth;
    int int_valveHeight;
    int int_btnSize;

    void placeContourButton();
    void placeFillButton();

signals:

public slots:
};





#endif // COLORSWATCH_H
