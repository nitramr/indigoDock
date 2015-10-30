#include "mainwindow.h"
#include <QMainWindow>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/**
 * Simple program to attempt to drag dock widgets between
 * multiple main windows.
 */
/*
#include <QApplication>
#include <QMainWindow>
#include <QDockWidget>
#include <QLabel>
#include <QString>
#include <iostream>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>

class DraggableQDockWidget : public QDockWidget
{
   public:
      DraggableQDockWidget(QWidget* parent=0);
      ~DraggableQDockWidget();

   protected:
      bool event ( QEvent * event );
      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *event);
   private:
      void performDrag();
      QPoint dragStartPosition;
};


DraggableQDockWidget::DraggableQDockWidget(QWidget* parent) :
   QDockWidget(parent)
{
    //setTitleBarWidget(new QLabel("Title Bar Label Widget") );
}

DraggableQDockWidget::~DraggableQDockWidget()
{
}

bool DraggableQDockWidget::event ( QEvent * event )
{
    switch ( event->type() ) {
        case QEvent::MouseButtonPress:
        {
            QMouseEvent* me = static_cast<QMouseEvent*>(event);
            if (
                ( me->buttons() & Qt::LeftButton ) &&
                ( titleBarWidget() ) &&
                ( titleBarWidget()->frameGeometry().contains(me->pos()) )
            ) {
                dragStartPosition = me->pos();
            }
            break;
        }
        case QEvent::MouseMove:
        {
            QMouseEvent* me = static_cast<QMouseEvent*>(event);
            if ( me->buttons() & Qt::LeftButton ) {
                int distance = (me->pos()  -
dragStartPosition).manhattanLength();
                if ( distance >= QApplication::startDragDistance() ) {
                    performDrag();
                }
            }
            break;
        }
        case QEvent::HoverEnter:
        {

            break;
        }
        default:
           break;
    }
    return QDockWidget::event(event);
}

void DraggableQDockWidget::performDrag()
{
   QPoint pos = QCursor::pos();
   QWidget* widget = qApp->widgetAt(pos);
   qDebug() << widget << endl;
}

void DraggableQDockWidget::mousePressEvent(QMouseEvent *event)
{
   // std::cout << "Never called" << std::endl;
}

void DraggableQDockWidget::mouseMoveEvent(QMouseEvent *event)
{
   // std::cout << "Never called" << std::endl;
}


QMainWindow* createMainWindow(QString str)
{
    QMainWindow* mainWindow = new QMainWindow;
    mainWindow->setWindowTitle(str);
    mainWindow->setMouseTracking(true);
    mainWindow->acceptDrops();

    QLabel* label = new QLabel(mainWindow);
    label->setText(str);

    mainWindow->setCentralWidget(label);

    return mainWindow;
}

QDockWidget* createDockWidget(QString str)
{
    DraggableQDockWidget* dockWidget = new DraggableQDockWidget;

    QLabel* label = new QLabel(dockWidget);
    label->setText(str);

    dockWidget->setWidget(label);

    return dockWidget;
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QMainWindow* mainWindow1 = createMainWindow("Window 1");
    QMainWindow* mainWindow2 = createMainWindow("Window 2");

    QDockWidget* dockWidget = createDockWidget("Dock Widget");

    mainWindow1->addDockWidget(Qt::TopDockWidgetArea, dockWidget);
    mainWindow2->addDockWidget(Qt::TopDockWidgetArea, dockWidget);

    mainWindow1->show();
    mainWindow2->show();

    return app.exec();
}
*/
