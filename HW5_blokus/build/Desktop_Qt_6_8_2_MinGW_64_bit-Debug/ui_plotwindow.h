/********************************************************************************
** Form generated from reading UI file 'plotwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTWINDOW_H
#define UI_PLOTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlotWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *boardGraphicsView;
    QGraphicsView *piecesGraphicsView;
    QLabel *titleLabel;
    QLabel *piecesLabel;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *playerStatshorizontalLayout;
    QVBoxLayout *p1verticalLayout;
    QLabel *p1label;
    QLabel *p1nameLabel;
    QLabel *placedLabel;
    QLabel *remainingLabel;
    QVBoxLayout *p2verticalLayout;
    QLabel *p2label;
    QLabel *p2nameLabel;
    QLabel *placedLabel_2;
    QLabel *remainingLabel_2;
    QVBoxLayout *p3verticalLayout;
    QLabel *p3label;
    QLabel *p3nameLabel;
    QLabel *placedLabel_3;
    QLabel *remainingLabel_3;
    QVBoxLayout *p4verticalLayout;
    QLabel *p4label;
    QLabel *p4nameLabel;
    QLabel *placedLabel_4;
    QLabel *remainingLabel_4;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *AbilityverticalLayout;
    QLabel *label;
    QPushButton *bombPushButton;
    QPushButton *mirrorPushButton;
    QPushButton *WildPushButton;
    QLabel *instructLabel;
    QLabel *instructLabel_2;
    QLabel *instructLabel_3;
    QLabel *instructLabel_4;

    void setupUi(QMainWindow *PlotWindow)
    {
        if (PlotWindow->objectName().isEmpty())
            PlotWindow->setObjectName("PlotWindow");
        PlotWindow->resize(1280, 720);
        PlotWindow->setAutoFillBackground(true);
        PlotWindow->setStyleSheet(QString::fromUtf8("QWidget#centralwidget {\n"
"    background-color: rgb(20, 0,20);\n"
"}\n"
""));
        centralwidget = new QWidget(PlotWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setAutoFillBackground(false);
        boardGraphicsView = new QGraphicsView(centralwidget);
        boardGraphicsView->setObjectName("boardGraphicsView");
        boardGraphicsView->setGeometry(QRect(10, 10, 700, 700));
        piecesGraphicsView = new QGraphicsView(centralwidget);
        piecesGraphicsView->setObjectName("piecesGraphicsView");
        piecesGraphicsView->setGeometry(QRect(730, 50, 531, 351));
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setGeometry(QRect(730, 10, 531, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Tahoma")});
        font.setPointSize(16);
        font.setItalic(false);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        piecesLabel = new QLabel(centralwidget);
        piecesLabel->setObjectName("piecesLabel");
        piecesLabel->setGeometry(QRect(950, 60, 91, 16));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(730, 410, 531, 86));
        playerStatshorizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        playerStatshorizontalLayout->setObjectName("playerStatshorizontalLayout");
        playerStatshorizontalLayout->setContentsMargins(0, 0, 0, 0);
        p1verticalLayout = new QVBoxLayout();
        p1verticalLayout->setObjectName("p1verticalLayout");
        p1label = new QLabel(horizontalLayoutWidget);
        p1label->setObjectName("p1label");
        p1label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        p1verticalLayout->addWidget(p1label);

        p1nameLabel = new QLabel(horizontalLayoutWidget);
        p1nameLabel->setObjectName("p1nameLabel");
        p1nameLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        p1verticalLayout->addWidget(p1nameLabel);

        placedLabel = new QLabel(horizontalLayoutWidget);
        placedLabel->setObjectName("placedLabel");

        p1verticalLayout->addWidget(placedLabel);

        remainingLabel = new QLabel(horizontalLayoutWidget);
        remainingLabel->setObjectName("remainingLabel");

        p1verticalLayout->addWidget(remainingLabel);


        playerStatshorizontalLayout->addLayout(p1verticalLayout);

        p2verticalLayout = new QVBoxLayout();
        p2verticalLayout->setObjectName("p2verticalLayout");
        p2label = new QLabel(horizontalLayoutWidget);
        p2label->setObjectName("p2label");
        p2label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        p2verticalLayout->addWidget(p2label);

        p2nameLabel = new QLabel(horizontalLayoutWidget);
        p2nameLabel->setObjectName("p2nameLabel");
        p2nameLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        p2verticalLayout->addWidget(p2nameLabel);

        placedLabel_2 = new QLabel(horizontalLayoutWidget);
        placedLabel_2->setObjectName("placedLabel_2");

        p2verticalLayout->addWidget(placedLabel_2);

        remainingLabel_2 = new QLabel(horizontalLayoutWidget);
        remainingLabel_2->setObjectName("remainingLabel_2");

        p2verticalLayout->addWidget(remainingLabel_2);


        playerStatshorizontalLayout->addLayout(p2verticalLayout);

        p3verticalLayout = new QVBoxLayout();
        p3verticalLayout->setObjectName("p3verticalLayout");
        p3label = new QLabel(horizontalLayoutWidget);
        p3label->setObjectName("p3label");
        p3label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        p3verticalLayout->addWidget(p3label);

        p3nameLabel = new QLabel(horizontalLayoutWidget);
        p3nameLabel->setObjectName("p3nameLabel");
        p3nameLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        p3verticalLayout->addWidget(p3nameLabel);

        placedLabel_3 = new QLabel(horizontalLayoutWidget);
        placedLabel_3->setObjectName("placedLabel_3");

        p3verticalLayout->addWidget(placedLabel_3);

        remainingLabel_3 = new QLabel(horizontalLayoutWidget);
        remainingLabel_3->setObjectName("remainingLabel_3");

        p3verticalLayout->addWidget(remainingLabel_3);


        playerStatshorizontalLayout->addLayout(p3verticalLayout);

        p4verticalLayout = new QVBoxLayout();
        p4verticalLayout->setObjectName("p4verticalLayout");
        p4label = new QLabel(horizontalLayoutWidget);
        p4label->setObjectName("p4label");
        p4label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        p4verticalLayout->addWidget(p4label);

        p4nameLabel = new QLabel(horizontalLayoutWidget);
        p4nameLabel->setObjectName("p4nameLabel");
        p4nameLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        p4verticalLayout->addWidget(p4nameLabel);

        placedLabel_4 = new QLabel(horizontalLayoutWidget);
        placedLabel_4->setObjectName("placedLabel_4");

        p4verticalLayout->addWidget(placedLabel_4);

        remainingLabel_4 = new QLabel(horizontalLayoutWidget);
        remainingLabel_4->setObjectName("remainingLabel_4");

        p4verticalLayout->addWidget(remainingLabel_4);


        playerStatshorizontalLayout->addLayout(p4verticalLayout);

        verticalLayoutWidget_5 = new QWidget(centralwidget);
        verticalLayoutWidget_5->setObjectName("verticalLayoutWidget_5");
        verticalLayoutWidget_5->setGeometry(QRect(730, 510, 191, 113));
        AbilityverticalLayout = new QVBoxLayout(verticalLayoutWidget_5);
        AbilityverticalLayout->setObjectName("AbilityverticalLayout");
        AbilityverticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget_5);
        label->setObjectName("label");
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label->setFont(font1);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        AbilityverticalLayout->addWidget(label);

        bombPushButton = new QPushButton(verticalLayoutWidget_5);
        bombPushButton->setObjectName("bombPushButton");

        AbilityverticalLayout->addWidget(bombPushButton);

        mirrorPushButton = new QPushButton(verticalLayoutWidget_5);
        mirrorPushButton->setObjectName("mirrorPushButton");

        AbilityverticalLayout->addWidget(mirrorPushButton);

        WildPushButton = new QPushButton(verticalLayoutWidget_5);
        WildPushButton->setObjectName("WildPushButton");

        AbilityverticalLayout->addWidget(WildPushButton);

        instructLabel = new QLabel(centralwidget);
        instructLabel->setObjectName("instructLabel");
        instructLabel->setGeometry(QRect(990, 510, 211, 16));
        instructLabel_2 = new QLabel(centralwidget);
        instructLabel_2->setObjectName("instructLabel_2");
        instructLabel_2->setGeometry(QRect(990, 530, 251, 61));
        instructLabel_2->setWordWrap(true);
        instructLabel_3 = new QLabel(centralwidget);
        instructLabel_3->setObjectName("instructLabel_3");
        instructLabel_3->setGeometry(QRect(990, 590, 251, 51));
        instructLabel_3->setWordWrap(true);
        instructLabel_4 = new QLabel(centralwidget);
        instructLabel_4->setObjectName("instructLabel_4");
        instructLabel_4->setGeometry(QRect(990, 640, 251, 21));
        instructLabel_4->setWordWrap(true);
        PlotWindow->setCentralWidget(centralwidget);

        retranslateUi(PlotWindow);

        QMetaObject::connectSlotsByName(PlotWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PlotWindow)
    {
        PlotWindow->setWindowTitle(QCoreApplication::translate("PlotWindow", "PlotWindow", nullptr));
        titleLabel->setText(QCoreApplication::translate("PlotWindow", "BLOKUS REMASTERED", nullptr));
        piecesLabel->setText(QCoreApplication::translate("PlotWindow", "Available Pieces", nullptr));
        p1label->setText(QCoreApplication::translate("PlotWindow", "Player 1", nullptr));
        p1nameLabel->setText(QCoreApplication::translate("PlotWindow", "p1_name", nullptr));
        placedLabel->setText(QCoreApplication::translate("PlotWindow", "Placed:", nullptr));
        remainingLabel->setText(QCoreApplication::translate("PlotWindow", "Remaining:", nullptr));
        p2label->setText(QCoreApplication::translate("PlotWindow", "Player 2", nullptr));
        p2nameLabel->setText(QCoreApplication::translate("PlotWindow", "p2_name", nullptr));
        placedLabel_2->setText(QCoreApplication::translate("PlotWindow", "Placed:", nullptr));
        remainingLabel_2->setText(QCoreApplication::translate("PlotWindow", "Remaining:", nullptr));
        p3label->setText(QCoreApplication::translate("PlotWindow", "Player 3", nullptr));
        p3nameLabel->setText(QCoreApplication::translate("PlotWindow", "p3_name", nullptr));
        placedLabel_3->setText(QCoreApplication::translate("PlotWindow", "Placed:", nullptr));
        remainingLabel_3->setText(QCoreApplication::translate("PlotWindow", "Remaining:", nullptr));
        p4label->setText(QCoreApplication::translate("PlotWindow", "Player 4", nullptr));
        p4nameLabel->setText(QCoreApplication::translate("PlotWindow", "p4_name", nullptr));
        placedLabel_4->setText(QCoreApplication::translate("PlotWindow", "Placed:", nullptr));
        remainingLabel_4->setText(QCoreApplication::translate("PlotWindow", "Remaining:", nullptr));
        label->setText(QCoreApplication::translate("PlotWindow", "Abilities", nullptr));
        bombPushButton->setText(QCoreApplication::translate("PlotWindow", "Bomb", nullptr));
        mirrorPushButton->setText(QCoreApplication::translate("PlotWindow", "Mirror Placed", nullptr));
        WildPushButton->setText(QCoreApplication::translate("PlotWindow", "Design Your Own", nullptr));
        instructLabel->setText(QCoreApplication::translate("PlotWindow", "How To Play:", nullptr));
        instructLabel_2->setText(QCoreApplication::translate("PlotWindow", "Rules: After the first block of yours is played, each of your next placements MUST connect via a diagonal to one of your already placed pieces.", nullptr));
        instructLabel_3->setText(QCoreApplication::translate("PlotWindow", "Game ends when no player can make a move and has expended all Placing Abilities (Mirror and DYO).", nullptr));
        instructLabel_4->setText(QCoreApplication::translate("PlotWindow", "Press 'r' to rotate, or use your scroll wheel.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlotWindow: public Ui_PlotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTWINDOW_H
