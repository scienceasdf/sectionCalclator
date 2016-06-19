#ifndef SHAPEINPUT_H
#define SHAPEINPUT_H

#include <QDialog>
#include"crossSection.h"

namespace Ui {
class shapeInput;
}

class shapeInput : public QDialog
{
    Q_OBJECT

public:
    explicit shapeInput(QWidget *parent = 0);
    ~shapeInput();

private slots:


    void on_OKpush_clicked();

    void on_cancelButton_clicked();

private:
    Ui::shapeInput *ui;
signals:
    void dlgReturn(namedShp&);
};

#endif // SHAPEINPUT_H
