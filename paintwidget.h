#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H


#include <QWidget>
#include <QPoint>
#include<vector>
#include"crossSection.h"

typedef struct myLine{
    QPoint startPnt;
    QPoint endPnt;
}myLine;

class MyPainterWidget: public QWidget
{
public:
    MyPainterWidget(QWidget* parent);
    ~MyPainterWidget();
    void paintEvent(QPaintEvent*p);
    std::vector<ring> vecRing;
    std::vector<rectangle> vecRec;
    std::vector<circle> vecEraRing;
    std::vector<rectangle> vecEraRec;
    void wheelEvent(QWheelEvent* event);
    QPoint startPnt=QPoint(0,0);   //起点
    QPoint endPnt=QPoint(0,0);     //终点
    bool isPressed=0;
    double ratio=1;
    int dx=0,dy=0;
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

};


#endif // PAINTWIDGET_H
