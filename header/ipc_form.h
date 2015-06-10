#ifndef IPC_FORM_H
#define IPC_FORM_H

//#include <QtGui/QWidget>
#include "ui_ipc_form.h"
#include <QList>
#include <QMessageBox>
#include "ipc_class.h"
#include </usr/include/postgresql/libpq-fe.h>

class IPC_form : public QWidget
{
    Q_OBJECT

public:
    IPC_form(QWidget *parent = 0);
    ~IPC_form();
    void fillTable(QList<ipc_class> & list);
    void connectDatabase();
    void disconnectDatabase();
    QString selectTitle(QString & ind);
    PGconn  * getConnection();

private:
    Ui::IPC_formClass ui;
    PGconn  *conn;

private slots:
    void syntax();
    void selectAll();
    void deselect();

signals:
	void changeCheckState(int k,bool state);
	void extractClaims();
	void messageInLog(QString message);

};

#endif // IPC_FORM_H
