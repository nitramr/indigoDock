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


#ifndef INDIGODOCKMANAGER_H
#define INDIGODOCKMANAGER_H

#include <QWidget>
#include "indigodock.h"

class IndigoDockManager: public QWidget
{
    Q_OBJECT
public:
    IndigoDockManager(QWidget *parent = 0);
    void addIndigoDock(IndigoDock * dock);
    void addIndigoPanel(IndigoDock * dock, IndigoPanel * panel, int tabIndex = -1);
    void scrollToPanel(QString name);

private:
    QList<IndigoDock*> lst_Docks;

signals:

public slots:
    void hoverDock();
    void dropPanel();
    void removePanel(int index);
};

#endif // INDIGODOCKMANAGER_H
