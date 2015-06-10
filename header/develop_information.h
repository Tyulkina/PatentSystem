#ifndef DEVELOP_INFORMATION_H
#define DEVELOP_INFORMATION_H

//#include <QtGui/QWidget>
#include "ui_develop_information.h"

class develop_information : public QWidget
{
    Q_OBJECT

public:
    develop_information(QWidget *parent = 0);
    ~develop_information();

private:
    Ui::develop_informationClass ui;

private slots:
    void agree();
};

#endif // DEVELOP_INFORMATION_H
