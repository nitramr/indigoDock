#ifndef INDIGODOCK_H
#define INDIGODOCK_H

#include <QWidget>
#include "indigopanel.h"
#include "indigodropzone.h"
#include "indigotabbar.h"



class IndigoDock : public QWidget
{
    Q_OBJECT
public:


    explicit IndigoDock(QWidget *parent = 0);
    IndigoDropZone * m_dropzone;
    IndigoTabBar * m_toolbar;    
    QList<IndigoPanel *> getPanelList();
    void addIndigoPanel(IndigoPanel *panel, int tabIndex = -1);


private:

    QHBoxLayout *m_layout;
    QScrollArea * m_scrollArea_dz;
    QScrollArea * m_scrollArea_tb;
    int dropZoneInitHeight;
    void resizeEvent(QResizeEvent *e);


signals:


public slots:
    void updateTabPosition(Qt::DockWidgetArea area);
    void scrollToPanel(int PanelIndex);
    void scrollToPanel(QString PanelName);
    void resizeScrollPanel();



};

#endif // INDIGODOCK_H
