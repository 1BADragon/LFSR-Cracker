#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextDocument>
#include <QSpinBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLineEdit *poly;
    QLineEdit *startValue;
    QPushButton *generate;
    QPushButton *random;
    QTextDocument *result;
    QSpinBox *rounds;

public slots:

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
