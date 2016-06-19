#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"paintwidget.h"
#include"crossSection.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    MyPainterWidget *paintArea;
    shape shp1=shape(0,0,0,0,0,0);
    void showshp1();
private slots:
    void on_addButton_clicked();

    void on_remButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_clButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
