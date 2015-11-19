#ifndef INDIGOEXPANDERGROUP_H
#define INDIGOEXPANDERGROUP_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QtGui>
#include <QPolygon>


class IndigoExpanderLabel : public QLabel
{
    Q_OBJECT
public:
    explicit IndigoExpanderLabel(QWidget *parent = 0);
    void collapsed(bool);

private:
    bool collapse;
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *e);

    int margin_left;
    int spacing;
    int icon_size;

signals:
    void stateSwitch(bool);
public slots:
};

/*******************************************************/

class IndigoExpanderGroup : public QWidget
{
    Q_OBJECT
public:
    explicit IndigoExpanderGroup(QWidget *parent = 0);
    void addWidget(QWidget * widget);
    void setCaption(const QString text);

private:
    QPalette palette;
    QVBoxLayout *m_contentArea;
    IndigoExpanderLabel * m_handle;
    QWidget * m_widget;

signals:

public slots:
    void stateSwitch(bool);
};



#endif // INDIGOEXPANDERGROUP_H
