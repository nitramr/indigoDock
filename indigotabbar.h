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
    Orientation tabPosition();
    void setTabPosition(Orientation tabOrientation);

    void insertTab(int index, QIcon &icon);

protected:
    QSize tabSizeHint (int) const {  return QSize(32,32);}
    void paintEvent(QPaintEvent *);

private:
   int int_iconScale;
   int int_oldIndex;
   int int_newIndex;
   Orientation m_tabOrientation;
   QIcon rotateIcon(const QIcon &icon, Orientation tabOrientation = North);
   void mousePressEvent(QMouseEvent*event);
   void mouseReleaseEvent(QMouseEvent*event);

signals:
   void tabMoved(int,int);

public slots:
    void addTab(QIcon icon, int index = -1);
    void removeTab(int index);
    void hideTab(int index);
    void showTab(int index);
};

#endif // INDIGOTABBAR_H
