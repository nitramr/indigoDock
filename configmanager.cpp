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


#include "configmanager.h"
#include <QDebug>

ConfigManager::ConfigManager()
{

    // read setting file
    str_SettingsFile = "settings.ini";

    QSettings settings(str_SettingsFile, QSettings::IniFormat);

    // load settings
    str_iconPath = settings.value("path/iconPath", ":/data/icons/dark/").toString();
    str_themePath = settings.value("path/themePath", ":/data/qss/scribus-dark.qss").toString();

}



QString ConfigManager::getIconPath(){
    return str_iconPath;
}



QString ConfigManager::getThemePath(){
    return str_themePath;
}



void ConfigManager::setIconPath(QString path){
    QSettings settings(str_SettingsFile, QSettings::IniFormat);
    settings.setValue("path/iconPath", path);
}



void ConfigManager::setThemePath(QString path){
    QSettings settings(str_SettingsFile, QSettings::IniFormat);
    settings.setValue("path/themePath", path);
}

