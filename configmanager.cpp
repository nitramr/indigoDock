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

