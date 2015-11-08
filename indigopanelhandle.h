#ifndef INDIGOPANELHANDLE_H
#define INDIGOPANELHANDLE_H

#include <QWidget>
#include <QtGui>
#include <QLayout>
#include <QLabel>
#include <QPushButton>

class IndigoPanelHandle : public QWidget
{
        Q_OBJECT
public:
    IndigoPanelHandle(QWidget* parent = 0);
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

#endif // INDIGOPANELHANDLE_H
