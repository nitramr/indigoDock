#ifndef CONFIGMANAGER_H
#define GONFIGMANAGER_H
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
    QString getTheme();
    void setTheme(QString name);


private:

    QString str_SettingsFile;
    QString str_iconPath;
    QString str_themePath;
    QString str_theme;


signals:

public slots:
};

#endif // CONFIGMANAGER_H
