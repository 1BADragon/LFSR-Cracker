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

#include <cmath>

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

    bool checkInput(QString input);
    QList<bool>* convertString(QString input);
    int determineSequence(QList<bool>* data);
    QList<bool>* generateOutput(QList<bool> *init, QList<bool> *poly, int round);
    QString* convertList(QList<bool>* data);

public slots:
    void solve();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();    
};

#endif // MAINWINDOW_H
