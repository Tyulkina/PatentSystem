/*
 * ipc_class.h
 *
 *  Created on: 11.04.2015
 *      Author: katerina
 */

#ifndef IPC_CLASS_H_
#define IPC_CLASS_H_
#include <QString>
#include <QSet>


class ipc_class
{
public:
	ipc_class();
	ipc_class(QString & str,int num,QString doc_num);
	virtual ~ipc_class();
	QString index;
	int count;
	bool checked;
	QSet <QString> doc_nums;
};

#endif /* IPC_CLASS_H_ */
