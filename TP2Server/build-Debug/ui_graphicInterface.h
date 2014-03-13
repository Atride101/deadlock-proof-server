/********************************************************************************
** Form generated from reading UI file 'graphicInterface.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICINTERFACE_H
#define UI_GRAPHICINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GraphicInterface
{
public:
    QGridLayout *gridLayout;
    QGroupBox *serverFrame;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *statusLabel;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *ipLabel;
    QLabel *portLabel;
    QVBoxLayout *verticalLayout_2;
    QComboBox *ipCombo;
    QLineEdit *portLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *startButton;
    QPushButton *quitButton;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *resourcesFrame;
    QGroupBox *logFrame;
    QGridLayout *gridLayout_3;
    QPlainTextEdit *logTextBox;

    void setupUi(QDialog *GraphicInterface)
    {
        if (GraphicInterface->objectName().isEmpty())
            GraphicInterface->setObjectName(QStringLiteral("GraphicInterface"));
        GraphicInterface->resize(270, 435);
        gridLayout = new QGridLayout(GraphicInterface);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        serverFrame = new QGroupBox(GraphicInterface);
        serverFrame->setObjectName(QStringLiteral("serverFrame"));
        gridLayout_2 = new QGridLayout(serverFrame);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        statusLabel = new QLabel(serverFrame);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(statusLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        ipLabel = new QLabel(serverFrame);
        ipLabel->setObjectName(QStringLiteral("ipLabel"));

        verticalLayout->addWidget(ipLabel);

        portLabel = new QLabel(serverFrame);
        portLabel->setObjectName(QStringLiteral("portLabel"));

        verticalLayout->addWidget(portLabel);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        ipCombo = new QComboBox(serverFrame);
        ipCombo->setObjectName(QStringLiteral("ipCombo"));
        ipCombo->setEditable(true);
        ipCombo->setInsertPolicy(QComboBox::NoInsert);

        verticalLayout_2->addWidget(ipCombo);

        portLineEdit = new QLineEdit(serverFrame);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));

        verticalLayout_2->addWidget(portLineEdit);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        startButton = new QPushButton(serverFrame);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setAutoDefault(false);

        horizontalLayout_3->addWidget(startButton);

        quitButton = new QPushButton(serverFrame);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setAutoDefault(false);

        horizontalLayout_3->addWidget(quitButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_3);


        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 1);


        gridLayout->addWidget(serverFrame, 0, 0, 1, 1);

        resourcesFrame = new QGroupBox(GraphicInterface);
        resourcesFrame->setObjectName(QStringLiteral("resourcesFrame"));

        gridLayout->addWidget(resourcesFrame, 1, 0, 1, 1);

        logFrame = new QGroupBox(GraphicInterface);
        logFrame->setObjectName(QStringLiteral("logFrame"));
        gridLayout_3 = new QGridLayout(logFrame);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        logTextBox = new QPlainTextEdit(logFrame);
        logTextBox->setObjectName(QStringLiteral("logTextBox"));
        logTextBox->setReadOnly(true);

        gridLayout_3->addWidget(logTextBox, 0, 0, 1, 1);


        gridLayout->addWidget(logFrame, 2, 0, 1, 1);


        retranslateUi(GraphicInterface);

        QMetaObject::connectSlotsByName(GraphicInterface);
    } // setupUi

    void retranslateUi(QDialog *GraphicInterface)
    {
        GraphicInterface->setWindowTitle(QApplication::translate("GraphicInterface", "Server - TP2 - IFT2245", 0));
        serverFrame->setTitle(QApplication::translate("GraphicInterface", "Server", 0));
        statusLabel->setText(QApplication::translate("GraphicInterface", "Server is not running", 0));
        ipLabel->setText(QApplication::translate("GraphicInterface", "IP Adress:", 0));
        portLabel->setText(QApplication::translate("GraphicInterface", "Port:", 0));
        startButton->setText(QApplication::translate("GraphicInterface", "Start Server", 0));
        quitButton->setText(QApplication::translate("GraphicInterface", "Quit", 0));
        resourcesFrame->setTitle(QApplication::translate("GraphicInterface", "Resources", 0));
        logFrame->setTitle(QApplication::translate("GraphicInterface", "Log", 0));
    } // retranslateUi

};

namespace Ui {
    class GraphicInterface: public Ui_GraphicInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICINTERFACE_H
