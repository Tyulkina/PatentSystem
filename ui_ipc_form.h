/********************************************************************************
** Form generated from reading UI file 'ipc_form.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPC_FORM_H
#define UI_IPC_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IPC_formClass
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *selectAllButton;
    QPushButton *deselectButton;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QPushButton *syntaxButton;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *IPC_formClass)
    {
        if (IPC_formClass->objectName().isEmpty())
            IPC_formClass->setObjectName(QStringLiteral("IPC_formClass"));
        IPC_formClass->resize(535, 352);
        IPC_formClass->setMinimumSize(QSize(395,266));
        gridLayout = new QGridLayout(IPC_formClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(IPC_formClass);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setColumnWidth(0,70);
		tableWidget->setColumnWidth(2,370);
		tableWidget->setColumnWidth(3,170);
		tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
		tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
		tableWidget->setStyleSheet("QTableView::item:selected {background-color:#4F94CD}");
		tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows );
        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        selectAllButton = new QPushButton(IPC_formClass);
        selectAllButton->setObjectName(QStringLiteral("pushButton_2"));
        selectAllButton->setStyleSheet("QPushButton:hover {background:QLinearGradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFF, stop:1 #6495ED);border:1px solid #838B8B;border-radius:5px} QPushButton:pressed {background:QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #6495ED, stop:1 #FFF);border:1px solid #696969;border-radius:5px}");
        selectAllButton->setFocusPolicy(Qt::NoFocus);
        verticalLayout->addWidget(selectAllButton);

        deselectButton = new QPushButton(IPC_formClass);
        deselectButton->setObjectName(QStringLiteral("pushButton_3"));
        deselectButton->setStyleSheet("QPushButton:hover {background:QLinearGradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFF, stop:1 #6495ED);border:1px solid #838B8B;border-radius:5px} QPushButton:pressed {background:QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #6495ED, stop:1 #FFF);border:1px solid #696969;border-radius:5px}");
        deselectButton->setFocusPolicy(Qt::NoFocus);
        verticalLayout->addWidget(deselectButton);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        syntaxButton = new QPushButton(IPC_formClass);
        syntaxButton->setObjectName(QStringLiteral("syntaxButton"));
        syntaxButton->setEnabled(true);
        QSize buttonSize(59,31);
		syntaxButton->setFixedSize(buttonSize);
		syntaxButton->setToolTip("Выполнить синтаксический разбор сегментов патентной формулы");
		syntaxButton->setStyleSheet("QPushButton {border-image: url(:/rec/icons/syntax_icon.png)} QPushButton:hover {background:QLinearGradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFF, stop:1 #6495ED);border:1px solid #838B8B;border-radius:5px} QPushButton:pressed {background:QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #6495ED, stop:1 #FFF);border:1px solid #696969;border-radius:5px}");
		syntaxButton->setFocusPolicy(Qt::NoFocus);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(syntaxButton->sizePolicy().hasHeightForWidth());
        syntaxButton->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(syntaxButton);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout_3, 1, 0, 1, 1);


        retranslateUi(IPC_formClass);

        QMetaObject::connectSlotsByName(IPC_formClass);
    } // setupUi

    void retranslateUi(QWidget *IPC_formClass)
    {
        IPC_formClass->setWindowTitle(QApplication::translate("IPC_formClass", "\320\230\320\275\320\264\320\265\320\272\321\201\321\213 \320\234\320\237\320\232", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("IPC_formClass", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("IPC_formClass", "\320\234\320\237\320\232 \320\270\320\275\320\264\320\265\320\272\321\201", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("IPC_formClass", "\320\234\320\237\320\232 \321\200\320\260\321\201\321\210\320\270\321\204\321\200\320\276\320\262\320\272\320\260", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("IPC_formClass", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\277\320\260\321\202\320\265\320\275\321\202\320\276\320\262", 0));
        selectAllButton->setText(QApplication::translate("IPC_formClass", "\320\222\321\213\320\264\320\265\320\273\320\270\321\202\321\214 \320\262\321\201\320\265", 0));
        deselectButton->setText(QApplication::translate("IPC_formClass", "\320\241\320\275\321\217\321\202\321\214 \320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\270\320\265", 0));
        //syntaxButton->setText(QApplication::translate("IPC_formClass", "syntax!", 0));
    } // retranslateUi

};

namespace Ui {
    class IPC_formClass: public Ui_IPC_formClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPC_FORM_H
