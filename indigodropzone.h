#ifndef INDIGODROPZONE_H
#define INDIGODROPZONE_H

#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <indigopanel.h>
#include <indigotabbar.h>
#include <QSplitter>

class IndigoDropZone : public QWidget
{
    Q_OBJECT
public:
    IndigoDropZone(QWidget* parent = 0);
    void addPanel (IndigoPanel * panel);
    void setBackgroundColor(const QColor &bgColor);

    bool isHighlight;
    void addPlaceholder ();
    void removePlaceholder ();

protected:
    void paintEvent(QPaintEvent*);

private:
    QVBoxLayout *m_layout;
    QSplitter *m_splitter;
    int padding;
    int borderHighlight;
    QPalette palette;
    QColor colorHighlight;
    QColor colorHighlightAlpha;
    QColor colorNormal;
    double transparency;
    QWidget * m_placeholder;
    QColor blendColor(QColor color1, QColor color2, double ratio = 0);

signals:

public slots:
    void dropPanel();
    void hoverZone();
};

#endif // INDIGODROPZONE_H
