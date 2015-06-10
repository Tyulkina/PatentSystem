#include "../header/patentsystem.h"

PatentSystem::PatentSystem(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.openButton,SIGNAL(clicked()),this,SLOT(open()));
	connect(ui.ipcButton,SIGNAL(clicked()),this,SLOT(showIPCtable()));
	connect(&o1,SIGNAL(changeCheckState(int,bool)),this,SLOT(updateCheckState(int,bool)));
	connect(&o1,SIGNAL(extractClaims()),this,SLOT(sentences()));
	connect(ui.infoButton,SIGNAL(clicked()),&o2,SLOT(show()));
	connect(&o1,SIGNAL(messageInLog(QString)),this,SLOT(receiveMessageInLog(QString)));
	connect(ui.individSolutButton,SIGNAL(clicked()),this,SLOT(writeIndividSolut()));
	ui.progressBar->setVisible(false);
	ui.tabWidget->setCurrentIndex(0);
}

void PatentSystem::open()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Открытие файла"), "/home/katerina/study/",
	        tr("XML Files (*.xml)"));
	if(!filename.isEmpty())
	{
		countSe = 0;
		patentCount = 1;
		documentCount = 1;
		ipc_indexes.clear();
		DXH.clear();
		QStandardItemModel *model = new QStandardItemModel(this);
		ui.dxhView->setModel(model);
		ui.morphView->setModel(model);
		QString filename_to =  filename;
		QString filename_out = filename;
	    file_from.setFileName(filename);
	    file_to.setFileName(filename_to.insert(filename_to.indexOf(".xml"),"_processed"));
	    file_out.setFileName(filename_out.replace(filename_out.indexOf(".xml"),4,"_output.txt"));
		enum ParseElement parse_option = Utility;
		ui.progressBar->setMaximum(file_from.size());
		ui.progressBar->setVisible(true);
		if(fileOpening())
		{
			ui.textEdit->setTextColor(QColor("#2925A9"));
			ui.textEdit->append("исходный файл " +filename+ " успешно открыт");
			ui.textEdit->setTextColor(QColor("#000000"));
			ui.textEdit->append("файл для записи " +filename_to+ " успешно открыт\nначало обработки...");
			t.start();
			primaryProcessing();
			ui.textEdit->append("количество документов, представленных в файле = " + QString::number(documentCount));
			ui.textEdit->append("количество патентов = " + QString::number(patentCount));
			xmlParsing(parse_option);
			ui.textEdit->append("обработка завершена");
			QString time = "времени потрачено: " + QString::number(t.elapsed()) + " мс";
			ui.textEdit->append(time);
		}
		else  ui.textEdit->append("обработка не может быть произведена");
	}
}

void PatentSystem::showIPCtable()
{
	o1.fillTable(ipc_indexes);
}

PatentSystem::~PatentSystem()
{

}

bool PatentSystem::fileOpening()
{
	bool from_open = true, to_open = true;
	if(!file_from.open(QIODevice::ReadWrite))
	{
		ui.textEdit->append("ошибка при открытии файла-источника");
		from_open = false;
	}
	if(!file_to.open(QIODevice::WriteOnly))
	{
		ui.textEdit->append("ошибка при открытии файла-назначения");
		to_open = false;
	}
	if(from_open && to_open)
	{
		return true;
	}
	else return false;
}

void PatentSystem::bytesPlus(QString & line, QTextStream & text_to, int * bytes)
{
	QByteArray bytesArray;
	text_to << line << endl;
	bytesArray = line.toUtf8();
	*bytes += bytesArray.size()+1;
}

