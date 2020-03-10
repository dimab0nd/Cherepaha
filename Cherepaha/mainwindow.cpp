#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cherepaha.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include "kruskal-dsu.hpp"
#include <vector>
#include <QPair>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file_name = "";
    points.clear();

}

void MainWindow::Show_File_Error(const unsigned int	 &line)
{
    QString error_text = "Something went wrong on line " + QString::number(line) + "!" ;
    QMessageBox::warning(this,"Error",error_text);

}
void MainWindow::Show_File_Error(const unsigned int &line,  const QCharRef &ch)
{
    QString error_text = "Something went wrong on line " + QString::number(line) + "!";
    error_text += "\nUnknown instruction: "+ ch;
    QMessageBox::warning(this,"Error",error_text);
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
        QMessageBox::warning(this,"Error","file not open!");

    }
    else
    {

        points.clear();
        unsigned int lines_count = 0;
        unsigned int entries_count = 0;
        QTextStream in(&file);
        bool success;
        QString command_line,number;
        do
        {
            success = true;
            number = in.readLine(); lines_count++; entries_count++;
            if(number == "") continue;
            int n = number.toInt(&success);
            if(!success)
            {
                Show_File_Error(lines_count);
                break;
            };
            command_line = in.readLine(); lines_count++;
            command_line = command_line.toUpper();
            if(command_line == "")
            {
                success = false;
                Show_File_Error(lines_count);
                continue;
            };


            Cherepaha* cherepaha = new Cherepaha();
            for(int i = 0; i<command_line.length(); i++)
            {
                if(command_line[i] == 'L') cherepaha->SetTurn(L);
                    else
                     if(command_line[i] == 'R') cherepaha->SetTurn(R);
                         else
                          if(command_line[i] == 'F') *cherepaha = *cherepaha + F;
                               else
                               if(command_line[i] == 'B') *cherepaha = *cherepaha + B;
                                    else
                               {
                                   success = false;
                                   Show_File_Error(lines_count,command_line[i]);
                                   break;
                               }
            };
            if(success)
            {
                (*cherepaha)*=n;
                QPair<int,int> ans = cherepaha->GetCurrentPos();
                points.push_back(ans);
                QString answer_message = "\n-------------------------------------------------------\n";
                answer_message += QString::number(entries_count) + ") Answer is  x = " + QString::number(ans.first) + " y = " + QString::number(ans.second) + "!\n";
               // QMessageBox::information(this,"Answer",answer_message);
                ui->textBrowser->append(answer_message);

            };
            delete(cherepaha);


        } while (number!= "");

    }
    file.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filter = "Text File (*.txt)";
    file_name = QFileDialog::getOpenFileName(this,"open a file","C://",filter);
    ui->textBrowser->setPlainText("Your file: " + file_name + '\n');


}

void MainWindow::on_pushButton_MST_clicked()
{
    if(points.size() < 2)
    {
        QMessageBox::warning(this,"Error", "Tree not found");
    }
    else
    {
        QVector<QPair<QPair<int,int>,QPair<int,int>>> ans = MST::kruskal(points);
        QString answer_message = "";
        answer_message += "\n-------------------------------------------------------\n";
        answer_message += "MST ребра:\n";
        ui->textBrowser->append(answer_message);
        for (int i = 0; i<ans.size();i++)
        {
            answer_message = "";
            answer_message += QString::number(i+1) + ") \n  x1 = " + QString::number(ans[i].first.first) + " y1 = " + QString::number(ans[i].first.second) + "\n";
            answer_message += "\n   x2 = " + QString::number(ans[i].second.first) + " y2 = " + QString::number(ans[i].second.second) + "\n";
            ui->textBrowser->append(answer_message);
        }

    }
}


