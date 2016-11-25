#include "crossSection.h"
#include<cmath>
#include<QDebug>

#define PI 3.1415926

shape operator+(shape &shp1,shape &shp2)
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

shape operator-(shape &shp1,shape &shp2)
{
    shape shp;
    double s=shp1.area-shp2.area;
    double cx=(s!=0)?(shp1.xc*shp1.area-shp2.xc*shp2.area)/s:0;
    double cy=(s!=0)?(shp1.yc*shp1.area-shp2.yc*shp2.area)/s:0;
    double Ixx=shp1.Ix-shp2.Ix;
    double Iyy=shp1.Iy-shp2.Iy;
    double Ixxy=shp1.Ixy-shp2.Ixy;
    shp=shape(cx,cy,s,Ixx,Iyy,Ixxy);
    return shp;
}


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



 rectangle::rectangle(double& x,double& y,double& wid,double& hei)
{
    xc=x;
    yc=y;
    h=hei;
    b=wid;
    area=hei*wid;
    Ix=b*h*h*h/12.0+area*y*y;
    Iy=h*b*b*b/12.0+area*x*x;
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

bool Intersect(rectangle& rect, circle& cir)
{
    //Algorithm from the Internet
    //Milo Yip's answer in Zhihu
    //https://www.zhihu.com/question/24251545
    //It can work in n-dimension condition
    double v[]={abs(rect.xc-cir.xc),abs(rect.yc-cir.yc)};
    double u[]={0,0};
    double h[]={rect.b/2.0,rect.h/2.0};
    u[0]=((v[0]-h[0])>0)?(v[0]-h[0]):.0;
    u[1]=((v[1]-h[1])>0)?(v[1]-h[1]):.0;
    return (u[0]*u[0]+u[1]*u[1])<(cir.diameter*cir.diameter/4.0);
}

bool Intersect(circle& cir, rectangle& rect)
{
    double v[]={abs(rect.xc-cir.xc),abs(rect.yc-cir.yc)};
    double u[]={0,0};
    double h[]={rect.b/2.0,rect.h/2.0};
    u[0]=((v[0]-h[0])>0)?(v[0]-h[0]):.0;
    u[1]=((v[1]-h[1])>0)?(v[1]-h[1]):.0;
    return (u[0]*u[0]+u[1]*u[1])<(cir.diameter*cir.diameter/4.0);
}

bool Intersect(rectangle& rect1, rectangle& rect2)
{
    double minx1=rect1.xc-rect1.b/2.0;
    double miny1=rect1.yc-rect1.h/2.0;
    double maxx1=rect1.xc+rect1.b/2.0;
    double maxy1=rect1.yc+rect1.h/2.0;
    double minx2=rect2.xc-rect2.b/2.0;
    double miny2=rect2.yc-rect2.h/2.0;
    double maxx2=rect2.xc+rect2.b/2.0;
    double maxy2=rect2.yc+rect2.h/2.0;
    double minx=std::min(minx1,minx2);
    double miny=std::min(miny1,miny2);
    double maxx=std::max(maxx1,maxx2);
    double maxy=std::max(maxy1,maxy2);
    return ((minx<maxx)||(miny<maxy));
}
