/***************************************************************************
 *   Copyright (C) 2005-2015 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 *                                                                         *
 * *************************************************************************

     This is a modified version of original code on:
     https://github.com/quassel/quassel/blob/master/src/uisupport/qssparser.h

 */


#ifndef THEMEFACTORY_H
#define THEMEFACTORY_H
#include <QString>
#include <QStyle>
#include <QPalette>


class ThemeFactory
{


public:
    ThemeFactory();

    inline QPalette palette() const { return pal_palette; }

    QString getTheme();
    void parseString(QString &StyleString);

protected:
    QHash<QString, QPalette::ColorRole> _paletteColorRoles;
    QHash<QString, QPalette::ColorGroup> _paletteColorGroups;
    QColor parseColor(const QString str);


 private:
    QString str_theme;
    QPalette pal_palette;

    void builtPalette(QString group, QString role, QString color);
    qreal colorRange(qreal value, qreal min, qreal max);

signals:

public slots:
};

#endif // THEMEFACTORY_H