void PatentSystem::primaryProcessing()
{
	QTextStream text_from(&file_from);
	QTextStream text_to(&file_to);
	int j=-1;
	QString line;
	QRegExp xmlheader ("\\<\\?xml version=(.+) encoding=(.+)\\?\\>");
	QRegExp patent_grant ("\\<us-patent-grant(.+)\\>");
	text_to << text_from.readLine()<<endl;
	text_to << text_from.readLine()<<endl;
	line = "<patent-array>";
	text_to << line <<endl;
	int bytes = 114;
	while(!text_from.atEnd())
	{
		QCoreApplication::processEvents();
		line=text_from.readLine();
		j = xmlheader.indexIn(line);
		if(j!=0)	bytesPlus(line,text_to,&bytes);
		else
		{
			line=text_from.readLine();
			documentCount++;
			bytes+=114;
			line=text_from.readLine();
			if(patent_grant.indexIn(line)==0)
			{
				patentCount++;
			}
			bytesPlus(line,text_to,&bytes);
		}
		ui.progressBar->setValue(bytes);
	}
	line = "</patent-array>";
	text_to << line <<endl;
	ui.textEdit->append("запись завершена");
	ui.progressBar->setValue(file_from.size());
	file_from.close();
	file_to.close();
}

void PatentSystem::xmlParsing(ParseElement element)
{
	if(!file_to.open(QIODevice::ReadOnly))
		ui.textEdit->append("ошибка при открытии файла для xml парсинга");
	else ui.textEdit->append("файл для xml парсинга был успешно открыт");
	if(!file_out.open(QIODevice::WriteOnly))
		ui.textEdit->append("ошибка при открытии файла для вывода");
	QXmlStreamReader xml(&file_to);
	if(element==Utility)	utilityCount(xml);
	else if (element==Claims) claimsDetecting(xml);
	if(xml.hasError())
	{
		ui.textEdit->append("при парсинге файла была обнаружена ошибка:");
		ui.textEdit->append(xml.errorString());
	}
	else	ui.textEdit->append("парсинг файла успешно завершен");
	file_to.close();
	file_out.close();
}

void PatentSystem::utilityCount(QXmlStreamReader & xml)
{
	ui.textEdit->append("определение индексов МПК патентов...");
	int utility = 0;
	ui.progressBar->setMaximum(patentCount);
	int y=0;
	while (!xml.atEnd())
	{
		QCoreApplication::processEvents();
		QXmlStreamReader::TokenType token = xml.readNext();
		if (token==QXmlStreamReader::StartElement && xml.name()=="us-patent-grant")
		{
			y++;
			ui.progressBar->setValue(y);
			bool singlePatent = true;
			QString doc;
			while(singlePatent && (xml.name()!="classifications-ipcr" || xml.tokenType()!=QXmlStreamReader::EndElement))
			{
				token=xml.readNext();
				if (token==QXmlStreamReader::StartElement && xml.name()=="publication-reference")
					doc = docNumbDetecting(xml);
				else if (token==QXmlStreamReader::StartElement && xml.name()=="application-reference")
				{
					if(xml.attributes().value("appl-type").toString()=="utility")
						utility ++;
					else singlePatent = false;
				}
				else if(token==QXmlStreamReader::StartElement && xml.name()=="classification-ipcr")
					ipcDeterminating(xml,doc);
			}
		}
	}
	ui.textEdit->append("количество патентов на изобретения = " + QString::number(utility));
}

QString PatentSystem::docNumbDetecting(QXmlStreamReader & xml)
{
	while(!(xml.readNext()==QXmlStreamReader::StartElement && xml.name()=="doc-number"));
	xml.readNext();
	return xml.text().toString();
}

void PatentSystem::ipcDeterminating(QXmlStreamReader & xml,QString num)
{
	QString ipc_index;
	while(xml.readNext()!=QXmlStreamReader::EndElement || xml.name()!="classification-ipcr")
	{
		if((xml.name()=="section" || xml.name()=="class") && xml.tokenType()==QXmlStreamReader::StartElement)
		{
			if (xml.readNext()==QXmlStreamReader::Characters)
				ipc_index.append(xml.text());
		}
	}
	QList<ipc_class>::iterator i;
	bool detected = false;
	for (i = ipc_indexes.begin(); i != ipc_indexes.end() && !detected; ++i)
	{
	    if((*i).index==ipc_index)
		{
	    	if(!(*i).doc_nums.contains(num))
	    	{
				(*i).count++;
				(*i).doc_nums.insert(num);
	    	}
	    	detected = true;
		}
	}
	if(!detected)
	{
		ipc_class new_detected(ipc_index,1,num);
   		ipc_indexes.append(new_detected);
	}
}

