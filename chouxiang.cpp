#include "chouxiang.h"
#include "ui_chouxiang.h"
#include"shapeinput.h"
#include<QMessageBox>
#include<QInputDialog>
#include<algorithm>

chouxiang::chouxiang(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chouxiang)
{
    ui->setupUi(this);
    ui->list1->setCurrentRow(0);
    showShpInfo(tolShp);
}

chouxiang::~chouxiang()
{
    delete ui;
}

void chouxiang::addShape(namedShp& shp){
    tolShp=tolShp+shp;
    int ret;
    if(shp.name!="全部")
    {   shpList[shp.name]=shape(shp.xc,shp.yc,shp.area,shp.Ix,shp.Iy,shp.Ixy);
        ui->list1->addItem(shp.name);}
    else    { ret=QMessageBox::information(this,"提示","不可以以全部为名",QMessageBox::Ok);}
    showShpInfo(tolShp);
}

void chouxiang::on_addButton_clicked()
{
    shapeInput* dlg=new shapeInput(this);
    connect(dlg,SIGNAL(dlgReturn(namedShp&)),this,SLOT(addShape(namedShp&)));
    dlg->show();
    ui->list1->setCurrentRow(0);

}

void chouxiang::on_list1_itemClicked(QListWidgetItem *item)
{
    QString str=item->text();
    if (str!="全部") {showShpInfo(shpList[str]);}
    else {showShpInfo(tolShp);}
}

void chouxiang::on_eraButton_clicked()
{
    QString str=ui->list1->currentItem()->text();
    if (str=="全部") {
        tolShp=shape(0,0,0,0,0,0);
        shpList.clear();
        ui->list1->clear();
        ui->list1->addItem("全部");

        }
    else{
        tolShp=tolShp-shpList[str];
        ui->list1->clear();
        ui->list1->addItem("全部");
        shpList.erase(str);
        std::map<QString,shape>::iterator p=shpList.end();
        for(std::map<QString,shape>::iterator iter=shpList.begin();iter!=p;++iter){
            ui->list1->addItem(iter->first);
        }
        }
    ui->list1->setCurrentRow(0);
}


void chouxiang::on_movButton_clicked()
{
    double x,y;
    bool ok;
    x=QInputDialog::getDouble(this,"","请输入X分量",0.00,-1111111111,1111111111,1,&ok);
    y=QInputDialog::getDouble(this,"","请输入X分量",0.00,-1111111111,1111111111,1,&ok);
    QString str=ui->list1->currentItem()->text();
    if (str=="全部") {
        tolShp.move(x,y);
        std::map<QString,shape>::iterator p=shpList.end();
        for(std::map<QString,shape>::iterator iter=shpList.begin();iter!=p;++iter){
            iter->second.move(x,y);
        }
        }
    else{
        tolShp=tolShp-shpList[str];
        shpList[str].move(x,y);
        tolShp=tolShp+shpList[str];
    }
    ui->list1->setCurrentRow(0);
    showShpInfo(tolShp);
}

void chouxiang::on_rotButton_clicked()
{
    double th;
    bool ok;
    th=QInputDialog::getDouble(this,"","请输入逆时针旋转角度数/°",0.00,-3000,3000,1,&ok)*3.1415926/180.0;
    QString str=ui->list1->currentItem()->text();
    if (str=="全部") {
        tolShp.rotate(th);
        std::map<QString,shape>::iterator p=shpList.end();
        for(std::map<QString,shape>::iterator iter=shpList.begin();iter!=p;++iter){
            iter->second.rotate(th);
        }
        }
    else{
        tolShp=tolShp-shpList[str];
        shpList[str].rotate(th);
        tolShp=tolShp+shpList[str];
    }
    ui->list1->setCurrentRow(0);
    showShpInfo(tolShp);
}

void chouxiang::showShpInfo(shape& shp1)
{
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



