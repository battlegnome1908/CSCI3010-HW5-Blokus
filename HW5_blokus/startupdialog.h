#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include <QDialog>

namespace Ui {
class startupDialog;
}

class startupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit startupDialog(QWidget *parent = nullptr);
    ~startupDialog();

    void UpdatePlayerFields(int count);

    void OnP1ColorClicked();
    void OnP2ColorClicked();
    void OnP3ColorClicked();
    void OnP4ColorClicked();

    void DonePushButtonClicked();

    // Data to pass to PlotWindow via main.cpp
    QVector<QString> playerNames;
    QVector<QColor> playerColors;
    int playerCount;

private:
    Ui::startupDialog *ui;

    QColor p1_color_;
    QColor p2_color_;
    QColor p3_color_;
    QColor p4_color_;



};

#endif // STARTUPDIALOG_H