void PatentSystem::claimsDetecting(QXmlStreamReader & xml)
{
	ui.textEdit->append("выделение формул патентов на изобретения...");
	ui.progressBar->setMaximum(patentCount);
	int y=0;
	while (!xml.atEnd())
	{
		QCoreApplication::processEvents();
		QString doc;
		if (xml.readNext()==QXmlStreamReader::StartElement && xml.name()=="publication-reference")
		{
			doc = docNumbDetecting(xml);
			ui.progressBar->setValue(y);
			if(patentNumbersForClaims.contains(doc)) claimsExtracting(xml);
			y++;
		}
	}
	ui.progressBar->setValue(patentCount);
}

void PatentSystem::claimsExtracting(QXmlStreamReader & xml)
{
	bool continueCycle = true;
	while(continueCycle)
	{
		if(xml.readNext()==QXmlStreamReader::StartElement && xml.name()=="claim" &&
					xml.attributes().value("id").toString()=="CLM-00001")
		{
			QString q_claim;
			while(xml.readNext()!=QXmlStreamReader::EndElement || xml.name()!="claim")
			{
				if (xml.tokenType()==QXmlStreamReader::Characters)
				{
					q_claim += xml.text().toString();
				}
			}
			continueCycle = false;
			claimsSegmenting(q_claim);
		}
	}
}

void PatentSystem::claimsSegmenting(QString & str)
{
	str.remove(" said");
	QTextStream text_out(&file_out);
	QRegExp divider ("(\\n|;|, |which|wherein)");
	QStringList h = str.split(divider);
	h.removeDuplicates();
    //вывод полученных сегментов формулы
	QStringList::iterator Iterator;
    for (Iterator = h.begin(); Iterator != h.end(); ++Iterator)
    {
    	QCoreApplication::processEvents();
    	text_out << lineParsing(*Iterator) << endl;
    }
}

int PatentSystem::parseElementsDefining()
{
	QList<ipc_class>::iterator i;
	for (i = ipc_indexes.begin(); i != ipc_indexes.end() ; ++i)
	{
		if((*i).checked)		patentNumbersForClaims.unite((*i).doc_nums);
	}
	ui.textEdit->append("Для разбора найдено "+QString::number(patentNumbersForClaims.size())+" патентов");
	return patentNumbersForClaims.size();
}

void PatentSystem::updateCheckState(int k,bool state)
{
	ipc_indexes[k].checked=state;
	if(state) ui.textEdit->append("Для анализа выбран индекс "+ipc_indexes[k].index);
}

void PatentSystem::sentences()
{
	t.restart();
	enum ParseElement parse_option = Claims;
	verb_classes.clear();
	patentNumbersForClaims.clear();
	countSe = 0;
	if(parseElementsDefining()==0)	return;
	parseSettings();
	xmlParsing(parse_option);
	DXHTable();
	morphTable();
	QString time = "На определение технических функций и построение морфологической таблицы было потрачено " + QString::number(t.elapsed()) + " мс";
	ui.textEdit->append(time);
}

QString PatentSystem::classSearching(QString & verb)
{
	PGresult   *res;
	QByteArray bAr = verb.toLocal8Bit();
	char * word = bAr.data();
	const char * values [1] = {word};
	int lengths [1] = {strlen(word)};
	int binary [1] = {0};
	int rec_count;
	QString ret_class;
	res = PQexecParams(o1.getConnection(), "select class_table.text_class from class_table,verb_table where verb_table.word=$1::varchar and verb_table.id_class=class_table.id_class",1,NULL,values,lengths,binary,0);
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		ui.textEdit->append("Данные не получены по причине: " + QString::fromLocal8Bit(PQerrorMessage(o1.getConnection())));
		PQclear(res);
	}
	rec_count = PQntuples(res);
	//Берем только первый найденный класс
	if(rec_count>0)		ret_class = QString::fromLocal8Bit(PQgetvalue(res, 0, 0)).trimmed();
	PQclear(res);
	return ret_class;
}

