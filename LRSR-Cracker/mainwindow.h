#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextDocument>
#include <QLabel>
#include <QTextBrowser>
#include <QList>
#include <QApplication>
#include <QDebug>
#include <QLCDNumber>
#include <QPalette>
#include <QVector>

#include <cmath>

typedef quint8 byte;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QTextEdit *inputField;
    QLabel *inputLabel;
    QPushButton *solveButton;
    QLabel *sequenceLabel;
    QTextBrowser *sequenceResult;
    QTextDocument *sequenceDoc;
    QLabel *polyLabel;
    QTextDocument *polyDoc;
    QTextBrowser *polyResult;
    QLabel *initLabel;
    QTextDocument *initDoc;
    QTextBrowser *initResult;
    QLabel *degreeLabel;
    QLCDNumber *degreeValue;

    QList<bool> *inputData;
    //QList<bool> *polyData;

    bool checkInput(QString input);
    QList<bool>* convertString(QString input);
    int determineSequence(QList<bool>* data);
    QList<bool>* generateOutput(QList<bool> *init, QList<bool> *poly, int round);
    QString* convertList(QList<bool>* data);
    int solve();

public slots:
    void go();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();    
};



#endif // MAINWINDOW_H
