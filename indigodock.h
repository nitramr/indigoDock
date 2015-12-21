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
    void addIndigoPanel(IndigoPanel *panel, int tabIndex = -1);

private:

    QHBoxLayout *m_layout;
    QScrollArea * m_scrollArea;
    void addPanel(IndigoPanel * panel, int index = -1 );    


signals:

public slots:
    void updateTabPosition(Qt::DockWidgetArea area);
    void movePanel(int oldIndex, int newIndex);
    void removeTab(int index);
    void updateSize();
    void addTab(QIcon icon, int index);


};

#endif // INDIGODOCK_H
