/*
 * ipc_class.cpp
 *
 *  Created on: 11.04.2015
 *      Author: katerina
 */

#include "../header/ipc_class.h"

ipc_class::ipc_class()
{
	this->count = 0;
	this->index = "";
	checked = false;

}
ipc_class::ipc_class(QString & str,int num,QString doc_num)
{
	index = str;
	count = num;
	checked = false;
	doc_nums.insert(doc_num);
}

ipc_class::~ipc_class() {
	// TODO Auto-generated destructor stub
}
