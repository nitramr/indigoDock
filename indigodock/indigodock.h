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


#ifndef INDIGODOCK_H
#define INDIGODOCK_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <QtGui>
#include <QList>

#include "indigopanel.h"
#include "indigotabbar.h"
#include "helper.h"


class IndigoDock : public QDockWidget
{
    Q_OBJECT

public:

    IndigoDock(QString name, QWidget *parent = 0);
    void addIndigoPanel(IndigoPanel *panel, int tabIndex = -1);
    void hoverDock(IndigoPanel *pan);
    void dropPanel(IndigoPanel *pan);
    void removePanel(int index);
    QList<IndigoPanel*>getPanels();
    void clear();
    Qt::Orientation Orientation();  
    void setMinimumDropzoneHeight(int height);
    void setMinimumDropzoneWidth(int width);
    void setMinimumDropzoneSize(int width, int height);

private:

    QList<IndigoPanel*> lst_PanelList;
    QBoxLayout * lyt_dropzone;

    IndigoTabBar * wdg_toolbar;
    QSplitter *wdg_mainSplitter;
    QSplitter *wdg_panelSplitter;
    QScrollArea * wdg_scrollArea_dz;
    QScrollArea * wdg_scrollArea_tb;
    QWidget *wdg_dropzone;
    QWidget * wdg_placeholder;
    Qt::Orientation m_orientation;

    int int_padding;
    int int_placeholderHeight;
    int int_minHeight;
    int int_minWidth;

    void updatePanels();
    void addPlaceholder (int index = -1);
    void removePlaceholder ();
    void addPanel (IndigoPanel *panel, int tabIndex);
    void calculateSize();


protected:
    void resizeEvent(QResizeEvent *e);
    bool eventFilter(QObject *object, QEvent *event);

signals:
    void panelRemoved(int index);  
    void panelAdded(QIcon icon,int index, QString);
    void panelDropped(int index);

public slots:

    void scrollToPanel(int PanelIndex);
    void scrollToPanel(QString PanelName);

    void movePanel(int oldIndex, int newIndex);


private slots:
     void updateTabPosition(Qt::DockWidgetArea area);
     void updateMinHeight();

};

#endif // INDIGODOCK_H
