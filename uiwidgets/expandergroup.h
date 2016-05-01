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


#ifndef EXPANDERGROUP_H
#define EXPANDERGROUP_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QtGui>
#include <QPolygon>


class ExpanderLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ExpanderLabel(QWidget *parent = 0);
    void collapsed(bool);
    void isCollapsable(bool collapsable);

private:
    bool collapse;
    bool b_collapsable;
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *);

    int margin_left;
    int spacing;
    int icon_size;
    QString iconPath;

signals:
    void stateSwitch(bool);
public slots:
};

/*******************************************************/

class ExpanderGroup : public QWidget
{
    Q_OBJECT
public:
    explicit ExpanderGroup(bool collapsable = true, QWidget *parent = 0);
    void addWidget(QWidget * widget);
    void setCaption(const QString text);
    void isCollapsable(bool collapsable);

private:
    QPalette palette;
    QVBoxLayout *m_contentArea;
    ExpanderLabel * m_handle;
    QWidget * m_widget;

signals:

public slots:
    void stateSwitch(bool);
};



#endif // EXPANDERGROUP_H
