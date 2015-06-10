#include "../header/ipc_form.h"

IPC_form::IPC_form(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.syntaxButton,SIGNAL(clicked()),this,SLOT(syntax()));
	connect(ui.selectAllButton,SIGNAL(clicked()),this,SLOT(selectAll()));
	connect(ui.deselectButton,SIGNAL(clicked()),this,SLOT(deselect()));
}

IPC_form::~IPC_form()
{

}

void IPC_form::fillTable(QList<ipc_class> & list)
{
	ui.tableWidget->setRowCount(list.size());
	int j=0;
	QList<ipc_class>::iterator i;
	connectDatabase();
	for (i = list.begin(); i != list.end(); ++i)
	{
        QTableWidgetItem *item = new QTableWidgetItem("");
        if ((*i).checked) item->setCheckState(Qt::Checked);
        else item->setCheckState(Qt::Unchecked);
		QTableWidgetItem *item1 = new QTableWidgetItem((*i).index);
		QTableWidgetItem *item2 = new QTableWidgetItem(selectTitle((*i).index));
		QTableWidgetItem *item3 = new QTableWidgetItem(QString::number((*i).count));
		ui.tableWidget->setItem(j,0,item);
		ui.tableWidget->setItem(j,1,item1);
		ui.tableWidget->setItem(j,2,item2);
		ui.tableWidget->setItem(j,3,item3);
		j++;
	}
	this->show();
	disconnectDatabase();
}

void IPC_form::syntax()
{
	if(ui.tableWidget->rowCount())
	{
		for(int i=0;i<ui.tableWidget->rowCount();i++)
		{
			QTableWidgetItem *item = ui.tableWidget->item(i,0);
			if(item->checkState()==Qt::Checked)		emit changeCheckState(i,true);
			else	emit changeCheckState(i,false);
		}
		emit extractClaims();
	}
	else QMessageBox::warning(this,"Ошибка","Не обнаружено ни одного патента для анализа.");
}

void IPC_form::connectDatabase()
{
	const char *conninfo;
	conninfo = "dbname = info_database host=localhost user=engineer password=123";
	conn = PQconnectdb(conninfo);
	if (PQstatus(conn) != CONNECTION_OK)
		emit messageInLog("Не удалось подключиться к БД: " + QString::fromLocal8Bit(PQerrorMessage(conn)));
	//else emit messageInLog("Подключение к БД выполнено");
}

void IPC_form::disconnectDatabase()
{
	PQfinish(conn);
}

QString IPC_form::selectTitle(QString & ind)
{
	PGresult   *res;
	char * index;
	QString title_gotten;
	QByteArray bAr = ind.toLocal8Bit();
	index = bAr.data();
	const char * values [1] = {index};
	int lengths [1] = {strlen(index)};
	int binary [1] = {0};
	res = PQexecParams(conn, "select title from ipc_table where index=$1::varchar",1,NULL,values,lengths,binary,0);
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
		emit messageInLog("Данные не получены по причине: " + QString::fromLocal8Bit(PQerrorMessage(conn)));
	else title_gotten = QString::fromLocal8Bit(PQgetvalue(res, 0, 0));
	PQclear(res);
	return title_gotten;
}

void IPC_form::selectAll()
{
	for(int i=0;i<ui.tableWidget->rowCount();i++)
	{
		QTableWidgetItem *item = ui.tableWidget->item(i,0);
		item->setCheckState(Qt::Checked);
	}
}

void IPC_form::deselect()
{
	for(int i=0;i<ui.tableWidget->rowCount();i++)
	{
		QTableWidgetItem *item = ui.tableWidget->item(i,0);
		item->setCheckState(Qt::Unchecked);
	}
}

PGconn  * IPC_form::getConnection()
{
	return conn;
}
