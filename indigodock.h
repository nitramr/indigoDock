#ifndef INDIGODOCK_H
#define INDIGODOCK_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <QtGui>
#include <QList>

#include "indigopanel.h"
#include "indigotabbar.h"
#include "helper.h"



//
// IndigoSplitter
//

class IndigoSplitter : public QSplitter
{
    Q_OBJECT
private:
    void resizeEvent(QResizeEvent *e);
public:
    IndigoSplitter(QWidget* parent = 0);
signals:
    void resize();
};


//
// IndigoDock
//

class IndigoDock : public QDockWidget
{
    Q_OBJECT
public:


    IndigoDock(QWidget *parent = 0);
    IndigoTabBar * wdg_toolbar;
    void addIndigoPanel(IndigoPanel *panel, int tabIndex = -1);


private:

    QList<IndigoPanel*> lst_PanelList;
    QWidget *wdg_dropzone;
    QWidget * wdg_placeholder;
    QVBoxLayout * lyt_dropzone;
    IndigoSplitter *wdg_splitter;
    //QHBoxLayout *lyt_main;
    QGridLayout *lyt_main;
    QScrollArea * wdg_scrollArea_dz;
    QScrollArea * wdg_scrollArea_tb;

    int int_padding;
    int int_placeholderHeight;

    void updatePanels();
    void addPlaceholder (int index = -1);
    void removePlaceholder ();
    void addPanel (IndigoPanel *panel, int tabIndex);

protected:
    //void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

signals:
    void panelRemoved(int index);
    void panelAdded(QIcon icon,int index, QString);

public slots:


    void scrollToPanel(int PanelIndex);
    void scrollToPanel(QString PanelName);

    void hoverDock();
    void dropPanel();

    void removePanel(int index);
    void movePanel(int oldIndex, int newIndex);

    void updateMinHeight();

private slots:
     void updateTabPosition(Qt::DockWidgetArea area);

};

#endif // INDIGODOCK_H
