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
    void createPanel(const QString &title, QWidget *widget);
    void setBackgroundColor(const QColor &bgColor);

protected:

private:
    QVBoxLayout *layout;
    QSplitter *splitter;
    int padding;
    QPalette palette;
    QColor colorHighlight;
    QColor colorNormal;

signals:

public slots:
    void dropPanel();
    void hoverZone();
};

#endif // INDIGODROPZONE_H
