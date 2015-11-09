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
    void setLastParent(QWidget * dropzone);
    QWidget * lastParent();

protected:   
    bool eventFilter(QObject *o, QEvent *e);

private:
    QPalette palette;
    QHBoxLayout *contentArea;
    QPoint oldPos;
    int relative_x;
    int relative_y;
    QWidget *lastParentWidget;

signals:
    void mouseReleased();
    void mouseMove();

public slots:
    void hide();
};

#endif // INDIGOPANEL_H
