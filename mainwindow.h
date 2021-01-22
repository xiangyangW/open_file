#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>//check if it's used

#define ROW_SIZE 3

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bt_op_file_clicked();

private:
    void iniModelFromStringList (QStringList&);

private:
    Ui::MainWindow *ui;

    QStandardItemModel *the_model_;
    QItemSelectionModel *the_selec_;//check if it's used
};
#endif // MAINWINDOW_H
