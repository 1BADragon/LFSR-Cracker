#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(600,300);

    inputField = new QTextEdit(this);
    inputField->setGeometry(5,20,245,275);

    inputLabel = new QLabel("Input:", this);
    inputLabel->setGeometry(5,5,245,15);

    solveButton = new QPushButton(this);
    solveButton->setGeometry(255,20,75,275);
    solveButton->setText("Solve\n---->");

    sequenceLabel = new QLabel("Sequence:",this);
    sequenceLabel->setGeometry(335,5,160,15);

    sequenceDoc = new QTextDocument();
    sequenceDoc->setPlainText("Sequence will be displayed here...");

    sequenceResult = new QTextBrowser(this);
    sequenceResult->setGeometry(335,20,260,50);
    sequenceResult->setDocument(sequenceDoc);

    polyLabel = new QLabel("Polynomial:", this);
    polyLabel->setGeometry(335, 80, 260, 15);

    polyDoc = new QTextDocument();
    polyDoc->setPlainText("Polynomial will be displayed here...");

    polyResult = new QTextBrowser(this);
    polyResult->setGeometry(335,95,260,50);
    polyResult->setDocument(polyDoc);

    initLabel = new QLabel("Initial Value:",this);
    initLabel->setGeometry(335, 155, 260, 15);

    initDoc = new QTextDocument();
    initDoc->setPlainText("Initial value will be displayed here...");

    initResult = new QTextBrowser(this);
    initResult->setGeometry(335,170,260,50);
    initResult->setDocument(initDoc);

    connect(solveButton,SIGNAL(clicked(bool)), this, SLOT(solve()));
}

MainWindow::~MainWindow()
{

}


void MainWindow::solve()
{
    QString input = inputField->document()->toPlainText();

    if(input.length() <= 1)
    {
        sequenceDoc->setPlainText("Input too small");
        polyDoc->setPlainText("Input too small");
        return;
    }

    if(!checkInput(input))
    {
        sequenceDoc->setPlainText("Invalid Input");
        polyDoc->setPlainText("Invalid Input");
        return;
    }

    QList<bool> *inputData = convertString(input);
    int sequenceSize = determineSequence(inputData);
    qApp->processEvents();
    int maxInitSize = sequenceSize;
    int minInitSize = log2(sequenceSize+1);

    //qDebug() << maxInitSize << minInitSize;

    QList<bool> *sequence = convertString(sequenceDoc->toPlainText());
    QList<bool> *tempOutput = NULL;
    QList<bool> *initData = new QList<bool>();
    QList<bool> *tempInitData = new QList<bool>();
    QString tempPoly;
    bool escape = false;
    for(int i = minInitSize; i <= maxInitSize; i++)
    {
        initData->clear();
        initData->append(sequence->mid(0, i));
        long range = pow(2, initData->length());
        for(int j = 2; j < range; j++)
        {
            tempPoly = QString::number(j,2);
            while(tempPoly.length() < initData->length())
            {
                tempPoly.prepend('0');
            }
            //qDebug() << tempPoly << QString::fromStdString(convertList(initData)->toStdString());
            tempInitData->clear();
            tempInitData->append(*initData);
            if(tempOutput != NULL)
            {
                delete tempOutput;
            }
            tempOutput = generateOutput(tempInitData,convertString(QString::number(j,2)),inputData->length());
            //qDebug() << *convertList(tempOutput) << ((*tempOutput) == (*inputData));

            if((*tempOutput) == (*inputData))
            {
                qDebug() << *convertList(tempOutput);
                escape = true;
                break;
            }
        }
        if(escape)
        {
            break;
        }
    }
    if(escape)
    {
        initDoc->setPlainText(*convertList(initData));
        polyDoc->setPlainText(tempPoly);
    }
    else
    {
        initDoc->setPlainText("No Solution Found");
        polyDoc->setPlainText("No Solution Found");
    }
}

int MainWindow::determineSequence(QList<bool> *data)
{
    int offset = 0;
    bool collision;
    do
    {
        offset++;
        collision = false;
        for(int i = 0; i+offset<data->length(); i++)
        {
            if(data->at(i) != data->at(i+offset))
            {
                collision = true;
                break;
            }
        }
    }
    while(offset < data->length() && collision);

    QString temp;
    for (int i = 0; i < offset; i++)
    {
        if(data->at(i))
        {
            temp.append('1');
        }
        else
        {
            temp.append('0');
        }
    }

    sequenceDoc->setPlainText(temp);

    return offset;
}

QList<bool>* MainWindow::convertString(QString input)
{
    QList<bool> *data = new QList<bool>();
    for(int i = 0; i < input.length(); i++)
    {
        if(input[i] == '1')
        {
            data->append(true);
        }
        else
        {
            data->append(false);
        }
    }

    return data;
}

bool MainWindow::checkInput(QString input)
{
    for(int i = 0; i < input.length(); i++)
    {
        if(!(input[i] == '1' or input[i] == '0'))
        {
            return false;
        }
    }
    return true;
}

QList<bool>* MainWindow::generateOutput(QList<bool> *init, QList<bool> *poly, int rounds)
{
    bool curr;
    QList<bool> *output = new QList<bool>();
    for(int i = 0; i < rounds; i++){
        curr = init->first();
        for(int j = 1; j < poly->length(); j++){
            if(poly->at(j)){
                curr ^= init->at(j);
            }
        }
        output->append(curr);
        init->pop_front();
        init->push_back(curr);
    }
    return output;
}

QString* MainWindow::convertList(QList<bool> *data)
{
    QString *output = new QString();
    for(int i = 0; i < data->length(); i++)
    {
        if(data->at(i))
        {
            output->append('1');
        }
        else
        {
            output->append('0');
        }
    }
    return output;
}
