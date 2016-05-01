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


#ifndef TEXTBOXSIMULATOR_H
#define TEXTBOXSIMULATOR_H

#include <QtWidgets>
#include <QWidget>

class TextBoxSimulator : public QWidget
{
       Q_OBJECT
public:
    TextBoxSimulator(QWidget *parent = 0);

private:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent * );

    bool bool_clicked;
    bool bool_dblclick;

signals:
    void mousePressed();
    void mouseDoubleClick();

public slots:
};

#endif // TEXTBOXSIMULATOR_H
