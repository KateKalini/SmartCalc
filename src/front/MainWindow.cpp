#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../back/s21_stack.h"
#include "../back/s21_calculate.h"
#include "../back/s21_credit_calc.h"
#include "../back/s21_debit_calc.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_open_br, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_close_br, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();
    QString new_label;

    qDebug()<<button->property("btn_type").toString();

    if ((ui->result_show->text() == "0"  &&  button->text() != '.') ||  ui->result_show->text() == "Error")
    {
        new_label = button->text();
    }
    else
    {
        new_label = ui->result_show->text() + button->text();
    }
    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked()
{
    //if (!(ui->result_show->text().contains('.')))
        ui->result_show->setText(ui->result_show->text() + ".");
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton *)sender();
    double all_numbers;
    QString new_label;

    if(button->text() == "+") {
        all_numbers = (ui->result_show->text().toDouble());
        new_label = QString::number(all_numbers, 'g', 100);

        ui->result_show->setText(ui->result_show->text() + " + ");
    }
    else if(button->text() == "-") {
        all_numbers = (ui->result_show->text().toDouble());
        new_label = QString::number(all_numbers, 'g', 100);

        ui->result_show->setText(ui->result_show->text() + " - ");
    }
    else if(button->text() == "*") {
        all_numbers = (ui->result_show->text().toDouble());
        new_label = QString::number(all_numbers, 'g', 100);

        ui->result_show->setText(ui->result_show->text() + " * ");
    }
    else if(button->text() == "/") {
        all_numbers = (ui->result_show->text().toDouble());
        new_label = QString::number(all_numbers, 'g', 100);

        ui->result_show->setText(ui->result_show->text() + " / ");
    }
    else if(button->text() == "^") {
        all_numbers = (ui->result_show->text().toDouble());
        new_label = QString::number(all_numbers, 'g', 100);

        ui->result_show->setText(ui->result_show->text() + " ^ ");
    }
    else if(button->text() == "mod") {
        all_numbers = (ui->result_show->text().toDouble());
        new_label = QString::number(all_numbers, 'g', 100);

        ui->result_show->setText(ui->result_show->text() + " mod ");
    }
    else if(button->text() == "(") {
        all_numbers = (ui->result_show->text().toDouble());
        new_label = QString::number(all_numbers, 'g', 100);

        ui->result_show->setText(ui->result_show->text() + " ( ");
    }
    else if(button->text() == ")") {
        if (!(ui->result_show->text().contains('('))) {
            ;
        }
        else {
            all_numbers = (ui->result_show->text().toDouble());
            new_label = QString::number(all_numbers, 'g', 100);

            ui->result_show->setText(ui->result_show->text() + " ) ");
        }
    }
}

