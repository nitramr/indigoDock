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
    QIcon tintIcon(const QIcon &icon);
    QMenu* getMenuItemFromJson(const QJsonObject json);
    QAction* getActionFromJson(const QJsonObject json, QObject* parent);
    const QString iconPath = "icons/";

};
#endif // INDIGOMENUBAR_H
