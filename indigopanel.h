#ifndef INDIGOPANEL_H
#define INDIGOPANEL_H

#include <QWidget>
#include <QtGui>
#include <QFrame>
#include <QLayout>
#include <indigopanelhandle.h>

class IndigoPanel : public QFrame
{
    Q_OBJECT

public:
    IndigoPanel(QWidget* parent = 0);
    IndigoPanelHandle * handle;
    void setBackgroundColor(const QColor &bgColor);
    void addWidget(QWidget *content);

protected:   
    bool eventFilter(QObject *o, QEvent *e);

private:
    QPalette palette;
    QHBoxLayout *contentArea;
    QPoint oldPos;
    int relative_x;
    int relative_y;

signals:
    void mouseReleased();

public slots:
    void close(bool * exit);
};

#endif // INDIGOPANEL_H
