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


#ifndef INDIGOPANEL_H
#define INDIGOPANEL_H

#include <QWidget>
#include <QtGui>
#include <QFrame>
#include <QLayout>
#include <QLabel>
#include <QToolButton>
#include <QScrollArea>
#include "uiwidgets/flowlayout.h"

class IndigoPanelHandle : public QWidget
{
        Q_OBJECT
public:

    enum IndigoExpanderState{
        Normal = 0,
        Advanced = 1
    };

    IndigoPanelHandle(QWidget* parent);
    QString Caption();
    void setCaption(QString title, int fontSize);
    void setIcon(QIcon icon, int iconSize);
    void setExpanderState(IndigoExpanderState expanderState);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QIcon ico_icon;
    int int_iconSize;
    QString str_title;
    int int_fontSize;
    QToolButton * wdg_btnClose;
    QToolButton * wdg_btnExpander;


signals:

public slots:
};


/**********************************************************/

class IndigoPanel : public QFrame
{
    Q_OBJECT

public:
    enum IndigoDockState{

        HiddenDocked = 0,
        Floating = 1,
        Docked = 2,
        None = 3

    };



    IndigoPanel(QString name, QWidget* dock = 0);
    IndigoPanel(QString name, QIcon icon, int iconSize = 22, QWidget* dock = 0);
    void addWidget(QWidget *content);
    void addWidget(QLayout *content);

    IndigoPanelHandle * wdg_handle;

    QString Caption();
    void setCaption(QString title = "", int fontSize = 10);

    QIcon Icon();
    void setIcon(QIcon icon, int iconSize = 22);

    int Index();
    void setIndex(int index);

    IndigoDockState dockState();
    void setDockState(IndigoDockState state);
    void setDockState(int state);

    IndigoPanelHandle::IndigoExpanderState expanderState();
    void setExpanderState(IndigoPanelHandle::IndigoExpanderState expanderState);
    void setExpanderState(int expanderState);

protected:   
    bool eventFilter(QObject *object, QEvent *e);

private:   
   // QWidget *wdg_normalContainer;
   // QVBoxLayout *lyt_normalArea;
    FlowLayout * lyt_normalArea;
    QVBoxLayout *lyt_main;
    QScrollArea * wdg_scrollArea;


    QPoint pnt_relativeOffset;
    QIcon ico_icon;    
    int int_index; 
    IndigoDockState m_state;
    IndigoPanelHandle::IndigoExpanderState m_expander;
   // QSpacerItem *wdg_spacer;

signals:
    void mouseReleased();
    void mouseMove();
    void isFloating();
    void panelClosed(int index);
    void panelShown(int index);
    void isAdvanced();
    void isNormal();

public slots:
    void show();
    void hide();
    void toggleExpander();
};

#endif // INDIGOPANEL_H
