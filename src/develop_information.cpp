#include "../header/develop_information.h"

develop_information::develop_information(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);
	connect(ui.okButton,SIGNAL(clicked()),this,SLOT(agree()));
}

develop_information::~develop_information()
{

}

void develop_information::agree()
{
	close();
}
