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
    void movePanel(int oldIndex, int newIndex);


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
    void updatePanels();
    void redockPanel();


signals:
    void resize();
    void panelRemoved(int);
    void panelAdded(QIcon,int);

public slots:
    void dropPanel();
    void hoverZone(int height);    
    void removePanel(int index);
};

#endif // INDIGODROPZONE_H
