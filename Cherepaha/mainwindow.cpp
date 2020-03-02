#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cherepaha.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

Cherepaha cherepaha;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file_name = "";
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"warning","file not open!");
    }
    QTextStream in(&file);
    bool success = true;
    QString number = in.readLine();
    int n = number.toInt(&success);
    QString text = in.readLine();
    text = text.toUpper();
    while(text != "" && success)
    {
        for(int i = 0; i<text.length(); i++)
        {
            if(text[i]== 'L') cherepaha.SetTurn(L);
                else
                 if(text[i]== 'R') cherepaha.SetTurn(R);
                     else
                      if(text[i]== 'F') cherepaha = cherepaha + F;
                           else
                           if(text[i]== 'B') cherepaha = cherepaha + B;
                                else
                           {
                               success = false;
                               QMessageBox::warning(this,"warning","wrong instruction - "+text[i]);
                               break;
                           }
        }
        text = in.readLine();
    }
    if(success)
    {
        std::pair<int,int> ans = cherepaha.GetCurrentPos();
        ans.first*=n;
        ans.second*=n;
        QString answer_message = "Answer is  x = " + QString::number(ans.first) + " y = " + QString::number(ans.second);
        QMessageBox::information(this,"Answer",answer_message);
    }
    file.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filter = "Text File (*.txt)";
    file_name = QFileDialog::getOpenFileName(this,"open a file","C://",filter);
    ui->plainTextEdit->setPlainText(file_name + '\n');

}
