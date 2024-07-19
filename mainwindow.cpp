#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDebug>
#include <QString>
#include <cmath>

#define TABLE_FILE "./digits.txt"
#define COUNT_NUMBERS 1000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

// Табличный метод
    // необходимо указывать путь к вашему требуемому файлу
    QFile file(TABLE_FILE);
    if(!file.open(QFile::ReadOnly | QIODevice::Text))
    {
        qDebug() << file.errorString();
    } else {
        // Создаём поток для извлечения данных из файла
        QTextStream in(&file);
        // Считываем данные до конца файла
        int num_len {0};
        while (!in.atEnd() || num_len <=COUNT_NUMBERS)
        {
            num_len++;
            // ... построчно
            QString line = in.readLine();
            line.replace(QString("   "), QString(" "));
            line.replace(QString("  "), QString(" "));

            // Добавляем в модель по строке с элементами

            // учитываем, что строка разделяется точкой с запятой на колонки
            int k {0};
            for (QString item : line.split(" "))
            {
                k++;
                if(k==1) continue;
                mas.push_back(item.toInt());
            }
        }
        file.close();
    }
    for(int i = 0; i < COUNT_NUMBERS; i++)
    {
        mas_txt_decimal.push_back(mas[i] % 9); //one digit
        mas_txt_hundredths.push_back(mas[i] % 90 + 5); //two digit
        mas_txt_thousandths.push_back(mas[i] % 900 + 85); //three digit
    }
// --- Конец Табличный метод
// Конгруэтный метод
    int A = 36261;
    int C = 66037;
    int M = 312500;
    int X = 100;
    int nextNumber = (A * X + C) % M;

    for(int i = 0; i < COUNT_NUMBERS; i++)
    {
        nextNumber = std::fabs((A * nextNumber + C) % M); //Конгруэнтный метод
        mas_algo.push_back(nextNumber);
    }

    for(int i = 0; i < COUNT_NUMBERS; i++)
    {
        mas_algo_decimal.push_back(mas_algo[i] % 11); //one digit
        mas_algo_hundredths.push_back(mas_algo[i] % 90 + 5); //two digit
        mas_algo_thousandths.push_back(mas_algo[i] % 900 + 85); //three digit
    }
// --- конец Конгруэтный метод

// Рисуем верхнюю таблицу
    ui->tableView->setModel(NULL);
    Tables* table = new Tables(this);
    QStandardItemModel* model = table->table(mas_txt_decimal,
                                             mas_txt_hundredths,
                                             mas_txt_thousandths,
                                             mas_algo_decimal,
                                             mas_algo_hundredths,
                                             mas_algo_thousandths);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //ширина
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //запрет редактирования
    ui->tableView->setModel(model);
// --- Конец Рисуем верхнюю таблицу
// Рисуем нижнюю таблицу
    ui->tableView_2->setModel(NULL);
    QStandardItemModel* model_rand = table->table_rand_assessment(rand_assessment(mas_txt_decimal),
                                                                  rand_assessment(mas_txt_hundredths),
                                                                  rand_assessment(mas_txt_thousandths),
                                                                  rand_assessment(mas_algo_decimal),
                                                                  rand_assessment(mas_algo_hundredths),
                                                                  rand_assessment(mas_algo_thousandths));
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //ширина
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers); //запрет редактирования
    ui->tableView_2->setModel(model_rand);
// --- Конец Рисуем нижнюю таблицу

// рисуем десять окон ввода
    for (int i = 0; i < ui->verticalLayout->count(); i++)
    {
       ui->verticalLayout->itemAt(i)->widget()->deleteLater();
    }

    for(int i = 0; i < 10; i++)
    {
        matrix_txt.push_back(new QLineEdit());
    }

    for(int i = 0; i < 10; i++)
    {
        ui->verticalLayout->addWidget(matrix_txt[i],i);
    }
