#ifndef SECTION_H
#define SECTION_H

#include<QString>

class shape{
    public:
        double xc,yc;
        double area;
        double Ix,Iy,Ixy;
        shape(double x,double y,double A,double ix,double iy,double ixy);
        shape();
        bool xSymmetry;
        bool ySymmetry;
        double Ixc();
        double Iyc();
        double Ixyc();
        shape& move(double& x, double& y);
        shape& rotate(double theta);

};

class rectangle:public shape{
    public:
        double h,b;
        rectangle(double& x,double& y,double& wid,double& hei);
        //void draw();
        //...
};

class  circle:public shape{
    public:
        double diameter;
        circle(double& x,double& y,double& d);
        //void draw();
        //...
};

class ring:public shape{
    public:
        double outerDiameter, innerDiameter;
        ring(double& x,double& y,double& d2,double  d1);
        //void draw();
        //...
};

class namedShp:public shape{
public:
    QString name;
    namedShp(double x,double y,double A,double ix,double iy,double ixy,QString qstr):shape(x,y,A,ix,iy,ixy),name(qstr) {}
};

shape operator+(shape shp1,shape shp2);
shape operator-(shape shp1,shape shp2);

bool Intersect(rectangle& rect, circle& cir);
bool Intersect(circle& cir, rectangle& rect);
bool Intersect(rectangle& rect1, rectangle& rect2);

#endif // SECTION_H
