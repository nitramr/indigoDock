#ifndef ANGLEPICKER_H
#define ANGLEPICKER_H

#include <QWidget>
#include <QtGui>


class AnglePicker : public QWidget
{
       Q_OBJECT

public:
    AnglePicker(QWidget *parent = 0);
    AnglePicker(double angle, QWidget *parent = 0);
    void setAngle(double degree);
    double Angle();

private:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void init();

    QPoint pnt_center;
    QPoint pnt_pointer;
    QRect rct_circleFrame;
    int int_lineThickness;
    double int_angle;
    int int_diameter;
    double dbl_transparency;

signals:
    void angleChanged();

public slots:
};

#endif // ANGLEPICKER_H
