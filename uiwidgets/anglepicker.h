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


#ifndef ANGLEPICKER_H
#define ANGLEPICKER_H

#include <QWidget>
#include <QtGui>


class AnglePicker : public QWidget
{
       Q_OBJECT

public:
    AnglePicker(QWidget *parent = 0);
    AnglePicker(double angle, QWidget *parent = 0);
    void setAngle(double degree);
    double Angle();

private:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void init();

    QPoint pnt_center;
    QPoint pnt_pointer;
    QRect rct_circleFrame;
    int int_lineThickness;
    double dbl_angle;
    int int_diameter;
    double dbl_transparency;

signals:
    void angleChanged();

public slots:
};

#endif // ANGLEPICKER_H
