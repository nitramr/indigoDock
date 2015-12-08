#ifndef ANGLEPICKER_H
#define ANGLEPICKER_H

#include <QWidget>
#include <QtGui>


class AnglePicker : public QWidget
{
       Q_OBJECT

public:
     AnglePicker(QWidget *parent = 0);


private:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    float getAngle(QPoint centerPt, QPoint targetPt);

    QPoint m_center;
    QPoint m_pointer;
    int m_lineThickness;
    float m_angle;

signals:

public slots:
};

#endif // ANGLEPICKER_H
