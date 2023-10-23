#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->x_value->setPlaceholderText("X Value");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_x_clicked()
{
    ui->textEdit->insertPlainText("x");
}


void MainWindow::on_button_1_clicked()
{
    ui->textEdit->insertPlainText("1");
}


void MainWindow::on_button_3_clicked()
{
    ui->textEdit->insertPlainText("3");
}


void MainWindow::on_button_2_clicked()
{
    ui->textEdit->insertPlainText("2");
}


void MainWindow::on_button_5_clicked()
{
    ui->textEdit->insertPlainText("5");
}


void MainWindow::on_button_4_clicked()
{
    ui->textEdit->insertPlainText("4");
}


void MainWindow::on_button_6_clicked()
{
    ui->textEdit->insertPlainText("6");
}


void MainWindow::on_button_7_clicked()
{
    ui->textEdit->insertPlainText("7");
}


void MainWindow::on_button_8_clicked()
{
    ui->textEdit->insertPlainText("8");
}


void MainWindow::on_button_9_clicked()
{
    ui->textEdit->insertPlainText("9");
}


void MainWindow::on_button_acos_clicked()
{
    ui->textEdit->insertPlainText("acos(");
}


void MainWindow::on_button_ln_clicked()
{
    ui->textEdit->insertPlainText("ln(");
}


void MainWindow::on_button_cos_clicked()
{
    ui->textEdit->insertPlainText("cos(");
}


void MainWindow::on_button_tan_clicked()
{
    ui->textEdit->insertPlainText("tan(");
}


void MainWindow::on_button_sin_clicked()
{
    ui->textEdit->insertPlainText("sin(");
}


void MainWindow::on_button_asin_clicked()
{
    ui->textEdit->insertPlainText("asin(");
}


void MainWindow::on_button_sqrt_clicked()
{
    ui->textEdit->insertPlainText("sqrt(");
}


void MainWindow::on_button_atan_clicked()
{
    ui->textEdit->insertPlainText("atan(");
}


void MainWindow::on_button_log_clicked()
{
    ui->textEdit->insertPlainText("log(");
}


void MainWindow::on_button_0_clicked()
{
    ui->textEdit->insertPlainText("0");
}


void MainWindow::on_button_dot_clicked()
{
    ui->textEdit->insertPlainText(".");
}


void MainWindow::on_button_left_bracket_clicked()
{
    ui->textEdit->insertPlainText("(");
}


void MainWindow::on_button_right_bracket_clicked()
{
    ui->textEdit->insertPlainText(")");
}


void MainWindow::on_button_mod_clicked()
{
    ui->textEdit->insertPlainText("mod");
}


void MainWindow::on_button_div_clicked()
{
    ui->textEdit->insertPlainText("/");
}


void MainWindow::on_button_mult_clicked()
{
    ui->textEdit->insertPlainText("*");
}


void MainWindow::on_button_min_clicked()
{
    ui->textEdit->insertPlainText("-");
}


void MainWindow::on_button_plus_clicked()
{
    ui->textEdit->insertPlainText("+");
}


void MainWindow::on_button_equal_clicked()
{
    ui->textEdit->insertPlainText("=");
    char *expression = (char*) ui->textEdit->toPlainText().toStdString().c_str();
    double answer = 0;
    char *x = "N";
    if (!ui->x_value->toPlainText().isEmpty()) {
        x = (char*)ui->x_value->toPlainText().toStdString().c_str();
    }
    int err = calculation(expression, &answer, x);
    if (err) {
        ui->textEdit->setText("ERROR");
    }
    else {
        ui->textEdit->setText(QString::number(answer));
    }
}


void MainWindow::on_button_del_clicked()
{
    ui->textEdit->setText("");
}


void MainWindow::on_button_pow_clicked()
{
    ui->textEdit->insertPlainText("^(");
}


void MainWindow::on_draw_graph_clicked()
{
    double a = -1; //Начало интервала, где рисуем график по оси Ox
    double b =  1; //Конец интервала, где рисуем график по оси Ox
    double h = 0.1; //Шаг, с которым будем пробегать по оси Ox
    int N = (b - a) / h + 2; //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N), y(N); //Массивы координат точек

    //Вычисляем наши данные
    int i=0;
    //Пробегаем по всем точкам
    ui->textEdit->insertPlainText("=");
    char *expression = (char*) ui->textEdit->toPlainText().toStdString().c_str();

    for (double X = a; i < N; X += h) { //X <= b
        x[i] = X;
        double answer = 0.0;
        std::string X_str = std::to_string(X);
        const char* X_char = X_str.c_str();
        int err = calculation(expression, &answer, X_char);
        if (err) {
            ui->textEdit->setText("ERROR");
            return;
        }
        y[i] = answer;
        i++;
    }
    ui->widget->clearGraphs();//Если нужно, но очищаем все графики

    //Добавляем один график в widget
    ui->widget->addGraph();

    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);

    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    //Установим область, которая будет показываться на графике
    ui->widget->xAxis->setRange(a, b);//Для оси Ox

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    double minY = y[0], maxY = y[0];
    for (int i = 1; i < N; i++) {
        if (y[i] < minY) minY = y[i];
        if (y[i] > maxY) maxY = y[i];
    }
    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

    //И перерисуем график на нашем widget
    ui->widget->replot();
}

