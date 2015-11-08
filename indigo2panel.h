#ifndef INDIGOPANEL2_H
#define INDIGOPANEL2_H

#include <QWidget>
#include <QtGui>
#include <QFrame>
#include <indigo2dropzone.h>

class Indigo2Panel : public QFrame
{
    Q_OBJECT

public:
    Indigo2Panel(QWidget* parent = 0);

protected:
   // bool event ( QEvent * event );
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent ( QMouseEvent * event );

private:
    QPoint oldPos;
    int relative_x;
    int relative_y;
signals:
    void mouseReleased();

public slots:
    void close(bool * exit);
};

#endif // INDIGOPANEL2_H
