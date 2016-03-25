#ifndef INDIGOLABELCONTROL_H
#define INDIGOLABELCONTROL_H

#include <QWidget>
#include <QtGui>
#include <QLayout>
#include <QLabel>

class IndigoLabelControl : public QWidget
{
       Q_OBJECT
public:
    IndigoLabelControl(QWidget *parent = 0);

    void setWidget(QWidget *widget, int width = -1);
    QWidget *Widget();

    void setLabel(QIcon icon, int iconSize = 22, Qt::Alignment alignment = false);
    void setLabel(QString string, int width = 22, Qt::Alignment alignment = false);
    void setLabel(QWidget *widget, int width = 22, Qt::Alignment alignment = false);
    QIcon Icon();
    QWidget *Label();


private:
    QIcon m_icon;
    QWidget *m_label;
    QWidget *m_widget;
    QHBoxLayout *m_widgetLayout;
    QHBoxLayout *m_labelLayout;

    int m_iconSize;

signals:

public slots:
};

#endif // INDIGOLABELCONTROL_H
