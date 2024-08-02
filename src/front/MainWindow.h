#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#ifdef __cplusplus

extern "C" {
#endif

#include "../back/s21_stack.h"
#include "../back/s21_calculate.h"
#include "../back/s21_credit_calc.h"
#include "../back/s21_debit_calc.h"

#ifdef __cplusplus
}
#endif



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    t_credit *data;
    t_debit *data_deb;

private slots:
    void digits_numbers();
    void on_pushButton_dot_clicked();
    void operations();
    void functions();
    void on_pushButton_AC_clicked();
    void on_pushButton_equal_clicked();
    void on_pushButton_unar_clicked();
    void on_pushButton_graph_clicked();
    void on_pushButton_graph_clear_clicked();
    void on_pushButton_calculate_loan_clicked();
    void on_pushButton_cred_clear_clicked();
    void on_pushButton_calculate_deb_clicked();
    void on_pushButton_deb_clear_clicked();
};
#endif // MAINWINDOW_H
