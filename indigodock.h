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
    QList<IndigoPanel*> PanelList;
    void addIndigoPanel(IndigoPanel *panel, int tabIndex = -1);

private:

    QHBoxLayout *m_layout;
    QScrollArea * m_scrollArea;   

signals:

public slots:
    void updateTabPosition(Qt::DockWidgetArea area);  
    void updateSize();


};

#endif // INDIGODOCK_H
