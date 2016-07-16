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


#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#include <QString>
#include <QSettings>

class ConfigManager
{
public:
    ConfigManager();

    QString getIconPath();
    void setIconPath(QString path);
    QString getThemePath();
    void setThemePath(QString path);


private:

    QString str_SettingsFile;  
    void writeSetting(QString key, QString value);
    QString readSetting(QString key, QString defaultValue);

signals:

public slots:
};

#endif // CONFIGMANAGER_H
