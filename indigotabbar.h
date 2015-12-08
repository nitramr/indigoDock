#ifndef INDIGOTABBAR_H
#define INDIGOTABBAR_H

#include <QtWidgets>
#include <QTabWidget>
#include <QIcon>

class IndigoTabBar : public QTabBar
{
    Q_OBJECT
public:

    enum Orientation{
        East,
        West,
        North,
        South
    };



    IndigoTabBar(QWidget* parent = 0);
    void setTabPosition(Orientation tabOrientation);
    void addTab(QIcon &icon);
    void insertTab(int index, QIcon &icon);
    int oldTabIndex();
    int newTabIndex();

protected:

private:
   int int_iconScale;
   int int_oldIndex;
   int int_newIndex;
   QIcon rotateIcon(const QIcon &icon, Orientation tabOrientation = North);
   void mousePressEvent(QMouseEvent*event);
   void mouseReleaseEvent(QMouseEvent*event); 

signals:
   void moveTab();

public slots:

};

#endif // INDIGOTABBAR_H
