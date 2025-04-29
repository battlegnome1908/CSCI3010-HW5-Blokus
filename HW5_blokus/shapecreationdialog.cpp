#include "shapecreationdialog.h"
#include "ui_shapecreationdialog.h"

ShapeCreationDialog::ShapeCreationDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShapeCreationDialog)
{
    ui->setupUi(this);
}

ShapeCreationDialog::~ShapeCreationDialog()
{
    delete ui;
}
