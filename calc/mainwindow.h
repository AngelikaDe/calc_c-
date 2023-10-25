#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//extern "C" {
//#include "../s21_smartcalc.h"
//}
#include "../s21_smartcalc.h"
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
    void on_x_clicked();

    void on_button_1_clicked();

    void on_button_3_clicked();

    void on_button_2_clicked();

    void on_button_5_clicked();

    void on_button_4_clicked();

    void on_button_6_clicked();

    void on_button_7_clicked();

    void on_button_8_clicked();

    void on_button_9_clicked();

    void on_button_acos_clicked();

    void on_button_ln_clicked();

    void on_button_cos_clicked();

    void on_button_tan_clicked();

    void on_button_sin_clicked();

    void on_button_asin_clicked();

    void on_button_sqrt_clicked();

    void on_button_atan_clicked();

    void on_button_log_clicked();

    void on_button_0_clicked();

    void on_button_dot_clicked();

    void on_button_left_bracket_clicked();

    void on_button_right_bracket_clicked();

    void on_button_mod_clicked();

    void on_button_div_clicked();

    void on_button_mult_clicked();

    void on_button_min_clicked();

    void on_button_plus_clicked();

    void on_button_equal_clicked();

    void on_button_del_clicked();

    void on_button_pow_clicked();

    void on_draw_graph_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
