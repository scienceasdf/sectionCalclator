#include "shapeinput.h"
#include "ui_shapeinput.h"
#include"crossSection.h"

shapeInput::shapeInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::shapeInput)
{
    ui->setupUi(this);
}

shapeInput::~shapeInput()
{
    delete ui;
}


void shapeInput::on_OKpush_clicked()
{
    double x=ui->XBox->value();
    double y=ui->YBox->value();

    double area=ui->areaBox->value();
    double ix=ui->ixcBox->value()+area*y*y;     //CAUTION!!!
    double iy=ui->iycBox->value()+area*x*x;     //CAUTION!!!
    double ixy=ui->ixycBox->value()+area*x*y;
    namedShp tempshp(x,
                     y,
                     area,
                     ix,
                     iy,
                     ixy,
                     ui->nameText->text());
    emit dlgReturn(tempshp);
    close();
}

void shapeInput::on_cancelButton_clicked()
{
    close();
}
