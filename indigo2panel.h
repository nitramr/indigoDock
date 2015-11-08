#ifndef INDIGOPANEL2_H
#define INDIGOPANEL2_H

#include <QWidget>
#include <QtGui>
#include <QFrame>
#include <QLayout>
#include <indigo2panelhandle.h>

class Indigo2Panel : public QFrame
{
    Q_OBJECT

public:
    Indigo2Panel(QWidget* parent = 0);
    Indigo2PanelHandle * handle;
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

#endif // INDIGOPANEL2_H
