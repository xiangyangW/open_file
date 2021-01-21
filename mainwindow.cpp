#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bt_op_file_clicked()
{
    QString filter = "TEXT File (*.txt)";
    QString file_path = QFileDialog::getOpenFileName(this,"choose a txt file","c://",filter);
    QFile file(file_path);

    //check this section
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"warning","error");
    }

    ui->le_path->setText(file_path);

    QTextStream in(&file);
    QString content = in.readAll();//chech diff function
    ui->plainTextEdit->setPlainText(content);

    file.close();
}
