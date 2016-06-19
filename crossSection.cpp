#include "crossSection.h"
#include<cmath>

#define PI 3.1415926

double shape::Ixc(){
    return (Ix-area*yc*yc);
}

 double shape::Iyc(){
    return (Iy-area*xc*xc);
}

 double shape::Ixyc(){
    return (Ixy-area*xc*yc);
}

 shape& shape::rotate(double theta)
 {
     double ix=Ix,iy=Iy,ixy=Ixy;
     Iy=(ix+iy)*.5+.5*(ix-iy)*cos(2.0*theta)-ixy*sin(2.0*theta);
     Iy=(ix+iy)*.5-.5*(ix-iy)*cos(2.0*theta)+ixy*sin(2.0*theta);
     Ixy=(ix-iy)*sin(2.0*theta)+ixy*cos(2.0*theta);
     ix=xc;iy=yc;
     xc=ix*cos(theta)+iy*sin(theta);
     yc=iy*cos(theta)-ix*sin(theta);
     return *this;
 }

 shape& shape::move(double& x,double& y)
{
    Ix=Ixc()+area*(yc+y)*(yc+y);
    Iy=Iyc()+area*(xc+x)*(xc+x);
    Ixy=Ixyc()+area*(yc+y)*(xc+x);
    xc+=x;
    yc+=y;      //These should be written here or the Ixc, Iyc will return a wrong number
    xSymmetry=(yc==0) && (Ixy==0);
    ySymmetry=(xc==0) && (Ixy==0);
    return *this;
}

 shape::shape()
{
    xc=0;
    yc=0;
    area=0;
    Ix=0;
    Iy=0;
    Ixy=0;
    xSymmetry=1;
    ySymmetry=1;
}

 shape::shape(double x,double y,double A,double ix,double iy,double ixy)
{
    xc=x;
    yc=y;
    area=A;
    Ix=ix;
    Iy=iy;
    Ixy=ixy;
    xSymmetry=(y==0) && (ixy==0);
    ySymmetry=(x==0) && (ixy==0);
}


 /*template<class shape1, class shape2>
 shape operator+(shape1 &shp1, shape2 &shp2)
 {
     shape shp;
     double s=shp1.area+shp2.area;
     double cx=(shp1.xc*shp1.area+shp2.xc*shp2.area)/s;
     double cy=(shp1.yc*shp1.area+shp2.yc*shp2.area)/s;
     double Ixx=shp1.Ix+shp2.Ix;
     double Iyy=shp1.Iy+shp2.Iy;
     double Ixxy=shp1.Ixy+shp2.Ixy;
     shp=shape(cx,cy,s,Ixx,Iyy,Ixxy);
     return shp;
 }

 template<class shape1, class shape2>
 shape operator-(shape1 &shp1, shape2 &shp2)
 {
     shape shp;
     double s=shp1.area-shp2.area;
     double cx=(shp1.xc*shp1.area-shp2.xc*shp2.area)/s;
     double cy=(shp1.yc*shp1.area-shp2.yc*shp2.area)/s;
     double Ixx=shp1.Ix-shp2.Ix;
     double Iyy=shp1.Iy-shp2.Iy;
     double Ixxy=shp1.Ixy-shp2.Ixy;
     shp=shape(cx,cy,s,Ixx,Iyy,Ixxy);
     return shp;
 }*/


 rectangle::rectangle(double& x,double& y,double& wid,double& hei)
{
    xc=x;
    yc=y;
    h=hei;
    b=wid;
    area=hei*wid;
    Iy=b*h*h*h/12.0+area*y*y;
    Ix=h*b*b*b/12.0+area*x*x;
    Ixy=x*y*area;
    xSymmetry=! y;
    ySymmetry=! x;
}



 circle::circle(double& x, double& y, double& d)
{
    xc=x;
    yc=y;
    diameter=d;
    area=PI*d*d/4.0;
    Ix=PI*d*d*d*d/64+area*y*y;
    Iy=PI*d*d*d*d/64+area*x*x;
    Ixy=x*y*area;
    xSymmetry=!y;
    ySymmetry=!x;
}

 ring::ring(double& x,double& y,double& d2,double  d1)
{
    xc=x;
    yc=y;
    innerDiameter=d1;
    outerDiameter=d2;
    area=PI*(d2*d2-d1*d1)/4.0;
    Ix=PI*(d2*d2*d2*d2-d1*d1*d1*d1)/64+area*y*y;
    Iy=PI*(d2*d2*d2*d2-d1*d1*d1*d1)/64+area*x*x;
    Ixy=x*y*area;
    xSymmetry=!y;
    ySymmetry=!x;
}

