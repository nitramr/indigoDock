#ifndef INDIGODROPZONE_H
#define INDIGODROPZONE_H

#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <indigopanel.h>
#include <QSplitter>
#include <QtGui>
#include <QList>
#include <QListWidget>


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


class IndigoDropZone : public QWidget
{
    Q_OBJECT
public:

    IndigoDropZone(QWidget* parent = 0);    
    QList<IndigoPanel*> PanelList;
    bool isHighlight;
    int minHeight;
    int lastPanelHeight;
    void addPanel (IndigoPanel * panel, int index = -1);
    void addPlaceholder (int index = -1);
    void removePlaceholder ();

protected:
    void paintEvent(QPaintEvent*); 

private:
    QVBoxLayout *m_layout;
    IndigoSplitter *m_splitter;
    QWidget * m_placeholder;
    QColor colorHighlightAlpha;
    QColor blendColor(QColor color1, QColor color2, double ratio = 0);    
    int padding;
    int borderHighlight;
    int placeholderHeight;
    double transparency;

    void updatePanels();  

signals:
    void panelRemoved(int index);
    void panelAdded(QIcon icon,int index);
    void contentResize();

public slots:
    void dropPanel();
    void hoverZone();
    void removePanel(int index);
    void movePanel(int oldIndex, int newIndex);
    QRect getPanelRect(int index, bool addPadding = true);
    void updateMinHeight();

};

#endif // INDIGODROPZONE_H
