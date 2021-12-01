#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString history[10] = { "" };
    int upHistory = 0, downHistory = 0, newestHistory = 0, oldestHistory = 0, nextHistory = 0, historySize = 0;

private slots:
    void inputButton_pressed();

    void exeButton_pressed();

    void delButton_pressed();

    void clearButton_pressed();

    void navigateHistoryUp();

    void navigateHistoryDown();

};
#endif // MAINWINDOW_H
