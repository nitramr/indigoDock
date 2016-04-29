#ifndef INDIGOTABBAR_H
#define INDIGOTABBAR_H

#include <QtWidgets>
#include <QWidget>
#include <QIcon>


//
// IndigoTab
//


class IndigoTab : public QWidget
{
    Q_OBJECT
public:

    enum Display{
        Visible,
        Hidden
    };

    // unused
    enum ActiveState{
        Enabled,
        Disabeld
    };

    IndigoTab(QIcon icon, QWidget* parent = 0);
    void setIcon(QIcon icon);
    QIcon Icon();
    void setDisplayState(Display display);
    Display displayState();

private:
    QIcon ico_icon;
    Display m_display;

};


//
// IndigoTabBar
//


class IndigoTabBar : public QWidget
{
    Q_OBJECT
public:

    enum Orientation{
        Horizontal,
        Vertical
    };

    IndigoTabBar(QWidget* parent = 0);

    QList<IndigoTab*> lst_TabList;

    int currentIndex();
    Orientation TabOrientation();
    void setTabOrientation(Orientation tabDirection);
    void setTabSize(int side);
    void setTabSize(int width, int height);


protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent*event);
    void mouseReleaseEvent(QMouseEvent*event);
    void mouseMoveEvent(QMouseEvent*event);
    void leaveEvent(QEvent *event);


private:
   int int_tabWidth;
   int int_tabHeight;
   int int_gap;
   int int_borderHighlight;
   double dbl_transparency;
   int int_hoverIndex;
   int int_oldIndex;
   int int_newIndex;
   bool bool_dragProceed;
   bool bool_hover;
   QPoint pnt_dragPosition;
   int int_realIndex;
   int int_dragIndex;
   int int_minDimension;

   Orientation m_tabOrientation;
   QColor col_colorHighlightAlpha;

   int realTabIndex(int mouseAxis);
   int fakeTabIndex(int mouseAxis);
   int countVisibleTabs();
   int countHiddenTabs();

   void moveTab();
   void calculateSize();


signals:
   void tabMoved(int,int);
   void tabClicked(int);

public slots:
    void addTab(QIcon icon, QString toolTip = "");
    void insertTab(QIcon icon, int index, QString toolTip = "");
    void removeTab(int index);
    void hideTab(int index);
    void showTab(int index);
    void hoverTabBar();
    void leaveTabBar();

};

#endif // INDIGOTABBAR_H
