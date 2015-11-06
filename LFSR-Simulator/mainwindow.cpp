#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(300,500);
    poly = new QLineEdit(this);
    startValue = new QLineEdit(this);
    generate = new QPushButton(this);
    random = new QPushButton(this);
    result = new QTextDocument(this);
    rounds = new QSpinBox(this);

    poly->setGeometry(5,5,290,25);

    //startValue->setGeometry();

}

MainWindow::~MainWindow()
{

}
