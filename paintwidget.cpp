#include "paintwidget.h"
#include <QString>
#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include<QBrush>
#include<algorithm>


//int dx=0,dy=0;

//const int cenX=125;
//const int cenY=200;


MyPainterWidget::MyPainterWidget(QWidget* parent)
     :QWidget(parent) {
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    //setMinimumSize(240, 120);
    //setMaximumSize(620, 840);
    this->setMouseTracking(true);

}

MyPainterWidget::~MyPainterWidget() {

}


void MyPainterWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPen pen;                                 //创建一个画笔
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    QBrush brush(QColor(0,0,255),Qt::Dense4Pattern);
    pen.setWidth(2);

    painter.setBrush(brush);
    painter.scale(ratio,ratio);
    painter.drawLine(QPoint(dx+125,dy-1e4),QPoint(dx+125,dy+400+1e4));
    painter.drawLine(QPoint(0+dx-1e4,200+dy),QPoint(250+dx+1e4,200+dy));
    std::for_each(vecRec.begin(),vecRec.end(),
                  [&painter,this] (rectangle& rec){painter.drawRect((rec.xc-rec.b/2.0)+dx+125,(rec.yc-rec.h/2.0)+dy+200,rec.b,rec.h);});
    //brush(QColor(0,0,255),Qt::Dense4Pattern);
    painter.setBrush(brush);
    std::for_each(vecRing.begin(),vecRing.end(),
                  [&painter,&brush,this] (ring& ring){painter.drawEllipse(QPoint(ring.xc+dx+125,ring.yc+dy+200),(int)(ring.outerDiameter/2.0),(int)(ring.outerDiameter/2.0));
                                                brush.setColor(Qt::gray);
                                                painter.setBrush(brush);
                                                painter.drawEllipse(QPoint(ring.xc+dx+125,ring.yc+dy+200),(int)(ring.innerDiameter/2.0),(int)(ring.innerDiameter/2.0));
                                                brush.setColor(QColor(0,0,255));
                                                painter.setBrush(brush);});
    std::for_each(vecEraRec.begin(),vecEraRec.end(),
                  [&painter,&brush,this] (rectangle& rec){brush.setColor(Qt::gray);
                                    painter.setBrush(brush);
                                    painter.drawRect((rec.xc-rec.b/2.0)+dx+125,(rec.yc-rec.h/2.0)+dy+200,rec.b,rec.h);
                                    brush.setColor(QColor(0,0,255));
                                    painter.setBrush(brush);});
    std::for_each(vecEraRing.begin(),vecEraRing.end(),
                  [&painter,&brush,this] (circle& ring){brush.setColor(Qt::gray);
                                    painter.setBrush(brush);
                                    painter.drawEllipse(QPoint(ring.xc+dx+125,ring.yc+dy+200),(int)(ring.diameter/2.0),(int)(ring.diameter/2.0));
                                    brush.setColor(QColor(0,0,255));
                                    painter.setBrush(brush);});
}

void MyPainterWidget::wheelEvent(QWheelEvent* event){
    if(event->delta()>0){
        ratio*=1.5;
    }
    else{
        ratio/=1.5;
    }
    update();

}

void MyPainterWidget::mousePressEvent(QMouseEvent *e) {
    setCursor(Qt::PointingHandCursor);
    startPnt = e->pos();
    endPnt = e->pos();
    this->isPressed = true;
    //QString msg ="("+QString::number(e->x())+","+QString::number(e->y())+")";
    //QMessageBox::warning(this,tr("Warning"),msg,QMessageBox::Ok);

}

void MyPainterWidget::mouseMoveEvent(QMouseEvent *e) {
    if (this->isPressed) {
        endPnt = e->pos();
        dx-=startPnt.x()-endPnt.x();
        dy-=startPnt.y()-endPnt.y();
        update();                                    //repainter，call paintEvent
        startPnt = endPnt;

    }

}

void MyPainterWidget::mouseReleaseEvent(QMouseEvent *e) {
    setCursor(Qt::ArrowCursor);
    this->isPressed = false;

}