void PatentSystem::DXHTable()
{
	// Отображение "действие-объект-условие"
	dictionary_delete(dict);
	parse_options_delete(opts);
	QList<function>::iterator iter;
	QStandardItemModel *model_1 = new QStandardItemModel(DXH.size(),3,this);
	model_1->setColumnCount(3);
	model_1->setHorizontalHeaderItem(0, new QStandardItem(QString("Действие")));
	model_1->setHorizontalHeaderItem(1, new QStandardItem(QString("Объект")));
	model_1->setHorizontalHeaderItem(2, new QStandardItem(QString("Условие")));
	int u = 0;
	for (iter = DXH.begin(); iter != DXH.end(); ++iter)
	{
		QStandardItem *firstRow = new QStandardItem(QString((*iter).action));
		model_1->setItem(u,0,firstRow);
		QStandardItem *secondRow = new QStandardItem(QString((*iter).object));
		model_1->setItem(u,1,secondRow);
		QStandardItem *thirdRow = new QStandardItem(QString((*iter).condition));
		model_1->setItem(u,2,thirdRow);
		u++;
	}
	ui.dxhView->setModel(model_1);
	ui.dxhView->resizeColumnsToContents();
	ui.tabWidget->setCurrentIndex(1);
}

void PatentSystem::writeIndividSolut()
{
	if(DXH.isEmpty())
	{
		QMessageBox::warning(this,"Ошибка","Морфологическая таблица ещё не заполнена.");
		ui.textEdit->append("Морфологическая таблица ещё не заполнена, файл с отдельными решениями не может быть записан.");
		return;
	}
	QItemSelectionModel * selection_model = ui.morphView->selectionModel();
	if(selection_model->hasSelection())
	{
		QString filename_individSolut = file_from.fileName().replace(file_from.fileName().indexOf(".xml"),4,"_separate_solutions.txt");
		QFile file_individSolut(filename_individSolut);
		if(filename_individSolut.isEmpty() || !file_individSolut.open(QIODevice::WriteOnly))
		{
			ui.textEdit->append("Невозможно открыть файл для записи отдельных решений");
			return;
		}
		QTextStream text_individSolut(&file_individSolut);
		QAbstractItemModel *model = ui.morphView->model();
		QModelIndexList list = selection_model->selectedIndexes();
		foreach(QModelIndex index,list)
		{
			text_individSolut << model->headerData(index.column(),Qt::Horizontal).toString()+": "+model->data(index,Qt::DisplayRole).toString() << endl;
		}
		ui.textEdit->append("файл " + file_individSolut.fileName()+" с отдельными решениями успешно записан на диск");
		file_individSolut.close();
	}
	else ui.textEdit->append("Ни одна ячейка морфологической таблицы не выделена, файл с отдельными решениями не был записан.");

}

void PatentSystem::morphTable()
{
	int class_count = verb_classes.size();
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setColumnCount(class_count + 1);
    for (int i=0;i<class_count;i++)
    {
      	 model->setHorizontalHeaderItem(i, new QStandardItem(verb_classes[i]));
    	 model->horizontalHeaderItem(i)->setData(0,Qt::UserRole);
    }
    model->setHorizontalHeaderItem(class_count, new QStandardItem(QString(" ")));
	QList<function>::iterator iter;
	for (iter = DXH.begin(); iter != DXH.end(); ++iter)
	{
		QString technical_function = (*iter).action+(*iter).object+(*iter).condition;
		QStandardItem *item = new QStandardItem(technical_function);
		if((*iter).class_no==-1) (*iter).class_no = class_count;
		int row_num = model->horizontalHeaderItem((*iter).class_no)->data(Qt::UserRole).toInt();
		model->setItem(row_num,(*iter).class_no,item);
		row_num++;
		model->horizontalHeaderItem((*iter).class_no)->setData(row_num,Qt::UserRole);
	}
	ui.morphView->setModel(model);
	ui.morphView->resizeColumnsToContents();
	ui.tabWidget->setCurrentIndex(2);
}

