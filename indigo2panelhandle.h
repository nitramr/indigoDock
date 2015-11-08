#ifndef INDIGO2PANELHANDLE_H
#define INDIGO2PANELHANDLE_H

#include <QWidget>
#include <QtGui>
#include <QLayout>
#include <QLabel>
#include <QPushButton>

class Indigo2PanelHandle : public QWidget
{
        Q_OBJECT
public:
    Indigo2PanelHandle(QWidget* parent = 0);
    void setTitle(const QString &title);
    void setBackgroundColor(const QColor &bgColor);

protected:

private:
    QLabel * lblTitle;
    QPushButton * btnClose;
    QPalette palette;

signals:

public slots:
};

#endif // INDIGO2PANELHANDLE_H
