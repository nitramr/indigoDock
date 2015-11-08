#include "indigo2panel.h"

Indigo2Panel::Indigo2Panel(QWidget *parent) :
   QFrame(parent)
{

    QPalette palette;
    palette.setColor( QPalette::Background, QColor( 200, 200, 200 ) );
    setPalette( palette );
    setAutoFillBackground( true );

     //connect(qApp, SIGNAL(close(bool)) , this, SLOT(close(bool)));


}

void Indigo2Panel::mousePressEvent(QMouseEvent *event)
{


     qDebug() << "Pan2 Mouse Press" << endl;
     if (event->button() == Qt::LeftButton) {


        // QRect bodyRect = this->geometry();
         //QPoint xy = mapToParent(this->pos());

         //QPoint xy = mapToGlobal( this->pos() );

         QPoint xy = mapToGlobal(QPoint(0,0));
         // mouse press relative position
         relative_x = event->globalPos().x() - xy.x();
         relative_y = event->globalPos().y() - xy.y();



        // undock Panel
        if(parent() != NULL){
            qDebug() << "Pan2 Parent != 0" << endl;
            //const QPoint delta = event->globalPos();
            setParent(0);
            move(xy);
            setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint| Qt::FramelessWindowHint);
            show();


        }
//oldPos = event->globalPos();

        QWidget::mousePressEvent(event);
     }
}

void Indigo2Panel::mouseMoveEvent(QMouseEvent *event)
{

    // TODO: Highlight parent while enter

      /*const QPoint delta = event->globalPos() - oldPos;
      move(x()+delta.x(), y()+delta.y());
      oldPos = event->globalPos();*/
     move(QPoint(event->globalPos().x() - relative_x, event->globalPos().y() - relative_y));
}

void Indigo2Panel::mouseReleaseEvent ( QMouseEvent * event )
{

    // TODO: add panel to active parent tab

    emit mouseReleased();
}

void Indigo2Panel::close(bool * exit){

    if(exit){
        qDebug() << "Close" << endl;
    }

}