void PatentSystem::parseSettings()
{
	opts = parse_options_create();
	parse_options_set_max_null_count(opts,6);
	parse_options_set_display_morphology(opts,0); //Отображение морфологии - функция не работает
	parse_options_set_islands_ok(opts, true);//Использование островов ссылок допустимо
	parse_options_set_linkage_limit(opts,10); //Ограничение по количеству пост-обрабатываемых связей (по умолчанию 100)
	dict = dictionary_create_lang("en");
	parse_options_set_disjunct_cost(opts, 2);
	if (!dict)		ui.textEdit->append("Критическая ошибка: невозможно открыть словарь.");
	DXH.clear();
	parse_options_set_use_cluster_disjuncts(opts,true);
}

QString PatentSystem::truncateMorphology(const char * input_string)
{
	QString str = QString::fromLocal8Bit(input_string);
	int r = str.indexOf("[");
	if(r < 0)	r = str.indexOf(".");
	if(r > 0)	str.truncate(r);
	return str;
}

QString PatentSystem::lineParsing(QString & line)
{
	QByteArray byteArray;
	char * input_string;
	Sentence sent;
	Linkage      	linkage;
	char *        	diagram;
	QString d;
	int           	num_linkages;
	if(!line.isEmpty())
	{
		byteArray = line.toLocal8Bit();
		input_string = byteArray.data();
		sent = sentence_create(input_string, dict);
		sentence_split(sent, opts);
		num_linkages = sentence_parse(sent, opts);
		countSe++;
		if (num_linkages > 0)
		{
			QCoreApplication::processEvents();
			linkage = linkage_create(0, sent, opts);
			diagram = linkage_print_diagram(linkage, false, 800);
			d = QString::fromLocal8Bit(diagram); //вывод диаграммы связей
			int linksCount = linkage_get_num_links(linkage);
			for(int j=0;j<linksCount;j++)
			{
				reviewLinks(linkage,j);
			}
			linkage_free_diagram(diagram);
			if(actionIndex.size())
			{
				elementsGathering(linkage);
			}
			linkage_delete(linkage);
		}
		else	d=line+"\nВ предложении не было обнаружено связей!\n";
		sentence_delete(sent);
		d+=QString::number(countSe);
	}
	return d;
}

void PatentSystem::prepositionsProcessing(const Linkage linkage,int j)
{
	int prep_num = linkage_get_link_rword(linkage,j);
	QString prep = linkage_get_word(linkage,prep_num);
	if(prep.indexOf("than")==0)
	{
		actionIndex.append(prep_num);
		return;
	}
	else if(prep.indexOf("to")==0)
	{
		int linksCount = linkage_get_num_links(linkage);
		for(int k=0;k<linksCount;k++)
		{
			QString link = QString::fromLocal8Bit(linkage_get_link_label(linkage,k));
			if(link=="I")//Ix - ??
			{
				if(linkage_get_link_lword(linkage,k)==prep_num)
				{
					actionIndex.append(prep_num);
					return;
				}
			}
		}
	}
	conditionIndex.append(prep_num);
}

void PatentSystem::reviewLinks(Linkage linkage,int j)
{
	QString link = QString::fromLocal8Bit(linkage_get_link_label(linkage,j));
	if(!link.indexOf("MV"))
	{
		startNonTerminal(linkage,j);
		prepositionsProcessing(linkage,j);
	}
	else if (!link.indexOf("O") && link[1]!='F')
	{
		startNonTerminal(linkage,j);
		objectIndex.append(linkage_get_link_rword(linkage,j));
	}
	else if (!link.indexOf("M") && link[1]!='J')		rightSidedLinks(linkage,j);
	else if (!link.indexOf("J"))		rightSidedLinks(linkage,j);
	else if (!link.indexOf("OF"))		rightSidedLinks(linkage,j);
	else if (!link.indexOf("I"))
	{
		if(actionIndex.contains(linkage_get_link_lword(linkage,j)))
			actionIndex.append(linkage_get_link_rword(linkage,j));
	}
	else if (!link.indexOf("A"))		leftSidedLinks(linkage,j);
	else if (!link.indexOf("SJl"))		leftSidedLinks(linkage,j);
	else if (!link.indexOf("SJr"))		rightSidedLinks(linkage,j);
	else if (!link.indexOf("MJl"))		leftSidedLinks(linkage,j);
	else if (!link.indexOf("MJr"))		rightSidedLinks(linkage,j);
	else if (!link.indexOf("AJl"))		leftSidedLinks(linkage,j);
	else if (!link.indexOf("AJr"))		rightSidedLinks(linkage,j);
}


