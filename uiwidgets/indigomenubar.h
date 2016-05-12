/*******************************************************
 *
 * Copyright (C) 2016  Ale Rimoldi
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


#ifndef INDIGOMENUBAR_H
#define INDIGOMENUBAR_H

#include <QMenuBar>

class QJsonObject;

class IndigoMenuBar : public QMenuBar
{
public:
    IndigoMenuBar();
private:
    bool loadSettings();
    void read(const QJsonObject &json);
    void fill(const QJsonArray menuMainEntries);

    QMenu* getMenuItemFromJson(const QJsonObject json);
    QAction* getActionFromJson(const QJsonObject json, QObject* parent);
    QString iconPath;

};
#endif // INDIGOMENUBAR_H
