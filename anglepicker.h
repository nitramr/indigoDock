#ifndef ANGLEPICKER_H
#define ANGLEPICKER_H

#include <QWidget>
#include <QtGui>


class AnglePicker : public QWidget
{
       Q_OBJECT

public:
    AnglePicker(QWidget *parent = 0);
    void setAngle(double degree);
    double Angle();

private:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);


    QPoint m_center;
    QPoint m_pointer;
    QRect circleFrame;
    int m_lineThickness;
    double m_angle;
    int diameter;
    double transparency;

signals:
    void angleChanged();

public slots:
};

#endif // ANGLEPICKER_H
