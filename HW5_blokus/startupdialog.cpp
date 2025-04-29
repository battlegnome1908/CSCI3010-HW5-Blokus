#include "startupdialog.h"
#include "ui_startupdialog.h"
#include <QGraphicsDropShadowEffect>
#include <QColorDialog>
#include <QMessageBox>


startupDialog::startupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::startupDialog)
{
    ui->setupUi(this);
    QGraphicsDropShadowEffect* glow = new QGraphicsDropShadowEffect(this);
    glow->setBlurRadius(25);    // How soft the glow is
    glow->setColor(Qt::white);  // Color of the glow
    glow->setOffset(0);         // Centered glow

    ui->titleLabel->setGraphicsEffect(glow);

    connect(ui->playerCountSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &startupDialog::UpdatePlayerFields);

    // Color choice
    connect(ui->p1ColorButton, &QPushButton::clicked, this, &startupDialog::OnP1ColorClicked);
    connect(ui->p2ColorButton, &QPushButton::clicked, this, &startupDialog::OnP2ColorClicked);
    connect(ui->p3ColorButton, &QPushButton::clicked, this, &startupDialog::OnP3ColorClicked);
    connect(ui->p4ColorButton, &QPushButton::clicked, this, &startupDialog::OnP4ColorClicked);

    // READDDDDDY
    connect(ui->DonePushButton, &QPushButton::clicked, this, &startupDialog::DonePushButtonClicked);


}

startupDialog::~startupDialog()
{
    delete ui;
}

void startupDialog::UpdatePlayerFields(int count) {
    // Player 3
    bool showP3 = count >= 3;
    ui->Player1Label_3->setVisible(showP3);
    ui->playerNameLabel_3->setVisible(showP3);
    ui->P1plainTextEdit_3->setVisible(showP3);
    ui->colorlabel_3->setVisible(showP3);
    ui->p3ColorButton->setVisible(showP3);

    // Player 4
    bool showP4 = count >= 4;
    ui->Player1Label_4->setVisible(showP4);
    ui->playerNameLabel_4->setVisible(showP4);
    ui->P1plainTextEdit_4->setVisible(showP4);
    ui->colorlabel_4->setVisible(showP4);
    ui->p4ColorButton->setVisible(showP4);
}

void startupDialog::OnP1ColorClicked() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color for Player 1");
    if (color.isValid()) {
        // Check brightness
        int brightness = (color.red() * 299 + color.green() * 587 + color.blue() * 114) / 1000;
        if (brightness < 75) { // too dark
            QMessageBox::warning(this, "Warning", "This color may be too dark to see clearly.");
        }

        ui->p1ColorButton->setStyleSheet("background-color: " + color.name());
        p1_color_ = color;
    }
}

void startupDialog::OnP2ColorClicked() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color for Player 2");
    if (color.isValid()) {
        // Check brightness
        int brightness = (color.red() * 299 + color.green() * 587 + color.blue() * 114) / 1000;
        if (brightness < 75) { // too dark
            QMessageBox::warning(this, "Warning", "This color may be too dark to see clearly.");
        }

        ui->p2ColorButton->setStyleSheet("background-color: " + color.name());
        p2_color_ = color;
    }
}
void startupDialog::OnP3ColorClicked() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color for Player 3");
    if (color.isValid()) {
        // Check brightness
        int brightness = (color.red() * 299 + color.green() * 587 + color.blue() * 114) / 1000;
        if (brightness < 75) { // too dark
            QMessageBox::warning(this, "Warning", "This color may be too dark to see clearly.");
        }

        ui->p3ColorButton->setStyleSheet("background-color: " + color.name());
        p3_color_ = color;
    }
}
void startupDialog::OnP4ColorClicked() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color for Player 4");
    if (color.isValid()) {
        // Check brightness
        int brightness = (color.red() * 299 + color.green() * 587 + color.blue() * 114) / 1000;
        if (brightness < 75) { // too dark
            QMessageBox::warning(this, "Warning", "This color may be too dark to see clearly.");
        }

        ui->p4ColorButton->setStyleSheet("background-color: " + color.name());
        p4_color_ = color;
    }
}

void startupDialog::DonePushButtonClicked() {
    playerCount = ui->playerCountSpinBox->value();

    playerNames.clear();
    playerColors.clear();

    // Gather names
    QString name1 = ui->P1plainTextEdit_1->toPlainText().trimmed();
    QString name2 = ui->P1plainTextEdit_2->toPlainText().trimmed();
    QString name3 = ui->P1plainTextEdit_3->toPlainText().trimmed();
    QString name4 = ui->P1plainTextEdit_4->toPlainText().trimmed();

    // Check for empty names
    if (name1.isEmpty() || name2.isEmpty() ||
        (playerCount >= 3 && name3.isEmpty()) ||
        (playerCount >= 4 && name4.isEmpty())) {

        QMessageBox::warning(this, "Invalid Input", "Please fill in a name for each player.");
        return;
    }

    // Default Colors: Red, Green, Blue, Yellow
    QVector<QColor> defaultColors = { Qt::red, Qt::green, Qt::blue, Qt::yellow };

    // Save names
    playerNames.append(name1);
    playerNames.append(name2);
    if (playerCount >= 3) playerNames.append(name3);
    if (playerCount >= 4) playerNames.append(name4);

    // Save colors, assigning defaults if needed
    playerColors.append(p1_color_.isValid() ? p1_color_ : defaultColors[0]);
    playerColors.append(p2_color_.isValid() ? p2_color_ : defaultColors[1]);
    if (playerCount >= 3) playerColors.append(p3_color_.isValid() ? p3_color_ : defaultColors[2]);
    if (playerCount >= 4) playerColors.append(p4_color_.isValid() ? p4_color_ : defaultColors[3]);

    accept();
}
