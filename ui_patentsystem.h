/********************************************************************************
** Form generated from reading UI file 'patentsystem.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATENTSYSTEM_H
#define UI_PATENTSYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PatentSystemClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *openButton;
    QPushButton *ipcButton;
    QPushButton *individSolutButton;
    QPushButton *infoButton;
    QSpacerItem *horizontalSpacer;
    QProgressBar *progressBar;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QTextEdit *textEdit;
    QWidget *tab_3;
    QGridLayout *gridLayout_4;
    QTableView *dxhView;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QTableView *morphView;

    void setupUi(QWidget *PatentSystemClass)
    {
        if (PatentSystemClass->objectName().isEmpty())
            PatentSystemClass->setObjectName(QStringLiteral("PatentSystemClass"));
        PatentSystemClass->resize(606, 437);
        PatentSystemClass->setMinimumSize(QSize(490,356));
        PatentSystemClass->setFocusPolicy(Qt::StrongFocus);
        gridLayout = new QGridLayout(PatentSystemClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        openButton = new QPushButton(PatentSystemClass);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(0, 0, 51, 41));
		QSize buttonSize(51,41);
		openButton->setFixedSize(buttonSize);
		openButton->setFocusPolicy(Qt::NoFocus);
		openButton->setStyleSheet("QPushButton {border-image: url(:/rec/icons/open_icon.png)} QPushButton:hover {background:QLinearGradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFF, stop:1 #6495ED);border:1px solid #838B8B;border-radius:5px} QPushButton:pressed {background:QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #6495ED, stop:1 #FFF);border:1px solid #696969;border-radius:5px}");
		openButton->setToolTip("Открыть XML-файл с патентным массивом");
        horizontalLayout->addWidget(openButton);

        ipcButton = new QPushButton(PatentSystemClass);
        ipcButton->setObjectName(QStringLiteral("ipcButton"));
        ipcButton->setGeometry(QRect(60, 0, 51, 41));
		ipcButton->setFocusPolicy(Qt::NoFocus);
		ipcButton->setFixedSize(buttonSize);
		ipcButton->setStyleSheet("QPushButton {border-image: url(:/rec/icons/ipc_icon_5.png)} QPushButton:hover {background:QLinearGradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFF, stop:1 #6495ED);border:1px solid #838B8B;border-radius:5px} QPushButton:pressed {background:QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #6495ED, stop:1 #FFF);border:1px solid #696969;border-radius:5px}");
		ipcButton->setToolTip("Определить индексы Международной Патентной Классификации");
        horizontalLayout->addWidget(ipcButton);

        individSolutButton = new QPushButton(PatentSystemClass);
        individSolutButton->setObjectName(QStringLiteral("individSolutButton"));
        individSolutButton->setGeometry(QRect(120, 0, 51, 41));
		individSolutButton->setFixedSize(buttonSize);
		individSolutButton->setFocusPolicy(Qt::NoFocus);
		individSolutButton->setToolTip("Запись в файл отдельных решений");
		individSolutButton->setStyleSheet("QPushButton {border-image: url(/home/katerina/workspace/Automated_system/icons/empty_page.png)} QPushButton:hover {background:QLinearGradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFF, stop:1 #6495ED);border:1px solid #838B8B;border-radius:5px} QPushButton:pressed {background:QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #6495ED, stop:1 #FFF);border:1px solid #696969;border-radius:5px}");
        horizontalLayout->addWidget(individSolutButton);

        infoButton = new QPushButton(PatentSystemClass);
        infoButton->setObjectName(QStringLiteral("infoButton"));
        infoButton->setFixedSize(buttonSize);
		infoButton->setGeometry(QRect(60, 0, 51, 41));
		infoButton->setFocusPolicy(Qt::NoFocus);
		infoButton->setStyleSheet("QPushButton {border-image: url(:/rec/icons/info_icon.png)} QPushButton:hover {background:QLinearGradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFF, stop:1 #6495ED);border:1px solid #838B8B;border-radius:5px} QPushButton:pressed {background:QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #6495ED, stop:1 #FFF);border:1px solid #696969;border-radius:5px}");
		infoButton->setToolTip("Информация о разработке");
        horizontalLayout->addWidget(infoButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        progressBar = new QProgressBar(PatentSystemClass);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);
        progressBar->setTextDirection(QProgressBar::TopToBottom);
        progressBar->setStyleSheet("QProgressBar:chunk {background: qlineargradient(x1: 0,y1: 0.5,x2: 1,y2: 0.5,stop: 0 #6495ED, stop:1 white);"
        			"border-bottom-left-radius: 8px;border-top-left-radius: 8px;border-bottom-right-radius: 8px;border-top-right-radius: 8px;border:1px solid #9FB6CD;}");
        progressBar->setAlignment(Qt::AlignCenter);
        gridLayout->addWidget(progressBar, 1, 0, 1, 1);

        tabWidget = new QTabWidget(PatentSystemClass);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setFocusPolicy(Qt::NoFocus);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        textEdit = new QTextEdit(tab);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setFrameShape(QFrame::StyledPanel);
        textEdit->setFrameShadow(QFrame::Sunken);
        textEdit->setReadOnly(true);
        textEdit->setTextColor(QColor("#000000"));
        gridLayout_2->addWidget(textEdit, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_4 = new QGridLayout(tab_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        dxhView = new QTableView(tab_3);
        dxhView->setObjectName(QStringLiteral("dxhView"));
        dxhView->setSelectionBehavior(QAbstractItemView::SelectRows );
        dxhView->resizeColumnsToContents();
        dxhView->setStyleSheet("QTableView::item:selected {background-color:#4F94CD}");
        dxhView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout_4->addWidget(dxhView, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        morphView = new QTableView(tab_2);
        morphView->setObjectName(QStringLiteral("morphView"));
        morphView->setShowGrid(true);
        morphView->resizeColumnsToContents();
		morphView->setStyleSheet("QTableView::item:selected {background-color:#4F94CD}");
		morphView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout_3->addWidget(morphView, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 2, 0, 1, 1);


        retranslateUi(PatentSystemClass);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PatentSystemClass);
    } // setupUi

    void retranslateUi(QWidget *PatentSystemClass)
    {
        PatentSystemClass->setWindowTitle(QApplication::translate("PatentSystemClass", "\320\220\320\262\321\202\320\276\320\274\320\260\321\202\320\270\320\267\320\270\321\200\320\276\320\262\320\260\320\275\320\275\320\260\321\217 \321\201\320\270\321\201\321\202\320\265\320\274\320\260 \320\260\320\275\320\260\320\273\320\270\320\267\320\260 \320\277\320\260\321\202\320\265\320\275\321\202\320\275\321\213\321\205 \320\274\320\260\321\201\321\201\320\270\320\262\320\276\320\262 \320\262 \320\267\320\260\320\264\320\260\321\207\320\260\321\205 \320\277\320\276\320\270\321\201\320\272\320\276\320\262\320\276\320\263\320\276 \320\272\320\276\320\275\321\201\321\202\321\200\321\203\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", 0));

        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("PatentSystemClass", "\320\233\320\276\320\263", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("PatentSystemClass", "\320\242\320\265\321\205\320\275\320\270\321\207\320\265\321\201\320\272\320\270\320\265 \321\204\321\203\320\275\320\272\321\206\320\270\320\270", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("PatentSystemClass", "\320\234\320\276\321\200\321\204\320\276\320\273\320\276\320\263\320\270\321\207\320\265\321\201\320\272\320\260\321\217 \321\202\320\260\320\261\320\273\320\270\321\206\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class PatentSystemClass: public Ui_PatentSystemClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATENTSYSTEM_H
