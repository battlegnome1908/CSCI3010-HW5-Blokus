#ifndef SHAPECREATIONDIALOG_H
#define SHAPECREATIONDIALOG_H

#include <QDialog>
#include <QPoint>
#include <QVector>
#include <QPushButton>

namespace Ui {
class ShapeCreationDialog;
}

class ShapeCreationDialog : public QDialog
{
    Q_OBJECT
// alright so the goal is to eventually paint a new mini grid. i don't want to copy over all of plot window. could we create a
public:
    explicit ShapeCreationDialog(QWidget *parent = nullptr);
    ~ShapeCreationDialog();
    QVector<QPoint> GetSelectedBlocks() const;


private:
    Ui::ShapeCreationDialog *ui;


private slots:

};

#endif // SHAPECREATIONDIALOG_H
