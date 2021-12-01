#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->button_0, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_1, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_2, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_3, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_4, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_5, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_6, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_7, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_8, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_9, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_dot, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_power, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_multiply, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_divide, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_add, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_minus, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_openingBrace, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));
    connect(ui->button_closingBrace, SIGNAL(pressed()), this, SLOT(inputButton_pressed()));

    connect(ui->button_exe, SIGNAL(pressed()), this, SLOT(exeButton_pressed()));

    connect(ui->button_clear, SIGNAL(pressed()), this, SLOT(clearButton_pressed()));

    connect(ui->button_del, SIGNAL(pressed()), this, SLOT(delButton_pressed()));

    connect(ui->button_up, SIGNAL(pressed()), this, SLOT(navigateHistoryUp()));
    connect(ui->button_down, SIGNAL(pressed()), this, SLOT(navigateHistoryDown()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inputButton_pressed()
{
    QPushButton * button = (QPushButton*)sender();

    QString inputStr = ui->label->text() + button->text();

    ui->label->setText(inputStr);
}

void MainWindow::exeButton_pressed()
{
    Calculator cal;
    QString str = ui->label->text();
    string inputStr = ui->label->text().toStdString();
    if(inputStr.length() == 0) return;

    history[nextHistory] = str;
    newestHistory = nextHistory;
    if(historySize < 10) historySize++;
    if(nextHistory == 9) nextHistory = 0;
    else nextHistory++;
    if(historySize < 10) oldestHistory = 0;
    else if(nextHistory == 9) oldestHistory = 0;
    else oldestHistory = nextHistory + 1;
    upHistory = newestHistory;
    downHistory = oldestHistory;

    try{
        string res = cal.calculate(inputStr);
        QString str = QString::number(std::stod(res), 'g', 15);
        ui->label_Ans->setText(str);
    }
    catch(invalid_argument &e){
        QString err = e.what();
        QMessageBox::warning(this, "Warning", err);
    }
}

void MainWindow::delButton_pressed()
{
    QString str = ui->label->text();
    str = str.left(str.length()-1);
    ui->label->setText(str);
}

void MainWindow::clearButton_pressed()
{
    upHistory = newestHistory;
    downHistory = oldestHistory;
    ui->label->setText("");
    ui->label_Ans->setText("");
}

void MainWindow::navigateHistoryUp()
{
    ui->label_Ans->setText("");
    if(history[upHistory].length() == 0) return;
    ui->label->setText(history[upHistory]);
    if(upHistory == 0 && historySize > 9) upHistory = 9;
    else if(upHistory == 0 && historySize < 10) upHistory = historySize - 1;
    else upHistory--;
}

void MainWindow::navigateHistoryDown()
{
    ui->label_Ans->setText("");
    if(history[downHistory].length() == 0) return;
    ui->label->setText(history[downHistory]);
    if(downHistory == historySize - 1) downHistory = 0;
    else downHistory++;
}
