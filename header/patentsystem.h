#ifndef PATENTSYSTEM_H
#define PATENTSYSTEM_H

#include <QWidget>
#include "ui_patentsystem.h"
#include "link-includes.h"
#include <QTextEdit>
#include "ipc_form.h"
#include "ipc_class.h"
#include "develop_information.h"
#include <QFileDialog>
#include <QTime>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QString>
#include <QStandardItemModel>
#include </usr/include/postgresql/libpq-fe.h>

class function
{
public:
	QString action;
	QString condition;
	QString object;
	int class_no;		//Индекс класса глагола в массиве QStringList verb_classes
};


class PatentSystem : public QWidget
{
    Q_OBJECT

public:
    PatentSystem(QWidget *parent = 0);
    ~PatentSystem();

    enum ParseElement
    {
		Utility = 0x0000,
		Claims = 0x0001
    };
    bool fileOpening();
    void primaryProcessing();
    void claimsDetecting(QXmlStreamReader & xml);
    void claimsExtracting(QXmlStreamReader & xml);
    void claimsSegmenting(QString & str);
    void ipcDeterminating(QXmlStreamReader & xml, QString num);
    void utilityCount(QXmlStreamReader & xml);
    void xmlParsing(ParseElement element);
    void bytesPlus(QString & line, QTextStream & text_to, int * bytes);
    QString docNumbDetecting(QXmlStreamReader & xml);
    int parseElementsDefining();
    void morphTable();
    void DXHTable();
    void parseSettings();
    QString truncateMorphology(const char * input_string);
    QString lineParsing(QString & line);
    void reviewLinks(Linkage linkage,int j);
    void startNonTerminal(Linkage linkage,int j);
    void rightSidedLinks(Linkage linkage,int j);
    void leftSidedLinks(Linkage linkage,int j);
    void elementsGathering(const Linkage linkage);
    QString classSearching(QString & verb);
    QString infinitiveGetting(QString verb,int * n);
    void prepositionsProcessing(const Linkage linkage,int j);

private:
    Ui::PatentSystemClass ui;
    QFile file_from;
    QFile file_to;
    QFile file_out;
    QTime t;
    int patentCount;
    int documentCount;
    QList <ipc_class> ipc_indexes;
    IPC_form o1;
    develop_information o2;
    QSet <QString> patentNumbersForClaims;
    Dictionary dict;
    Parse_Options opts;
    QList <int> actionIndex;
	QList <int> conditionIndex;
	QList <int> objectIndex;
	QList <function> DXH;
	int countSe;
	QStringList verb_classes;

private slots:
    void open();
    void showIPCtable();
    void updateCheckState(int k,bool state);
    void sentences();
    void receiveMessageInLog(QString message);
    void writeIndividSolut();
};



#endif // PATENTSYSTEM_H
