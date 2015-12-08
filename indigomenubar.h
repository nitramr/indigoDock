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
    int smallest(int r, int g, int b);
    int biggest(int r, int g, int b);
    QIcon tintIcon(const QIcon &icon, int min = 0, int max = 255);
    QMenu* getMenuItemFromJson(const QJsonObject json);
    QAction* getActionFromJson(const QJsonObject json, QObject* parent);
    const QString iconPath = "icons/";

};
#endif // INDIGOMENUBAR_H
