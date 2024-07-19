#ifndef TABLES_H
#define TABLES_H

#include <QObject>

#include <QStandardItemModel>
#include "QStandardItem"
#include <QTableView>

class Tables : public QObject
{
    Q_OBJECT
public:
    explicit Tables(QObject *parent = nullptr);
    QStandardItemModel* table(const QVector<int>&,
               const QVector<int>&,
               const QVector<int>&,
               const QVector<int>&,
               const QVector<int>&,
               const QVector<int>&);
    QStandardItemModel* table_rand_assessment(double,
                                              double,
                                              double,
                                              double,
                                              double,
                                              double);
signals:

};

#endif // TABLES_H
