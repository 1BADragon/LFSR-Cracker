#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextDocument>
#include <QSpinBox>
#include <QLabel>
#include <QWidget>
#include <QTextBrowser>
#include <QList>
#include <QApplication>
#include <cstdlib>
#include <time.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLineEdit *polyField;
    QLineEdit *startValueField;
    QPushButton *generateButton;
    QPushButton *randomButton;
    QTextDocument *resultDoc;
    QSpinBox *roundsBox;
    QLabel *polyLable;
    QLabel *startValueLabel;
    QLabel *roundsLabel;
    QTextBrowser *resultViewer;

    QList<bool> *polyData;
    QList<bool> *data;

    bool checkInput(QString input);
    QList<bool>* convertData(QString input);
    void generateOutput();

public slots:
    void generate_f();
    void random_f();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
