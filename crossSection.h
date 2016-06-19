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
        /*template<class shape1>shape& operator+=(shape1 &shp1)
        {
            shape shp;
            double s=shp1.area+area;
            double cx=(shp1.xc*shp1.area+xc*area)/s;
            double cy=(shp1.yc*shp1.area+yc*area)/s;
            double Ixx=shp1.Ix+Ix;
            double Iyy=shp1.Iy+Iy;
            double Ixxy=shp1.Ixy+Ixy;
            shp=shape(cx,cy,s,Ixx,Iyy,Ixxy);
            return shp;
        }*/

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
/*shape operator+(shape &shp1,ring &shp2);
shape operator-(shape &shp1,ring &shp2);
shape operator+(shape &shp1,rectangle &shp2);
shape operator-(shape &shp1,rectangle &shp2);*/
/*template<class shape1, class shape2>
shape operator+(shape1 &shp1, shape2 &shp2);
template<class shape1, class shape2>
shape operator-(shape1 &shp1, shape2 &shp2);
template<class shape1>*/

#endif // SECTION_H