QString PatentSystem::infinitiveGetting(QString verb_initial,int * n)
{
	QString verb = verb_initial;
	int i,j,k;
	QRegExp suffix_3 ("(ing)");
	QRegExp suffix_2 ("(ed|es)");
	QRegExp suffix_1 ("(s)");
	i = suffix_3.lastIndexIn(verb);
	j = suffix_2.lastIndexIn(verb);
	k = suffix_1.lastIndexIn(verb);
	if(i==verb.size()-3)		verb.truncate(i);
	else if(j==verb.size()-2)	verb.truncate(j);
	else if(k==verb.size()-1)	verb.truncate(k);
	QString vetra = classSearching(verb);
	if(vetra.isEmpty())
	{
		verb.append("e");
		vetra = classSearching(verb);
	}
	if(vetra.isEmpty())
	{
		*n = -1;
		return verb_initial;
	}
	else
	{
		if(verb_classes.contains(vetra))
		{
			*n = verb_classes.indexOf(vetra);
		}
		else
		{
			*n = verb_classes.size();
			verb_classes << vetra;
		}
		return verb;
	}
}

void PatentSystem::elementsGathering(const Linkage linkage)
{
	o1.connectDatabase();
	qSort(actionIndex);
	qSort(conditionIndex);
	qSort(objectIndex);
	function variable;
	QList<int>::iterator iter;
	for (iter = actionIndex.begin(); iter != actionIndex.end(); ++iter)
	{
		variable.action+=infinitiveGetting(truncateMorphology(linkage_get_word(linkage,*iter)),&variable.class_no) +  " ";
	}
	for (iter = objectIndex.begin(); iter != objectIndex.end(); ++iter)
	{
		variable.object+=truncateMorphology(linkage_get_word(linkage,*iter)) + " ";
	}
	for (iter = conditionIndex.begin(); iter != conditionIndex.end(); ++iter)
	{
		variable.condition+=truncateMorphology(linkage_get_word(linkage,*iter)) + " ";
	}
	DXH.append(variable);
	o1.disconnectDatabase();
	conditionIndex.clear();
	objectIndex.clear();
	actionIndex.clear();
}

void PatentSystem::rightSidedLinks(Linkage linkage,int j)
{
	if(conditionIndex.contains(linkage_get_link_lword(linkage,j)))
	{
		conditionIndex.append(linkage_get_link_rword(linkage,j));
	}
	else if(objectIndex.contains(linkage_get_link_lword(linkage,j)))
	{
		objectIndex.append(linkage_get_link_rword(linkage,j));
	}
}

void PatentSystem::leftSidedLinks(Linkage linkage,int j)
{
	if(conditionIndex.contains(linkage_get_link_rword(linkage,j)))
	{
		conditionIndex.append(linkage_get_link_lword(linkage,j));
	}
	else if(objectIndex.contains(linkage_get_link_rword(linkage,j)))
	{
		objectIndex.append(linkage_get_link_lword(linkage,j));
	}
}

void PatentSystem::startNonTerminal(Linkage linkage,int j)
{
	if(actionIndex.size()==0) actionIndex.append(linkage_get_link_lword(linkage,j));
	if(!actionIndex.contains(linkage_get_link_lword(linkage,j)))
	{
		elementsGathering(linkage);
		actionIndex.append(linkage_get_link_lword(linkage,j));
	}
}

void PatentSystem::receiveMessageInLog(QString message)
{
	ui.textEdit->append(message);
}
