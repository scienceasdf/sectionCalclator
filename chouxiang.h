#ifndef CHOUXIANG_H
#define CHOUXIANG_H

#include <QWidget>
#include<map>
#include<QString>
#include"crossSection.h"
#include<QListWidgetItem>

namespace Ui {
class chouxiang;
}

class chouxiang : public QWidget
{
    Q_OBJECT

public:
    explicit chouxiang(QWidget *parent = 0);
    ~chouxiang();
    std::map<QString,shape> shpList;
    shape tolShp;
    void showShpInfo(shape& shp);
public slots:
    void addShape(namedShp& shp);
private slots:
    void on_addButton_clicked();

    void on_eraButton_clicked();

    void on_movButton_clicked();

    void on_rotButton_clicked();

    void on_list1_itemClicked(QListWidgetItem *item);

private:
    Ui::chouxiang *ui;
};

#endif // CHOUXIANG_H
