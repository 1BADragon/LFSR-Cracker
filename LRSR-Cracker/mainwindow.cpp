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

    sequenceLabel = new QLabel("Initial Sequence",this);
    sequenceLabel->setGeometry(335,5,160,15);

    sequenceDoc = new QTextDocument();
    sequenceDoc->setPlainText("Initial Sequnce will be displayed here...");

    sequenceResult = new QTextBrowser(this);
    sequenceResult->setGeometry(335,20,260,50);
    sequenceResult->setDocument(sequenceDoc);

    degreeLabel = new QLabel("Degree:", this);
    degreeLabel->setGeometry(335, 80, 100, 15);

    degreeValue = new QLCDNumber(this);
    degreeValue->setGeometry(385, 75, 50, 25);
    QPalette LCDpalette= degreeValue->palette();
    LCDpalette.setColor(LCDpalette.WindowText,QColor(0,255,0));
    degreeValue->setPalette(LCDpalette);
    degreeValue->display(0);

    polyLabel = new QLabel("Polynomial:", this);
    polyLabel->setGeometry(335, 80+35, 260, 15);

    polyDoc = new QTextDocument();
    polyDoc->setPlainText("Polynomial will be displayed here...");

    polyResult = new QTextBrowser(this);
    polyResult->setGeometry(335,95+35,260,50);
    polyResult->setDocument(polyDoc);

    initLabel = new QLabel("Initial Value:",this);
    initLabel->setGeometry(335, 155+35, 260, 15);

    initDoc = new QTextDocument();
    initDoc->setPlainText("Initial value will be displayed here...");

    initResult = new QTextBrowser(this);
    initResult->setGeometry(335,170+35,260,50);
    initResult->setDocument(initDoc);

    connect(solveButton,SIGNAL(clicked(bool)), this, SLOT(go()));

    inputData = new QList<bool>();
}

MainWindow::~MainWindow()
{

}


void MainWindow::go()
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

    QList<bool> *tempData = convertString(input);

    int sequenceSize = determineSequence(tempData);
    inputData->clear();
    inputData->append(tempData->mid(0,sequenceSize));
    sequenceDoc->setPlainText(*convertList(inputData));

    int result = solve();
    degreeValue->display(result);

    QList<bool> *initValue = new QList<bool>();
    initValue->append(inputData->mid(0,result));
    initDoc->setPlainText(*convertList(initValue));
    delete tempData;
    delete initValue;
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

// BERLEKAMP-MASSEY ALGORITHM
int MainWindow::solve()
{
    QVector<byte> s(this->inputData->length());
    for (int i = 0; i < s.length(); i++)
    {
         if(inputData->at(i))
         {
             s[i] = 1;
         }
         else
         {
             s[i] = 0;
         }
    }

    int L, N, m, d;

    int n = s.size();
    QVector<byte> c(n);
    QVector<byte> b(n);
    QVector<byte> t(n);

    //Initialization
    b[0]=c[0]=1;
    N=L=0;
    m=-1;

    while(N < n)
    {
        d=s[N];
        for(int i=1; i <= L; i++)
        {
            d ^= c[i]&s[N-i];
        }
        if (d==1)
        {
            t.clear();
            t.append(c);
            for(int i=0; (i+N-m)<n; i++)
            {
                c[i+N-m]^=b[i];
            }
            if(L<=(N>>1))
            {
                L=N+1-L;
                m=N;
                b.clear();
                b.append(t);
            }
        }
        N++;
    }
    return L;
}

void MainWindow::arrayCopy(byte *src, byte *dest, int size)
{
    for (int i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
}


