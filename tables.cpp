#include "tables.h"

Tables::Tables(QObject *parent) : QObject(parent)
{

}

QStandardItemModel* Tables::table(const QVector<int>& mas_txt_decimal,
                                  const QVector<int>& mas_txt_hundredths,
                                  const QVector<int>& mas_txt_thousandths,
                                  const QVector<int>& mas_algo_decimal,
                                  const QVector<int>& mas_algo_hundredths,
                                  const QVector<int>& mas_algo_thousandths)
{

    QStandardItemModel* model = new QStandardItemModel();
    model->setRowCount(10);
    model->setColumnCount(6);

    // установка заголовков таблицы

        model->setHeaderData(0, Qt::Horizontal, "Файл");
        model->setHeaderData(1, Qt::Horizontal, "Файл");
        model->setHeaderData(2, Qt::Horizontal, "Файл");
        model->setHeaderData(3, Qt::Horizontal, "Формула");
        model->setHeaderData(4, Qt::Horizontal, "Формула");
        model->setHeaderData(5, Qt::Horizontal, "Формула");

    for(int i = 0; i < 10; i++)
    {
        model->setItem(i, 0, new QStandardItem(QString::number(mas_txt_decimal[i])));
        model->setItem(i, 1, new QStandardItem(QString::number(mas_txt_hundredths[i])));
        model->setItem(i, 2, new QStandardItem(QString::number(mas_txt_thousandths[i])));
        model->setItem(i, 3, new QStandardItem(QString::number(mas_algo_decimal[i])));
        model->setItem(i, 4, new QStandardItem(QString::number(mas_algo_hundredths[i])));
        model->setItem(i, 5, new QStandardItem(QString::number(mas_algo_thousandths[i])));
    }
    return model;
}

QStandardItemModel* Tables::table_rand_assessment(double one,
                                          double two,
                                          double three,
                                          double four,
                                          double five,
                                          double six)
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setRowCount(1);
    model->setColumnCount(6);

    // установка заголовков таблицы

//        model->setHeaderData(0, Qt::Horizontal, "Файл: 0-9");
//        model->setHeaderData(1, Qt::Horizontal, "Файл: 10-99");
//        model->setHeaderData(2, Qt::Horizontal, "Файл: 100-999");
//        model->setHeaderData(3, Qt::Horizontal, "Формула: 0-9");
//        model->setHeaderData(4, Qt::Horizontal, "Формула: 10-99");
//        model->setHeaderData(5, Qt::Horizontal, "Формула: 100-999");

    for(int i = 0; i < 1; i++)
    {
        model->setItem(i, 0, new QStandardItem(QString::number(one)));
        model->setItem(i, 1, new QStandardItem(QString::number(two)));
        model->setItem(i, 2, new QStandardItem(QString::number(three)));
        model->setItem(i, 3, new QStandardItem(QString::number(four)));
        model->setItem(i, 4, new QStandardItem(QString::number(five)));
        model->setItem(i, 5, new QStandardItem(QString::number(six)));
    }
    return model;
}
