#ifndef INDIGODROPZONE_H
#define INDIGODROPZONE_H

#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <indigopanel.h>
#include <QSplitter>
#include <QtGui>
#include <QList>

class IndigoDropZone : public QWidget
{
    Q_OBJECT
public:

    IndigoDropZone(QWidget* parent = 0);    
    QList<IndigoPanel*> PanelList;
    bool isHighlight;
    void addPanel (IndigoPanel * panel, int index = -1);
    void addPlaceholder (int index = -1);
    void removePlaceholder ();

protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    QVBoxLayout *m_layout;
    QSplitter *m_splitter;
    QWidget * m_placeholder;
    QColor colorHighlightAlpha;
    QColor blendColor(QColor color1, QColor color2, double ratio = 0);    
    int padding;
    int borderHighlight;
    int placeholderHeight;
    double transparency;    

    void redockPanel();
    void updatePanels();

signals:
    void resize();
    void panelRemoved(int index);
    void panelAdded(QIcon icon,int index);

public slots:
    void dropPanel();
    void hoverZone(int height);    
    void removePanel(int index);
    void movePanel(int oldIndex, int newIndex);

};

#endif // INDIGODROPZONE_H
