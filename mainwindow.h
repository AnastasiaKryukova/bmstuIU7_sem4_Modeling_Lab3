#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "tables.h"
#include <QStandardItemModel>
#include "QStandardItem"
#include <QTableView>
#include <QLineEdit>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static double rand_assessment(const QVector<int>&);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    QVector<int> mas;
    QVector<int> mas_txt_decimal;
    QVector<int> mas_txt_hundredths;
    QVector<int> mas_txt_thousandths;

    QVector<int> mas_algo;
    QVector<int> mas_algo_decimal;
    QVector<int> mas_algo_hundredths;
    QVector<int> mas_algo_thousandths;

    QVector<QLineEdit*> matrix_txt;
    QVector<int> manual;
};
#endif // MAINWINDOW_H
