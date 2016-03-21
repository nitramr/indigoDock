#ifndef INDIGOTABBAR_H
#define INDIGOTABBAR_H

#include <QtWidgets>
#include <QWidget>
#include <QIcon>

class IndigoTab : public QWidget
{
    Q_OBJECT
public:

    enum Display{
        visible,
        hidden,
        inactive // currently unused
    };

    IndigoTab(QIcon icon, QWidget* parent = 0);
    void setIcon(QIcon icon);
    QIcon Icon();
    void setDisplayState(Display display);
    Display displayState();

private:
    QIcon m_icon;
    Display m_display;

};

/****************************************/

class IndigoTabBar : public QWidget
{
    Q_OBJECT
public:

    enum Orientation{
        East,
        West
    };

    IndigoTabBar(QWidget* parent = 0);

    QList<IndigoTab*> TabList;

    int currentIndex();
    Orientation tabPosition();
    void setTabPosition(Orientation tabOrientation);
    void setTabSize(int side);
    void setTabSize(int width, int height);


protected:   
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent*event);
    void mouseReleaseEvent(QMouseEvent*event);
    void mouseMoveEvent(QMouseEvent*event);
    void leaveEvent(QEvent *);

private:
   int int_tabWidth;
   int int_tabHeight;
   int int_gap;
   int borderHighlight;
   double transparency;

   int int_hoverIndex;

   int int_oldIndex;
   int int_newIndex;

   bool dragProceed;
   int dragPosition;
   int int_dragIndex;

   Orientation m_tabOrientation;
   QColor colorHighlightAlpha;

   int realTabIndex(int mouseY);
   int fakeTabIndex(int mouseY);

   void moveTab();


signals:
   void tabMoved(int,int);
   void scrollToPanel(int);

public slots:
    void addTab(QIcon icon);
    void insertTab(QIcon icon, int index);
    void removeTab(int index);
    void hideTab(int index);
    void showTab(int index);

};

#endif // INDIGOTABBAR_H
