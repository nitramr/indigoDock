#ifndef INDIGODROPZONE_H
#define INDIGODROPZONE_H

#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <indigopanel.h>
#include <indigotabbar.h>
#include <QSplitter>
#include <QtGui>

class IndigoDropZone : public QWidget
{
    Q_OBJECT
public:
    IndigoDropZone(QWidget* parent = 0);
    void addPanel (IndigoPanel * panel, int index = -1);

    bool isHighlight;
    void addPlaceholder (int height = 10);
    void removePlaceholder ();
    void movePanel(int newIndex, QString name);

protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *event);

private:
    QVBoxLayout *m_layout;
    QSplitter *m_splitter;
    int padding;
    int borderHighlight;
    QColor colorHighlightAlpha;
    double transparency;
    QWidget * m_placeholder;  
    QColor blendColor(QColor color1, QColor color2, double ratio = 0);

signals:
    void resize();

public slots:
    void dropPanel();
    void hoverZone(int height);
};

#endif // INDIGODROPZONE_H
