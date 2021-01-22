#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

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

void MainWindow::on_pbtn_open_file_clicked()
{
    QString filter = "TEXT File (*.txt)";
    QString file_path = QFileDialog::getOpenFileName(this, "choose a txt file", "c://Users/user/Desktop/", filter);
    ui->lineEdit_path->setText(file_path);

    if (file_path.isEmpty())
        return;

    // put the content in txt to a stringlist row by row
    QStringList file_rcontent;
    QFile file(file_path);
    if (file.open(QFile::ReadOnly | QFile::Text)) {

        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        while (!stream.atEnd()) {
            QString str = stream.readLine();
            file_rcontent.append(str);
        }
        file.close();

        the_model_ = new QStandardItemModel(this);

        //transfer the str list into a standard item and put the item in the model
        iniModelFromStringList(file_rcontent);
    }
    ui->tableView->setModel(the_model_);

//    //測試輸出file_rcontent內容
//    QStringListModel *strmodel = new QStringListModel();
//    strmodel->setStringList(file_rcontent);
//    ui->listView->setModel(strmodel);
}

void MainWindow::iniModelFromStringList(QStringList& file_rcontent)
{
    int row_cnt = file_rcontent.count();
    the_model_->setRowCount(row_cnt);

    QStringList header_list;
    header_list << "name" << "sex" << "birthday";
    the_model_->setHorizontalHeaderLabels(header_list);

    //處理表格數據
    QStandardItem *item;

//    for (int i=0; i<row_cnt; i++)
//    {
//        //每一行要處理的程序
//        //strlist中列出row裡面各項資料 在model中依序填入item
//        QString str = file_rcontent.at(i);
//        QStringList strlist = str.split(";");
//        strlist.removeLast();
//        for (j=0; j<ROW_SIZE; j++)
//        {
//            item = new QStandardItem(strlist.at(j));
//            the_model_->setItem(i,j,item);
//        }
//    }

    for (int i = 0; i < row_cnt ; i++) {

        //split the string in each row and put into temp_list
        QString rtext = file_rcontent.at(i);
        QStringList temp_list = rtext.split(";");
        temp_list.removeLast();

        for (int j = 0; j < temp_list.count(); j++) {

            item = new QStandardItem(temp_list.at(j));
            the_model_->setItem(i, j, item);
        }
    }
}
