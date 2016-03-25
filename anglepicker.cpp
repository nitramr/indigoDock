#include "anglepicker.h"
#include "math.h"
#include <QStyle>
#include "qapplication.h"
#include "helper.h"


AnglePicker::AnglePicker(QWidget *parent)
    : QWidget(parent)
{
    //this->setFixedSize(30,30);

    diameter = 30;
    m_center = QPoint(this->diameter/2, this->diameter/2);
    m_pointer = QPoint(this->diameter/2, 0);
    m_lineThickness = 2;
    m_angle = 0;
    transparency = 0.55; // 10%

    circleFrame = QRect(1,1,this->diameter-m_lineThickness - 1, this->diameter-m_lineThickness -1);

    this->setFixedSize(diameter, diameter);
}



void AnglePicker::paintEvent(QPaintEvent*) {

    QPainter painter(this);
    QColor c_line = QColor(this->palette().color(QPalette::WindowText));
    QColor c_fill = Helper().blendColor(QColor(this->palette().color(QPalette::Background)),
                                        QColor(this->palette().color(QPalette::Highlight)),
                                        transparency);

    QBrush brush(c_fill);

    QPen pen;
    pen.setColor(c_line);
    pen.setWidth(m_lineThickness);

    painter.setRenderHint(QPainter::Antialiasing);

    // draw filled angle
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawPie(circleFrame, 0, 6000 / 360 * m_angle);
    painter.restore();

    painter.setPen(pen);

    // draw outer circle
    painter.drawEllipse(circleFrame);

    // darw angle line
    painter.save();
    painter.translate(m_center.x(), m_center.y());
    painter.rotate(-m_angle);
    painter.drawLine(0, 0, diameter/2 - m_lineThickness - 1, 0);
    painter.restore();


}


void AnglePicker::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton)
    {
        m_pointer = event->pos();

        QLineF *line = new QLineF(m_center, m_pointer);

        // rotate 0° to 12 o'clock
        double angle = line->angle();// -90;
       // if (angle > 0) angle -= 360;

        // invert counter direction
        m_angle = angle;

        update();

        emit angleChanged();

        qDebug() << "mouseDown" << m_pointer << "Angle is:" << m_angle << endl;


    }
}

double AnglePicker::Angle() {

    return m_angle;
}

void AnglePicker::setAngle(double degree){

    if (degree < 0) degree = 0;
    if (degree > 360) degree = 360;

    m_angle = degree;

}
