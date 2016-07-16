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

}



QString ConfigManager::readSetting(QString key, QString defaultValue){

    QSettings settings(str_SettingsFile, QSettings::IniFormat);
    return settings.value(key, defaultValue).toString();
}



void ConfigManager::writeSetting(QString key, QString value){

    QSettings settings(str_SettingsFile, QSettings::IniFormat);
    settings.setValue(key, value);
}



QString ConfigManager::getIconPath(){

    return readSetting("path/iconPath", ":/data/icons/dark/");
}



QString ConfigManager::getThemePath(){

    return readSetting("path/themePath", ":/data/qss/scribus-dark.qss");
}



void ConfigManager::setIconPath(QString path){
    writeSetting("path/iconPath", path);
}



void ConfigManager::setThemePath(QString path){
    writeSetting("path/themePath", path);
}

