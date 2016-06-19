#include "widget.h"
#include "ui_widget.h"
#include"crossSection.h"
#include<QString>
#include<QMessageBox>
#include"chouxiang.h"
#include<QFile>
#include<QDebug>


shape operator+(shape shp1,shape shp2)
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


shape operator-(shape shp1,shape shp2)
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
}



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setGeometry(458,188,500,400);
    paintArea=new MyPainterWidget(this);

    QRect rec(0,0,800,800);
    paintArea->setGeometry(125,0,250,400);
    QString tempStr;
    tempStr="重心X坐标:"+QString::number(shp1.xc);
    ui->xcLabel->setText(tempStr);
    tempStr="重心Y坐标:"+QString::number(shp1.yc);
    ui->ycLabel->setText(tempStr);
    tempStr="面积:"+QString::number(shp1.area);
    ui->areaLabel->setText(tempStr);
    tempStr="Ix:"+QString::number(shp1.Ix);
    ui->ixLabel->setText(tempStr);
    tempStr="Iy:"+QString::number(shp1.Iy);
    ui->iyLabel->setText(tempStr);
    tempStr="Ixy:"+QString::number(shp1.Ixy);
    ui->ixyLabel->setText(tempStr);
    tempStr="Ixc:"+QString::number(shp1.Ixc());
    ui->ixcLabel->setText(tempStr);
    tempStr="Iyc:"+QString::number(shp1.Iyc());
    ui->iycLabel->setText(tempStr);
    tempStr="Ixyc:"+QString::number(shp1.Ixyc());
    ui->ixycLabel->setText(tempStr);
    tempStr=QString((shp1.xSymmetry)?"关于X对称  ":"") + QString((shp1.ySymmetry)?"关于Y对称":"");
    ui->symmLabel->setText(tempStr);

    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
    setWindowFlags (flags);

    connect(ui->addButton,SIGNAL(clicked()),paintArea,SLOT(repaint()));
    connect(ui->remButton,SIGNAL(clicked()),paintArea,SLOT(repaint()));
    connect(ui->clButton,SIGNAL(clicked()),paintArea,SLOT(repaint()));
    //connect(ui->clButton,SIGNAL(clicked()),paintArea,SLOT(clear()));

    QString strPath = QCoreApplication::applicationDirPath();
    qDebug()<<strPath;
    QString strCssFile = strPath + "/qss/sectionCalc.qss";
    QFile fCss(strCssFile);
    if( !fCss.open(QFile::ReadOnly))
    {
            //qDebug("css File %s load false",strCssFile);
            return;
    }
    QString strCssContent(fCss.readAll());
    qApp->setStyleSheet(strCssContent);
    fCss.close();

    paintArea->setStyleSheet("background-color:gray");
}

Widget::~Widget()
{
    delete ui;
}



void Widget::on_addButton_clicked()
{
    double x,y,up,down;
    QString valueStr=ui->xText->text();
    x=valueStr.toDouble();
    valueStr=ui->yText->text();
    y=valueStr.toDouble();
    valueStr=ui->upText->text();
    up=valueStr.toDouble();
    valueStr=ui->downText->text();
    down=valueStr.toDouble();
    switch (ui->comboBox->currentIndex()) {
    case 0:
        //shp1=addShp(shp1,rectangle(x,y,up,down));
        shp1=shp1+rectangle(x,y,up,down);
        paintArea->vecRec.push_back(rectangle(x,y,up,down));
        break;
    case 1:
        shp1=shp1+ring(x,y,up,0);
        paintArea->vecRing.push_back(ring(x,y,up,0));
        break;
    case 2:
        shp1=shp1+ring(x,y,up,0);
        paintArea->vecRing.push_back(ring(x,y,up,down));
        break;
    default:
        break;
    }

    showshp1();

}

void Widget::on_remButton_clicked()
{
    double x,y,up,down;
    QString valueStr=ui->xText->text();
    x=valueStr.toDouble();
    valueStr=ui->yText->text();
    y=valueStr.toDouble();
    valueStr=ui->upText->text();
    up=valueStr.toDouble();
    valueStr=ui->downText->text();
    down=valueStr.toDouble();
    int ret;
    switch (ui->comboBox->currentIndex()) {
    case 0:
        shp1=shp1-rectangle(x,y,up,down);
        paintArea->vecEraRec.push_back(rectangle(x,y,up,down));
        break;
    case 1:
        shp1=shp1-circle(x,y,up);
        paintArea->vecEraRing.push_back(circle(x,y,up));
        break;
    case 2:
        ret=QMessageBox::information(this,"提示","不支持圆环逻辑",QMessageBox::Ok);
    default:
        break;
    }

    showshp1();

}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        ui->upLabel->setText("宽度");
        ui->downLabel->setVisible(true);
        ui->downText->setVisible(true);
        ui->downLabel->setText("高度");
        break;
    case 1:
        ui->downLabel->setVisible(false);
        ui->downText->setVisible(false);
        ui->upLabel->setText("直径");
        break;
    case 2:
        ui->upLabel->setText("外径");
        ui->downLabel->setVisible(true);
        ui->downText->setVisible(true);
        ui->downLabel->setText("内径");
        break;
    }
}

void Widget::on_pushButton_clicked()
{
    chouxiang *cx=new chouxiang(0);
    cx->show();
}

void Widget::on_clButton_clicked()
{
    paintArea->vecEraRec.clear();
    paintArea->vecEraRing.clear();
    paintArea->vecRec.clear();
    paintArea->vecRing.clear();
    shp1=shape(0,0,0,0,0,0);
    paintArea->update();
    showshp1();
}

void Widget::showshp1(){
    QString valueStr;
    valueStr="重心X坐标:"+QString::number(shp1.xc);
    ui->xcLabel->setText(valueStr);
    valueStr="重心Y坐标:"+QString::number(shp1.yc);
    ui->ycLabel->setText(valueStr);
    valueStr="面积:"+QString::number(shp1.area);
    ui->areaLabel->setText(valueStr);
    valueStr="Ix:"+QString::number(shp1.Ix);
    ui->ixLabel->setText(valueStr);
    valueStr="Iy:"+QString::number(shp1.Iy);
    ui->iyLabel->setText(valueStr);
    valueStr="Ixy:"+QString::number(shp1.Ixy);
    ui->ixyLabel->setText(valueStr);
    valueStr="Ixc:"+QString::number(shp1.Ixc());
    ui->ixcLabel->setText(valueStr);
    valueStr="Iyc:"+QString::number(shp1.Iyc());
    ui->iycLabel->setText(valueStr);
    valueStr="Ixyc:"+QString::number(shp1.Ixyc());
    ui->ixycLabel->setText(valueStr);
    valueStr=QString((shp1.xSymmetry)?"关于X对称  ":"") + QString((shp1.ySymmetry)?"关于Y对称":"");
    ui->symmLabel->setText(valueStr);
}
