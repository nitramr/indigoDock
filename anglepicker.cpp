#include "anglepicker.h"
#include "math.h"
#include <QStyle>
#include "qapplication.h"


AnglePicker::AnglePicker(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(30,30);

    m_center = QPoint(this->width()/2, this->height()/2);
    m_pointer = QPoint(this->width()/2, 0);
    m_lineThickness = 2;
}

void AnglePicker::paintEvent(QPaintEvent*) {

    QPainter painter(this);
    QPen pen;

    QColor c_line = QColor(this->palette().color(QPalette::WindowText));

    pen.setColor(c_line);
    pen.setWidth(m_lineThickness);

    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(1,1,this->height()-m_lineThickness - 1, this->width()-m_lineThickness -1);

    painter.drawLine(m_center.x(), m_center.y(), m_pointer.x(), m_pointer.y());

}


void AnglePicker::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton)
    {
        m_pointer = event->pos();

        update();

        qDebug() << "mouseDown" << m_pointer << endl;


    }
}

float AnglePicker::getAngle(QPoint centerPt, QPoint targetPt) {

       /* qreal theta = qAtan2(targetPt.y() - centerPt.y(), targetPt.x() - centerPt.x());

        theta += M_PI/2.0;

        // convert from radians to degrees
        // this will give you an angle from [0->270],[-180,0]
        double angle = Math.toDegrees(theta);

        if (angle < 0) {
            angle += 360;
        }

        return angle;*/
    return 0;
}
