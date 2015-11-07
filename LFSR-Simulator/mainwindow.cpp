#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(300,500);
    polyField = new QLineEdit(this);
    startValueField = new QLineEdit(this);
    generateButton = new QPushButton(this);
    randomButton = new QPushButton(this);
    resultDoc = new QTextDocument("Results Shown Here...");
    roundsBox = new QSpinBox(this);
    polyLable = new QLabel("Polynomial",this);
    startValueLabel = new QLabel("Initial Value", this);
    roundsLabel = new QLabel("Rounds:", this);
    resultViewer = new QTextBrowser(this);

    polyLable->setGeometry(5,5,290,15);
    polyField->setGeometry(5,20,290,25);

    startValueLabel->setGeometry(5,50,290,15);
    startValueField->setGeometry(5,65,290,25);

    generateButton->setGeometry(5,100,75,25);
    generateButton->setText("Generate");

    randomButton->setGeometry(215,100,75,25);
    randomButton->setText("Random");

    roundsBox->setGeometry(135,100,75,25);
    roundsBox->setValue(0);
    roundsBox->setMinimum(0);
    roundsBox->setMaximum(10000000);

    roundsLabel->setGeometry(90,100,70,25);

    resultViewer->setGeometry(5,150,290,370);
    resultViewer->setDocument(resultDoc);

    connect(generateButton, SIGNAL(clicked(bool)), this, SLOT(generate_f()));
    connect(randomButton, SIGNAL(clicked(bool)), this, SLOT(random_f()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::generate_f(){
    QString polyString = polyField->text();
    QString startString = polyField->text();

    if(polyString.length() != startString.length()){
        resultDoc->setPlainText("Invalid Input");
        return;
    }

    if(!checkInput(polyString)){
        return;
    }
    if(!checkInput(startString)){
        return;
    }

    if((polyData = convertData(polyString)) == NULL){
        resultDoc->setPlainText("Invalid Input");
        return;
    }

    if((initData = convertData(startString)) == NULL){
        resultDoc->setPlainText("Invalid Input");
        return;
    }

    generateOutput();
}

void MainWindow::random_f()
{

}

bool MainWindow::checkInput(QString input){
    if(input.length() < 1){
        resultDoc->setPlainText("Invalid Input");
        return false;
    }


    return true;
}

QList<bool>* MainWindow::convertData(QString input){
    QList<bool> *list = new QList<bool>();
    for(int i = 0; i < input.length(); i++){
        if(input[i] == '1'){
            list->append(true);
        } else if(input[i] == '0'){
            list->append(false);
        } else {
            return NULL;
        }
    }
    return list;
}

void MainWindow::generateOutput(){
    QList<bool> *output = new QList<bool>();
    int rounds = roundsBox->value();
    bool curr;
    for(int i = 0; i < rounds; i++){
        curr = false;
        for(int j = 0; j < polyData->length(); j++){
            if(polyData->at(j)){
                curr ^= initData->at(j);
            }
        }
        output->append(initData->first());
        initData->pop_front();
        initData->push_back(curr);
    }
    QString outputString = "";
    for(int i = 0; i < output->length(); i++){
        if(output->at(i)){
            outputString.append('1');
        } else {
            outputString.append('0');
        }
    }
    resultDoc->setPlainText(outputString);
    return;
}





