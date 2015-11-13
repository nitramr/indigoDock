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
};

#endif // INDIGOMENUBAR_H