void MainWindow::functions()
{
    QPushButton *button = (QPushButton *)sender();
    QString new_label;

    if (ui->result_show->text() == "0")
    {
        new_label = button->text() + " ( ";
    }
    else
    {
        new_label = ui->result_show->text() + button->text() + " ( ";
    }
    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_AC_clicked()
{
    ui->result_show->setText("0");
}


void MainWindow::on_pushButton_equal_clicked()
{
    //QPushButton *button = (QPushButton *)sender();
    QString new_label;
    new_label = ui->result_show->text() + " =";
    ui->result_show->setText(new_label);

    QString text = ui->result_show->text().toStdString().c_str();
    double result;
    double value_x = ui->doubleSpinBox_x->value();
    result = calculate(text.toStdString().data(), value_x);

    //qDebug()<<"stroka iz ravno ="<<result;
    new_label = QString::number(result, 'f', 7);
    ui->result_show->setText(new_label);
}


void MainWindow::on_pushButton_unar_clicked()
{
    //QPushButton *button = (QPushButton *)sender();
    //QString new_label;

    QString text = ui->result_show->text().toStdString().c_str();
    int index = text.lastIndexOf(' ');
    if (index == -1) {
        if (text.at(0)=='-') {
            text.replace(0,1,"");
        }
        else {
            text = "-" + text;
        }
    } else {
        if (text.at(index+1) == '-') {
            text.replace(index+1,1,"");
        }
        else {
            text.replace(index,1," -");
        }
    }

    ui->result_show->setText(text);
}


void MainWindow::on_pushButton_graph_clicked()
{
    double x_min = ui->doubleSpinBox_x_min->value();
    double x_max = ui->doubleSpinBox_x_max->value();
    double y_min = ui->doubleSpinBox_y_min->value();
    double y_max = ui->doubleSpinBox_y_max->value();

    double h = 0.1;
    QVector<double> x, y;

    QString text = ui->result_show->text().toStdString().c_str();
    text = text + " =";
    ui->widget->xAxis->setRange(x_min, x_max);
    ui->widget->yAxis->setRange(y_min, y_max);

    for (double X = x_min; X <= x_max; X += h) {
       x.push_back(X);

       double result = calculate(text.toStdString().data(), X);
       //qDebug()<<"eto X"<<X;
       //qDebug()<<"eto result"<<result;
       y.push_back(result);
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    ui->widget->replot();
//    x.clear();
//    y.clear();
}


void MainWindow::on_pushButton_graph_clear_clicked()
{
    for (int g = 0; g < ui->widget->graphCount(); g++) {
        ui->widget->graph(g)->data().data()->clear();
    }
    ui->widget->clearGraphs();
    ui->widget->replot();
}


void MainWindow::on_pushButton_calculate_loan_clicked()
{
    data->sum = ui->doubleSpinBox_sum->value();
    data->months = ui->doubleSpinBox_months->value();
    data->rate = ui->doubleSpinBox_rate->value();

    if (ui->radioButton_ann->isChecked()) {
        ann_credit_calc(data);
        ui->label_month_payment->setText(QString::number(data->month_payment, 'f', 2));
        ui->label_all_payment->setText(QString::number(data->ann_all_payment, 'f', 2));
        ui->label_overpayment->setText(QString::number(data->overpayment, 'f', 2));
    }
    else if (ui->radioButton_diff->isChecked()) {
        diff_credit_calc(data);
        ui->label_month_payment->setText(QString::number(data->max_month_payment, 'f', 2) + " ... " + QString::number(data->min_month_payment, 'f', 2));
        ui->label_all_payment->setText(QString::number(data->ann_all_payment, 'f', 2));
        ui->label_overpayment->setText(QString::number(data->overpayment, 'f', 2));
    }
    else{
        ;
    }


}


void MainWindow::on_pushButton_cred_clear_clicked()
{
    ui->doubleSpinBox_months->clear();
    ui->doubleSpinBox_rate->clear();
    ui->doubleSpinBox_sum->clear();
    ui->label_all_payment->clear();
    ui->label_month_payment->clear();
    ui->label_overpayment->clear();
}


void MainWindow::on_pushButton_calculate_deb_clicked()
{
    data_deb->sum = ui->doubleSpinBox_sum_debit->value();
    data_deb->months = ui ->doubleSpinBox_months_debit ->value();
    data_deb->rate = ui->doubleSpinBox_rate_debit->value();
    data_deb->tax = ui->doubleSpinBox_tax_debit->value();
    data_deb->extra_money = ui->doubleSpinBox_extra_money->value();
    if (ui->radioButton_1->isChecked())  data_deb->gap_capitalization = 1;
    if (ui->radioButton_3->isChecked())  data_deb->gap_capitalization = 3;
    if (ui->radioButton_12->isChecked())  data_deb->gap_capitalization = 3;

    debit_calc(data_deb);

    ui->label_deposit_money->setText(QString::number(data_deb->deposit_money, 'f', 2));
    ui->label_tax->setText(QString::number(data_deb->tax_payment, 'f', 2));
    ui->label_payment->setText(QString::number(data_deb->payment, 'f', 2));

}


void MainWindow::on_pushButton_deb_clear_clicked()
{
    ui->label_deposit_money->clear();
    ui->label_tax->clear();
    ui->label_payment->clear();
    ui->doubleSpinBox_extra_money->clear();
    ui->doubleSpinBox_months_debit->clear();
    ui->doubleSpinBox_rate_debit->clear();
    ui->doubleSpinBox_sum_debit->clear();
    ui->doubleSpinBox_tax_debit->clear();
    ui->doubleSpinBox_extra_money->clear();

}