// --- конец рисуем десять окон ввода
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::rand_assessment(const QVector<int>& mas)
{
    QVector<int> divide_two;
    QVector<int> divide_three;
    QVector<int> divide_other;

    for(int i=0; i<mas.length(); i++)
    {
        if(mas[i]%2==0)
        {
            divide_two.push_back(mas[i]);
        }
        else if(mas[i]%3==0)
        {
            divide_three.push_back(mas[i]);
        }
        else
        {
            divide_other.push_back(mas[i]);
        }
    }


    long int sum_two {0};
    int count_two {0};
    long int sum_three {0};
    int count_three {0};
    long int sum_other {0};
    int count_other {0};

    int amount_two{0};
    int amount_three{0};
    int amount_other{0};

    for(int i=0; i<mas.length()-1; i++)
    {
        if(mas[i]%2==0)
        {
            amount_two++;
        }
        else if(mas[i]%3==0)
        {
            amount_three++;
        }
        else
        {
            amount_other++;
        }
    }



    for(int i=0; i<divide_two.length(); i++)
    {
       sum_two += divide_two[i];
       count_two++;
    }
//    if(count_two == 0) return -1;
    double diff_two{0};
    if(count_two > 0) diff_two = (double)sum_two/count_two;



    for(int i=0; i<divide_three.length(); i++)
    {
       sum_three += divide_three[i];
       count_three++;
    }
//    if(count_three == 0) return -1;
    double diff_three{0};
    if(count_three > 0) diff_three = (double)sum_three/count_three;



    for(int i=0; i<divide_other.length(); i++)
    {
       sum_other += divide_other[i];
       count_other++;
    }
//    if(count_other == 0) return -1;
    double diff_other{0};
    if(count_other > 0) diff_other = (double)sum_other/count_other;

    double result{0};

//    if(diff_two == 0.0 && diff_three == 0.0 && diff_other == 0.0) return -1;

//    result = 1-(1/(diff_two+diff_three+diff_other+amount_other+amount_three+amount_two));
//    result = 1-(1/(diff_two+diff_three+diff_other+amount_other));

    //result = sum_other;

    if(diff_two == 0.0 && diff_three == 0.0) result = 1-(1/diff_other);
    else if(diff_two == 0.0 && diff_other == 0.0) result = 1-(1/diff_three);
    else if(diff_three == 0.0 && diff_other == 0.0) result = 1-(1/diff_two);
    else if(diff_two == 0.0) result = 1-(1/(diff_other+diff_three + amount_other*0.8+amount_three*0.8));
    else if(diff_other == 0.0) result = 1-(1/(diff_three+diff_two + amount_three*0.8+amount_two*0.8));
    else if(diff_three == 0.0) result = 1-(1/(diff_two+diff_other + amount_two*0.8+amount_other*0.8));
    else result = 1-(1/(diff_two+diff_three+diff_other + amount_other*0.8+amount_three*0.8+amount_two*0.8));
//if (diff_two != 0.0 && diff_three != 0.0 && diff_other != 0.0) result = 1-(1/(diff_two+diff_three+diff_other+amount_other+amount_three+amount_two));

//    qDebug() <<diff_odd << " " << diff_even << " " << result << " " << sum_even << " " <<count_even;

    return result;
}

void MainWindow::on_pushButton_clicked()
{
    QString a;
    int data;
    manual.clear();
    for(int i = 0; i < matrix_txt.size(); i++)
    {
        a = matrix_txt[i]->text();
        data = a.toInt();
        manual.push_back(data);
    }

    ui->tableView_3->setModel(NULL);
    QStandardItemModel* model = new QStandardItemModel();
    model->setRowCount(1);
    model->setColumnCount(1);

    // установка заголовков таблицы
//    model->setHeaderData(0, Qt::Horizontal, "algorithm");

    for(int i = 0; i < 1; i++)
    {
        model->setItem(i, 0, new QStandardItem(QString::number(rand_assessment(manual))));
    }

    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //ширина
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers); //запрет редактирования

    ui->tableView_3->setModel(model);
}


void MainWindow::on_pushButton_2_clicked()
{
    for(int i = 0; i < matrix_txt.size(); i++)
    {
        matrix_txt[i]->clear();
    }
    ui->tableView_3->setModel(NULL);
}

