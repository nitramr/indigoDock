#ifndef TEXTBOXSIMULATOR_H
#define TEXTBOXSIMULATOR_H

#include <QtWidgets>
#include <QWidget>

class TextBoxSimulator : public QWidget
{
       Q_OBJECT
public:
    TextBoxSimulator(QWidget *parent = 0);

private:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent * );

    bool bool_clicked;
    bool bool_dblclick;

signals:
    void mousePressed();
    void mouseDoubleClick();

public slots:
};

#endif // TEXTBOXSIMULATOR_H
