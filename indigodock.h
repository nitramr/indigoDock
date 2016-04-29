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


class IndigoDock : public QDockWidget
{
    Q_OBJECT

public:

    IndigoDock(QWidget *parent = 0);
    void addIndigoPanel(IndigoPanel *panel, int tabIndex = -1);
    void hoverDock(IndigoPanel *pan);
    void dropPanel(IndigoPanel *pan);
    void removePanel(int index);
    QList<IndigoPanel*>getPanels();

private:

    QList<IndigoPanel*> lst_PanelList;
    QVBoxLayout * lyt_dropzone;

    IndigoTabBar * wdg_toolbar;
    QSplitter *wdg_mainSplitter;
    QSplitter *wdg_panelSplitter;
    QScrollArea * wdg_scrollArea_dz;
    QScrollArea * wdg_scrollArea_tb;
    QWidget *wdg_dropzone;
    QWidget * wdg_placeholder;

    int int_padding;
    int int_placeholderHeight;

    void updatePanels();
    void addPlaceholder (int index = -1);
    void removePlaceholder ();
    void addPanel (IndigoPanel *panel, int tabIndex);


protected:
    void resizeEvent(QResizeEvent *e);
    bool eventFilter(QObject *object, QEvent *event);

signals:
    void panelRemoved(int index);
    void panelAdded(QIcon icon,int index, QString);

public slots:

    void scrollToPanel(int PanelIndex);
    void scrollToPanel(QString PanelName);

    void movePanel(int oldIndex, int newIndex);


private slots:
     void updateTabPosition(Qt::DockWidgetArea area);
     void updateMinHeight();

};

#endif // INDIGODOCK_H
