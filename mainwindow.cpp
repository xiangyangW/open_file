#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    the_model_ = new QStandardItemModel(this);
    the_selec_ = new QItemSelectionModel(the_model_);
    connect(the_selec_, SIGNAL(QModelIndex), this, SLOT(selec_to_model()));

    ui->tableView->setModel(the_model_);
    ui->tableView->setSelectionModel(the_selec_);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbtn_op_file_clicked()
{
    QString filter = "TEXT File (*.txt)";
    QString file_path = QFileDialog::getOpenFileName(this, "choose a txt file", "c:// Users/user/Desktop/", filter);
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

        // transfer the str list into a standard item and put the item in the model
        iniModelFromStringList(file_rcontent);
    }

}

void MainWindow::iniModelFromStringList(QStringList& file_rcontent)
{
    int row_cnt = file_rcontent.count();
    the_model_->setRowCount(row_cnt);

    QStringList header_list;
    header_list << "name" << "sex" << "birthday";
    the_model_->setHorizontalHeaderLabels(header_list);

    // 處理表格數據
    for (int i = 0; i < row_cnt ; i++) {
        // split the string in each row and put into temp_list
        QString rtext = file_rcontent.at(i);
        QStringList temp_list = rtext.split(";");
        temp_list.removeLast();

        for (int j = 0; j < temp_list.count(); j++) {
            QStandardItem* item = new QStandardItem(temp_list.at(j));
            the_model_->setItem(i, j, item);
        }
    }

}

void MainWindow::on_pbtn_add_clicked()
{
    QList<QStandardItem*>   item_list;
    QStandardItem   *item;

    // 創建一行
    for (int i=0; i<COL_SIZE; i++ ) {
        item = new QStandardItem("edit here");
        item_list<<item;
    }

    // 新增行和index
    the_model_->insertRow(the_model_->rowCount(), item_list);
    QModelIndex index = the_model_->index(the_model_->rowCount()-1, 0);

    // 將選擇欄位換到新增的行
    the_selec_->clearSelection();
    the_selec_->setCurrentIndex(index, QItemSelectionModel::Select);
}

void MainWindow::on_pbtn_dlt_clicked()
{
    QModelIndex index = the_selec_->currentIndex();

    if(index.row()==the_model_->rowCount()-1)
        the_model_->removeRow(index.row());
    else
    {
        the_model_->removeRow(index.row());
        the_selec_->setCurrentIndex(index, QItemSelectionModel::Select);
    }
}

void MainWindow::selec_to_model()
{
// 狀態欄顯示index
}
