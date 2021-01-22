#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#define COL_SIZE 3

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
    void on_pbtn_op_file_clicked();

    void on_pbtn_add_clicked();

    void on_pbtn_dlt_clicked();

    void selec_to_model();

private:
    void iniModelFromStringList (QStringList&);

private:
    Ui::MainWindow *ui;

    QStandardItemModel *the_model_;
    QItemSelectionModel *the_selec_;
};
#endif // MAINWINDOW_H
