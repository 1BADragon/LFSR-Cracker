#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(300,500);
    poly = new QLineEdit(this);
    startValue = new QLineEdit(this);
    generate = new QPushButton(this);
    random = new QPushButton(this);
    result = new QTextDocument("Results Shown Here...");
    rounds = new QSpinBox(this);
    polyLable = new QLabel("Polynomial",this);
    startValueLabel = new QLabel("Initial Value", this);
    roundsLabel = new QLabel("Rounds:", this);
    resultViewer = new QTextBrowser(this);

    polyLable->setGeometry(5,5,290,15);
    poly->setGeometry(5,20,290,25);

    startValueLabel->setGeometry(5,50,290,15);
    startValue->setGeometry(5,65,290,25);

    generate->setGeometry(5,100,75,25);
    generate->setText("Generate");

    random->setGeometry(215,100,75,25);
    random->setText("Random");

    rounds->setGeometry(135,100,75,25);
    rounds->setValue(0);
    rounds->setMinimum(0);
    rounds->setMaximum(10000000);

    roundsLabel->setGeometry(90,100,70,25);

    resultViewer->setGeometry(5,150,290,370);
    resultViewer->setDocument(result);
}

MainWindow::~MainWindow()
{

}
