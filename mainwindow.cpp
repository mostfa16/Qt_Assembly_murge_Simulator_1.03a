#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qDebug.h>
#include <qtextstream.h>
#include <QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QFileDialog>
#include <QTableWidget>
#include <QLineEdit>
#include <QTableWidgetItem>
#include <QStringList>
#include<QWidgetItem>
#include <QByteArray>

int cmpGenerale;
QString codeSource;
QTextCursor cur;
bool test;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setFocus();
    cmpGenerale=0;
    test=false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::executeInstruction(QString instruction){
    QStringList lesMots=instruction.split(" ");
    if(!lesMots.at(0).compare("NOP")){

    }else if(!lesMots.at(0).compare("LOAD") || !lesMots.at(0).compare("LDR")){
        QStringList mot=lesMots.at(1).split(",");
        //qDebug() << "mot = "<< mot<<"lesMots = "<< lesMots;
        //qDebug() << "mot.at(1).at(0) = "<<mot.at(1).at(0);
        //qDebug() << "mot.at(1) = "<<mot.at(1);
        if(mot.at(1).at(0)=='@'){
            bool ok;
            QString aa=mot.at(1);
            //qDebug() << "aa1 = "<<aa;
            aa.remove(0,1);
            //qDebug() << "aa2 = "<<aa;
            int motInt=aa.toUInt(&ok,16);
            //qDebug() << "motint = "<<motInt;
            if(motInt>6) return false;
            QString bb=mot.at(0);
            //qDebug() << "bb1 = "<<bb;
            bb.remove(0,1);
            //qDebug() << "bb2 = "<<bb;
            int numRow=bb.toInt();
            //qDebug() << "numrow = "<<numRow;
            QString val=ui->tableWidget_2->item(motInt,1)->text();
            //qDebug() << "val = "<<val;
            ui->tableWidget_3->item(numRow,1)->setText(val);
        }else if(mot.at(1).at(0)=='#'){
            QString num=mot.at(1);
            //qDebug() << "num1 = "<<num;
            num.remove(0,1);
            //qDebug() << "num2 = "<<num;
            QString bb=mot.at(0);
            //qDebug() << "bb1 = "<<bb;
            bb.remove(0,1);
            //qDebug() << "bb2 = "<<bb;
            int numRow=bb.toInt();
            //qDebug() << "numRow = "<<numRow;
            ui->tableWidget_3->item(numRow,1)->setText(num);
        }
    }else if(!lesMots.at(0).compare("MOV")){
        QStringList mot=lesMots.at(1).split(",");
        //qDebug() << "mot = "<< mot<<"lesMots = "<< lesMots;
        if(mot.at(0).at(0)=='R')
            {if(mot.at(1).at(0)=='R')
                {bool ok;
                QString aa=mot.at(1);
                aa.remove(0,1);
                int motInt=aa.toUInt(&ok,16);
                if(motInt>6) return false;
                QString bb=mot.at(0);
                bb.remove(0,1);
                int numRow=bb.toInt();
                QString val=ui->tableWidget_3->item(motInt,1)->text();
                ui->tableWidget_3->item(numRow,1)->setText(val);

                }
            else if(mot.at(1).at(0)=='@')
                {bool ok;
                QString aa=mot.at(1);
                aa.remove(0,1);
                int motInt=aa.toUInt(&ok,16);
                if(motInt>6) return false;
                QString bb=mot.at(0);
                bb.remove(0,1);
                int numRow=bb.toInt();
                QString val=ui->tableWidget_2->item(motInt,1)->text();
                ui->tableWidget_3->item(numRow,1)->setText(val);

                }
            else if(mot.at(1).at(0)=='#')
                {
                QString num=mot.at(1);
                num.remove(0,1);
                QString bb=mot.at(0);
                //qDebug() << "bb1 = "<<bb;
                bb.remove(0,1);
                //qDebug() << "bb2 = "<<bb;
                int numRow=bb.toInt();
                //qDebug() << "numRow = "<<numRow;
                ui->tableWidget_3->item(numRow,1)->setText(num);
                }

            }
        else if(mot.at(0).at(0)=='@'){
            if(mot.at(1).at(0)=='R')
                            {bool ok;
                            QString aa=mot.at(1);
                            aa.remove(0,1);
                            qDebug() << "aa = "<<aa;
                            int motInt=aa.toUInt(&ok,16);
                            if(motInt>6) return false;
                            QString bb=mot.at(0);
                            bb.remove(0,1);
                            int numRow=bb.toInt();
                            qDebug() << "motInt = "<<motInt;
                            QString val=ui->tableWidget_3->item(motInt,1)->text();
                            qDebug() << "val = "<<val;
                            ui->tableWidget_2->item(numRow,1)->setText(val);

                            }
                        else if(mot.at(1).at(0)=='@')
                            {bool ok;
                            QString aa=mot.at(1);
                            aa.remove(0,1);
                            int motInt=aa.toUInt(&ok,16);
                            if(motInt>6) return false;
                            QString bb=mot.at(0);
                            bb.remove(0,1);
                            int numRow=bb.toInt();
                            QString val=ui->tableWidget_2->item(motInt,1)->text();
                            ui->tableWidget_2->item(numRow,1)->setText(val);

                            }
                        else if(mot.at(1).at(0)=='#')
                            {
                            QString num=mot.at(1);
                            num.remove(0,1);
                            QString bb=mot.at(0);
                            //qDebug() << "bb1 = "<<bb;
                            bb.remove(0,1);
                            //qDebug() << "bb2 = "<<bb;
                            int numRow=bb.toInt();
                            //qDebug() << "numRow = "<<numRow;
                            ui->tableWidget_2->item(numRow,1)->setText(num);
                            }

        }
    }else if(!lesMots.at(0).compare("STORE")|| !lesMots.at(0).compare("STR")){
        QStringList mot=lesMots.at(1).split(",");
        if(mot.at(0).at(0)=='R'){
            bool ok;
            QString aa=mot.at(1);
            aa.remove(0,1);
            int motInt=aa.toUInt(&ok,16);
            if(motInt>6) return false;
            QString bb=mot.at(0);
            bb.remove(0,1);
            int numRow=bb.toInt();
            QString val=ui->tableWidget_3->item(numRow,1)->text();
            ui->tableWidget_2->item(motInt,1)->setText(val);
        }else{
            bool ok;
            QString aa=mot.at(1);
            aa.remove(0,1);
            int motInt=aa.toUInt(&ok,16);
            if(motInt>6) return false;
            QString bb=mot.at(0);
            bb.remove(0,1);
            ui->tableWidget_2->item(motInt,1)->setText(bb);
        }
    }else if(!lesMots.at(0).compare("ADD")){
        QStringList mot=lesMots.at(1).split(",");
        int cp=mot.size();
        if(cp==2){
        if(mot.at(1).at(0)=='@'){
            QString bb=mot.at(1);
            bb.remove(0,1);
            bool ok;
            int numRow=bb.toUInt(&ok,16);
            if(numRow>6) return false;
            QString aa=mot.at(0);
            aa.remove(0,1);
            int num=aa.toInt();
            QString val1=ui->tableWidget_3->item(num,1)->text();
            QString val2=ui->tableWidget_2->item(numRow,1)->text();
            int som=val1.toInt()+val2.toInt();
            ui->tableWidget_3->item(num,1)->setText(QString::number(som));
        }else if(mot.at(1).at(0)=='#'){
            QString bb=mot.at(1);
            bb.remove(0,1);
            int nb=bb.toInt();
            QString aa=mot.at(0);
            aa.remove(0,1);
            int num=aa.toInt();
            QString val1=ui->tableWidget_3->item(num,1)->text();
            int som=nb+val1.toInt();
            ui->tableWidget_3->item(num,1)->setText(QString::number(som));
        }else if(mot.at(1).at(0)=='R'){
            QString bb=mot.at(1);
            bb.remove(0,1);
            bool ok;
            int numRow=bb.toUInt(&ok,16);
            if(numRow>6) return false;
            QString aa=mot.at(0);
            aa.remove(0,1);
            int num=aa.toInt();
            QString val1=ui->tableWidget_3->item(num,1)->text();
            QString val2=ui->tableWidget_3->item(numRow,1)->text();
            int som=val1.toInt()+val2.toInt();
            ui->tableWidget_3->item(num,1)->setText(QString::number(som));
        }
        }else if(cp==3)
        {
             if(mot.at(2).at(0)=='#'){
                QString bb=mot.at(2);
                bb.remove(0,1);
                int nb=bb.toInt();
                QString aa=mot.at(1);
                aa.remove(0,1);
                int num=aa.toInt();
                QString val1=ui->tableWidget_3->item(num,1)->text();
                int som=nb+val1.toInt();

                QString cc=mot.at(0);
                cc.remove(0,1);
                int c=cc.toInt();
                ui->tableWidget_3->item(c,1)->setText(QString::number(som));
            }else if(mot.at(2).at(0)=='R'){
                 QString bb=mot.at(2);
                 bb.remove(0,1);
                 int nb=bb.toInt();
                 QString val2=ui->tableWidget_3->item(nb,1)->text();

                 QString aa=mot.at(1);
                 aa.remove(0,1);
                 int num=aa.toInt();
                 QString val1=ui->tableWidget_3->item(num,1)->text();

                 int som=val2.toInt()+val1.toInt();

                 QString cc=mot.at(0);
                 cc.remove(0,1);
                 int c=cc.toInt();
                 ui->tableWidget_3->item(c,1)->setText(QString::number(som));
        }}
    }else if(!lesMots.at(0).compare("MUL")){
        QStringList mot=lesMots.at(1).split(",");
        int cp=mot.size();
        if(cp==2){
        if(mot.at(1).at(0)=='@'){
            QString bb=mot.at(1);
            bb.remove(0,1);
            bool ok;
            int numRow=bb.toUInt(&ok,16);
            if(numRow>6) return false;
            QString aa=mot.at(0);
            aa.remove(0,1);
            int num=aa.toInt();
            QString val1=ui->tableWidget_3->item(num,1)->text();
            QString val2=ui->tableWidget_2->item(numRow,1)->text();
            int som=val1.toInt()*val2.toInt();
            ui->tableWidget_3->item(num,1)->setText(QString::number(som));
        }else  if(mot.at(1).at(0)=='#'){
            QString bb=mot.at(1);
            bb.remove(0,1);
            int nb=bb.toInt();
            QString aa=mot.at(0);
            aa.remove(0,1);
            int num=aa.toInt();
            QString val1=ui->tableWidget_3->item(num,1)->text();
            int som=nb*val1.toInt();
            ui->tableWidget_3->item(num,1)->setText(QString::number(som));

        } else if(mot.at(1).at(0)=='R'){
            QString bb=mot.at(1);
            bb.remove(0,1);
            bool ok;
            int numRow=bb.toUInt(&ok,16);
            if(numRow>6) return false;
            QString aa=mot.at(0);
            aa.remove(0,1);
            int num=aa.toInt();
            QString val1=ui->tableWidget_3->item(num,1)->text();
            QString val2=ui->tableWidget_3->item(numRow,1)->text();
            int som=val1.toInt()*val2.toInt();
            ui->tableWidget_3->item(num,1)->setText(QString::number(som));
        }
        }else if(cp==3){
            if(mot.at(2).at(0)=='#'){
                            QString bb=mot.at(2);
                            bb.remove(0,1);
                            int nb=bb.toInt();
                            QString aa=mot.at(1);
                            aa.remove(0,1);
                            int num=aa.toInt();
                            QString val1=ui->tableWidget_3->item(num,1)->text();
                            int som=val1.toInt()*nb;

                            QString cc=mot.at(0);
                            cc.remove(0,1);
                            int c=cc.toInt();
                            ui->tableWidget_3->item(c,1)->setText(QString::number(som));
                        }else if(mot.at(2).at(0)=='R'){
                             QString bb=mot.at(2);
                             bb.remove(0,1);
                             int nb=bb.toInt();
                             QString val2=ui->tableWidget_3->item(nb,1)->text();

                             QString aa=mot.at(1);
                             aa.remove(0,1);
                             int num=aa.toInt();
                             QString val1=ui->tableWidget_3->item(num,1)->text();

                             int som=val1.toInt()*val2.toInt();

                             QString cc=mot.at(0);
                             cc.remove(0,1);
                             int c=cc.toInt();
                             ui->tableWidget_3->item(c,1)->setText(QString::number(som));
                    }
    }}else if(!lesMots.at(0).compare("NEG")){
        //QStringList mot=lesMots.at(1).split(",");
        QString mot=lesMots.at(1);
        //qDebug() << "mot = "<< mot;
        //qDebug() << "mot.at(0) = "<< mot.at(0);
        if(mot.at(0)=='R'){
        mot=mot.remove(0,1);
        //qDebug() << "mot2 = "<< mot;
        //bool ok;
        int numRow=mot.toInt();
        //qDebug() << "numRow = "<< numRow;
        QString val2=ui->tableWidget_3->item(numRow,1)->text();
        //qDebug() << "val2 = "<< val2;
        int som=-1*val2.toInt();
        //qDebug() << "som = "<< som;
        ui->tableWidget_3->item(numRow,1)->setText(QString::number(som));
        }
        else{
            mot=mot.remove(0,1);
            //qDebug() << "mot2 = "<< mot;
            //bool ok;
            int numRow=mot.toInt();
            //qDebug() << "numRow = "<< numRow;
            QString val2=ui->tableWidget_2->item(numRow,1)->text();
            //qDebug() << "val2 = "<< val2;
            int som=-1*val2.toInt();
            //qDebug() << "som = "<< som;
            ui->tableWidget_2->item(numRow,1)->setText(QString::number(som));
        }
    }else if(!lesMots.at(0).compare("DEC")){
                //QStringList mot=lesMots.at(1).split(",");
                QString mot=lesMots.at(1);
                //qDebug() << "mot = "<< mot;
                //qDebug() << "mot.at(0) = "<< mot.at(0);
                if(mot.at(0)=='R'){
                mot=mot.remove(0,1);
                //qDebug() << "mot2 = "<< mot;
                //bool ok;
                int numRow=mot.toInt();
                //qDebug() << "numRow = "<< numRow;
                QString val2=ui->tableWidget_3->item(numRow,1)->text();
                //qDebug() << "val2 = "<< val2;
                int som=val2.toInt()-1;
                //qDebug() << "som = "<< som;
                ui->tableWidget_3->item(numRow,1)->setText(QString::number(som));
                }
                else{
                    mot=mot.remove(0,1);
                    //qDebug() << "mot2 = "<< mot;
                    //bool ok;
                    int numRow=mot.toInt();
                    //qDebug() << "numRow = "<< numRow;
                    QString val2=ui->tableWidget_2->item(numRow,1)->text();
                    //qDebug() << "val2 = "<< val2;
                    int som=val2.toInt()-1;
                    //qDebug() << "som = "<< som;
                    ui->tableWidget_2->item(numRow,1)->setText(QString::number(som));
    }
    }else if(!lesMots.at(0).compare("INC")){
                    //QStringList mot=lesMots.at(1).split(",");
                    QString mot=lesMots.at(1);
                    //qDebug() << "mot = "<< mot;
                    //qDebug() << "mot.at(0) = "<< mot.at(0);
                    if(mot.at(0)=='R'){
                    mot=mot.remove(0,1);
                    //qDebug() << "mot2 = "<< mot;
                    //bool ok;
                    int numRow=mot.toInt();
                    //qDebug() << "numRow = "<< numRow;
                    QString val2=ui->tableWidget_3->item(numRow,1)->text();
                    //qDebug() << "val2 = "<< val2;
                    int som=val2.toInt()+1;
                    //qDebug() << "som = "<< som;
                    ui->tableWidget_3->item(numRow,1)->setText(QString::number(som));
                    }
                    else{
                        mot=mot.remove(0,1);
                        //qDebug() << "mot2 = "<< mot;
                        //bool ok;
                        int numRow=mot.toInt();
                        //qDebug() << "numRow = "<< numRow;
                        QString val2=ui->tableWidget_2->item(numRow,1)->text();
                        //qDebug() << "val2 = "<< val2;
                        int som=val2.toInt()+1;
                        //qDebug() << "som = "<< som;
                        ui->tableWidget_2->item(numRow,1)->setText(QString::number(som));
                    }
    }else if(!lesMots.at(0).compare("DIV")){
        QStringList mot=lesMots.at(1).split(",");
        int cp=mot.size();
        if(cp==2){
        if(mot.at(1).at(0)=='@'){
            QString bb=mot.at(1);
            bb.remove(0,1);
            bool ok;
            int numRow=bb.toUInt(&ok,16);
            if(numRow>6) return false;
            QString aa=mot.at(0);
            aa.remove(0,1);
            int num=aa.toInt();
            QString val1=ui->tableWidget_3->item(num,1)->text();
            QString val2=ui->tableWidget_2->item(numRow,1)->text();
            if(val2.toInt()!=0)
            {
            int som=val1.toInt()/val2.toInt();
            ui->tableWidget_3->item(num,1)->setText(QString::number(som));
            }else QMessageBox::information(this,"Message d'information","division par zéro impossible",
                                           QMessageBox::Information);
        }else  if(mot.at(1).at(0)=='#'){
            QString bb=mot.at(1);
            bb.remove(0,1);
            int nb=bb.toInt();
            QString aa=mot.at(0);
            aa.remove(0,1);
            int num=aa.toInt();
            QString val1=ui->tableWidget_3->item(num,1)->text();
            if(nb!=0)
            {int som=val1.toInt()/nb;
            ui->tableWidget_3->item(num,1)->setText(QString::number(som));
            }else QMessageBox::information(this,"Message d'information","division par zéro impossible",
                                           QMessageBox::Information);

        } else if(mot.at(1).at(0)=='R'){
            QString bb=mot.at(1);
            bb.remove(0,1);
            bool ok;
            int numRow=bb.toUInt(&ok,16);
            if(numRow>6) return false;
            QString aa=mot.at(0);
            aa.remove(0,1);
            int num=aa.toInt();
            QString val1=ui->tableWidget_3->item(num,1)->text();
            QString val2=ui->tableWidget_3->item(numRow,1)->text();
            if(val2.toInt()!=0)
            {int som=val1.toInt()/val2.toInt();
            ui->tableWidget_3->item(num,1)->setText(QString::number(som));
            }else QMessageBox::information(this,"Message d'information","division par zéro impossible",
                                           QMessageBox::Information);
        }
        }else if(cp==3)
        {if(mot.at(2).at(0)=='#'){
                QString bb=mot.at(2);
                bb.remove(0,1);
                int nb=bb.toInt();
                QString aa=mot.at(1);
                aa.remove(0,1);
                int num=aa.toInt();
                QString val1=ui->tableWidget_3->item(num,1)->text();
                if(nb!=0)
                {int som=val1.toInt()/nb;

                QString cc=mot.at(0);
                cc.remove(0,1);
                int c=cc.toInt();
                ui->tableWidget_3->item(c,1)->setText(QString::number(som));
                }else QMessageBox::information(this,"Message d'information","division par zéro impossible",
                                               QMessageBox::Information);
            }else if(mot.at(2).at(0)=='R'){
                 QString bb=mot.at(2);
                 bb.remove(0,1);
                 int nb=bb.toInt();
                 QString val2=ui->tableWidget_3->item(nb,1)->text();

                 QString aa=mot.at(1);
                 aa.remove(0,1);
                 int num=aa.toInt();
                 QString val1=ui->tableWidget_3->item(num,1)->text();
                 if(val2.toInt()!=0)
                 {int som=val1.toInt()/val2.toInt();

                 QString cc=mot.at(0);
                 cc.remove(0,1);
                 int c=cc.toInt();
                 ui->tableWidget_3->item(c,1)->setText(QString::number(som));
                 }else QMessageBox::information(this,"Message d'information","division par zéro impossible",
                                                QMessageBox::Information);
        }}
    }else if(!lesMots.at(0).compare("SUB")){
        QStringList mot=lesMots.at(1).split(",");
        int cp=mot.size();
        if(cp==2){
        if(mot.at(1).at(0)=='@'){
            QString bb=mot.at(1);
            bb.remove(0,1);
            bool ok;
            int numRow=bb.toUInt(&ok,16);
            if(numRow>6) return false;
            QString aa=mot.at(0);
            aa.remove(0,1);
            int num=aa.toInt();
            QString val1=ui->tableWidget_3->item(num,1)->text();
            QString val2=ui->tableWidget_2->item(numRow,1)->text();
            int som=val1.toInt()-val2.toInt();//som=som*-1;
            ui->tableWidget_3->item(num,1)->setText(QString::number(som));
        }else if(mot.at(1).at(0)=='#'){
            QString bb=mot.at(1);
            bb.remove(0,1);
            int nb=bb.toInt();
            QString aa=mot.at(0);
            aa.remove(0,1);
            int num=aa.toInt();
            QString val1=ui->tableWidget_3->item(num,1)->text();
            int som=val1.toInt()-nb;
            ui->tableWidget_3->item(num,1)->setText(QString::number(som));
        }else if(mot.at(1).at(0)=='R'){
            QString bb=mot.at(1);
            bb.remove(0,1);
            bool ok;
            int numRow=bb.toUInt(&ok,16);
            if(numRow>6) return false;
            QString aa=mot.at(0);
            aa.remove(0,1);
            int num=aa.toInt();
            QString val1=ui->tableWidget_3->item(num,1)->text();
            QString val2=ui->tableWidget_3->item(numRow,1)->text();
            int som=val1.toInt()-val2.toInt();
            ui->tableWidget_3->item(num,1)->setText(QString::number(som));
        }
        }else if(cp==3)
        {
             if(mot.at(2).at(0)=='#'){
                QString bb=mot.at(2);
                bb.remove(0,1);
                int nb=bb.toInt();
                QString aa=mot.at(1);
                aa.remove(0,1);
                int num=aa.toInt();
                QString val1=ui->tableWidget_3->item(num,1)->text();
                int som=val1.toInt()-nb;

                QString cc=mot.at(0);
                cc.remove(0,1);
                int c=cc.toInt();
                ui->tableWidget_3->item(c,1)->setText(QString::number(som));
            }else if(mot.at(2).at(0)=='R'){
                 QString bb=mot.at(2);
                 bb.remove(0,1);
                 int nb=bb.toInt();
                 QString val2=ui->tableWidget_3->item(nb,1)->text();

                 QString aa=mot.at(1);
                 aa.remove(0,1);
                 int num=aa.toInt();
                 QString val1=ui->tableWidget_3->item(num,1)->text();

                 int som=val1.toInt()-val2.toInt();

                 QString cc=mot.at(0);
                 cc.remove(0,1);
                 int c=cc.toInt();
                 ui->tableWidget_3->item(c,1)->setText(QString::number(som));
        }}
    }else if(!lesMots.at(0).compare("RSB")){
        QStringList mot=lesMots.at(1).split(",");

             if(mot.at(2).at(0)=='#'){
                QString bb=mot.at(2);
                bb.remove(0,1);
                int nb=bb.toInt();
                QString aa=mot.at(1);
                aa.remove(0,1);
                int num=aa.toInt();
                QString val1=ui->tableWidget_3->item(num,1)->text();
                int som=nb-val1.toInt();

                QString cc=mot.at(0);
                cc.remove(0,1);
                int c=cc.toInt();
                ui->tableWidget_3->item(c,1)->setText(QString::number(som));
            }else if(mot.at(2).at(0)=='R'){
                 QString bb=mot.at(2);
                 bb.remove(0,1);
                 int nb=bb.toInt();
                 QString val2=ui->tableWidget_3->item(nb,1)->text();

                 QString aa=mot.at(1);
                 aa.remove(0,1);
                 int num=aa.toInt();
                 QString val1=ui->tableWidget_3->item(num,1)->text();

                 int som=val2.toInt()-val1.toInt();

                 QString cc=mot.at(0);
                 cc.remove(0,1);
                 int c=cc.toInt();
                 ui->tableWidget_3->item(c,1)->setText(QString::number(som));
        }
    }else if(!lesMots.at(0).compare("BRANCH")){
        QStringList mot=lesMots.at(1).split(",");
        if(!mot.at(0).compare("LE")){
            QString adresse=mot.at(1);
            adresse.remove(0,1);
            bool ok;
            int numLigne=adresse.toUInt(&ok,16);
            if(numLigne>ui->tableWidget->rowCount()) return false;
            cmpGenerale=numLigne-1;
            cur.movePosition(QTextCursor::Start);
            for(int i=0;i<numLigne;i++){
                if(!cur.movePosition(QTextCursor::EndOfLine)){
                    QMessageBox::information(this,"Message d'information","La fin de code",
                                             QMessageBox::Information);
                    return false;
                }
                if(!cur.movePosition(QTextCursor::Right)){
                    QMessageBox::information(this,"Message d'information","La fin de code",
                                             QMessageBox::Information);
                    return false;
                }
            }
            test=true;
        }else{

        }
    }else if(!lesMots.at(0).compare("CALL")){
    }else if(!lesMots.at(0).compare("RET")){
    }else if(!lesMots.at(0).compare("PUSH")){
    }else if(!lesMots.at(0).compare("POP")){
    }else if(!lesMots.at(0).compare("HALT")){
    }
    return true;
}

bool MainWindow::verifier(QString text){//verifier la structeur de code
    if(!text.compare("")) return false;
  //  QStringList lingInstruction=text.split("\n");
    QString str = text;
        QStringList lingInstruction=str.split("\n",QString::SkipEmptyParts);
//QStringList lingInstruction=text.split("\n", QString::SkipEmptyParts);
    //qDebug() << "linginst = "<< lingInstruction ;
    for (int i = 0; i < lingInstruction.size(); ++i) {
        if(!lingInstruction.at(i).compare("")) return false;
        //qDebug() << "!lingInstruction.at(i).compare("") = "<< !lingInstruction.at(i).compare("") ;
        QStringList listDesMots=lingInstruction.at(i).split(" ");
        //qDebug() << "listDesMots = "<< listDesMots ;
        //qDebug() << "listDesMots.at(0) = "<< listDesMots.at(0) ;//codeop
        if(!listDesMots.at(0).compare("NOP")){
            if(listDesMots.size()!=1) return false;
        }else if(!listDesMots.at(0).compare("LOAD") || !listDesMots.at(0).compare("LDR")){//tester reg R
            if(listDesMots.size()!=2) return false;
            QStringList l=listDesMots.at(1).split(",");
            //qDebug()<< "l = "<< l;
            if(l.size()!=2) return false;
            if(!l.at(0).compare("R00")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R01")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R02")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R03")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R04")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R05")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R06")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R07")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R08")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R09")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R10")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R11")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R12")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R13")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R14")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R15")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R16")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R17")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R18")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R19")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R20")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R21")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R22")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R23")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R24")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R25")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R26")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R27")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R28")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R29")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R30")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;
            }else if(!l.at(0).compare("R31")){
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;

            }else return false;
        }else if(!listDesMots.at(0).compare("MOV")){
            if(listDesMots.size()!=2) return false;
            QStringList l=listDesMots.at(1).split(",");
            //qDebug()<< "l = "<< l;
            if(l.size()!=2) return false;
            QRegExp r("^R(0?|1|2)[0-9]$");
            QRegExp r1("^R3[0-1]$");
            QRegExp reg("^@[0-9A-F]{4}$");
            QRegExp reg1("^#[0-9]*$");
            if(!l.at(0).contains(r) && !l.at(0).contains(r1)&& !l.at(0).contains(reg)) return false;
            if(!l.at(1).contains(r) && !l.at(1).contains(r1)&& !l.at(1).contains(reg) && !l.at(1).contains(reg1)) return false;


        }else if(!listDesMots.at(0).compare("STORE") || !listDesMots.at(0).compare("STR")){
            if(listDesMots.size()!=2) return false;
            QStringList l=listDesMots.at(1).split(",");
            if(l.size()!=2) return false;
            QRegExp r("^R(0?|1|2)[0-9]$");
            QRegExp r1("^R3[0-1]$");
            QRegExp reg1("^#[0-9]*$");
            if(!l.at(0).contains(r) && !l.at(0).contains(r1) && !l.at(0).contains(reg1))
                return false;
            QRegExp reg("^@[0-9A-F]{4}$");
            if(!l.at(1).contains(reg)) return false;
        }else if(!listDesMots.at(0).compare("ADD")){
            if(listDesMots.size()!=2) return false;
            QStringList l=listDesMots.at(1).split(",");
            if(l.size()!=2 && l.size()!=3) return false;
            if(l.size()==2){
            QRegExp r("^R(0?|1|2)[0-9]");
            QRegExp r1("^R3[0-1]$");
            if(!l.at(0).contains(r) && !l.at(0).contains(r1)) return false;
            QRegExp reg("^@[0-9A-F]{4}$");
            QRegExp reg1("^#[0-9]*$");
            if(!l.at(1).contains(reg) && !l.at(1).contains(reg1) && !l.at(1).contains(r) && !l.at(1).contains(r1)) return false;}
            else if(l.size()==3){

                QRegExp r("^R(0?|1|2)[0-9]");
                QRegExp r1("^R3[0-1]$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(0).contains(r) && !l.at(0).contains(r1)) return false;
                if(!l.at(1).contains(r) && !l.at(1).contains(r1)) return false;
                if(!l.at(2).contains(r) && !l.at(2).contains(r1) && !l.at(2).contains(reg1)) return false;
            }
        }else if(!listDesMots.at(0).compare("SUB")){
            if(listDesMots.size()!=2) return false;
            QStringList l=listDesMots.at(1).split(",");
            if(l.size()!=2 && l.size()!=3) return false;
            if(l.size()==2){
            QRegExp r("^R(0?|1|2)[0-9]$");
            QRegExp r1("^R3[0-1]$");
            if(!l.at(0).contains(r) && !l.at(0).contains(r1)) return false;
            QRegExp reg("^@[0-9A-F]{4}$");
            QRegExp reg1("^#[0-9]*$");
            if(!l.at(1).contains(reg) && !l.at(1).contains(reg1) && !l.at(1).contains(r) && !l.at(1).contains(r1)) return false;}
            else if(l.size()==3){
                QRegExp r("^R(0?|1|2)[0-9]");
                QRegExp r1("^R3[0-1]$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(0).contains(r) && !l.at(0).contains(r1)) return false;
                if(!l.at(1).contains(r) && !l.at(1).contains(r1)) return false;
                if(!l.at(2).contains(r) && !l.at(2).contains(r1) && !l.at(2).contains(reg1)) return false;
            }
        }else if(!listDesMots.at(0).compare("RSB")){
            if(listDesMots.size()!=2) return false;
            QStringList l=listDesMots.at(1).split(",");
            if(l.size()!=3) return false;

            QRegExp r("^R(0?|1|2)[0-9]");
            QRegExp r1("^R3[0-1]$");
            QRegExp reg1("^#[0-9]*$");
            if(!l.at(0).contains(r) && !l.at(0).contains(r1)) return false;
            if(!l.at(1).contains(r) && !l.at(1).contains(r1)) return false;
            if(!l.at(2).contains(r) && !l.at(2).contains(r1) && !l.at(2).contains(reg1)) return false;
        }else if(!listDesMots.at(0).compare("BRANCH")){
            if(listDesMots.size()!=2) return false;
            QStringList l=listDesMots.at(1).split(",");
            if(l.size()!=2) return false;
            if(l.at(0).compare("LE") && l.at(0).compare("NC")) return false;
            QRegExp reg("^@[0-9A-F]{4}$");
            if(!l.at(1).contains(reg)) return false;
        }else if(!listDesMots.at(0).compare("CALL")){
            if(listDesMots.size()!=2) return false;
            QRegExp reg("^@[0-9A-F]{4}$");
            if(!listDesMots.at(1).contains(reg)) return false;
        }else if(!listDesMots.at(0).compare("RET")){
            if(listDesMots.size()!=1) return false;
        }else if(!listDesMots.at(0).compare("PUSH")){
            if(listDesMots.size()!=2) return false;
            QRegExp reg("^@[0-9A-F]{4}$");
            if(!listDesMots.at(1).contains(reg)) return false;
        }else if(!listDesMots.at(0).compare("POP")){
            if(listDesMots.size()!=1) return false;
        }else if(!listDesMots.at(0).compare("HALT")){
            if(listDesMots.size()!=1) return false;
        }else if(!listDesMots.at(0).compare("MUL")){
            if(listDesMots.size()!=2) return false;
            QStringList l=listDesMots.at(1).split(",");
            if(l.size()!=2 && l.size()!=3) return false;
            if(l.size()==2){
            QRegExp r("^R(0?|1|2)[0-9]$");
            QRegExp r1("^R3[0-1]$");
            if(!l.at(0).contains(r) && !l.at(0).contains(r1)) return false;
            QRegExp reg("^@[0-9A-F]{4}$");
            QRegExp reg1("^#[0-9]*$");
            if(!l.at(1).contains(reg) && !l.at(1).contains(reg1) && !l.at(1).contains(r) && !l.at(1).contains(r1)) return false;}
            else if(l.size()==3){
                QRegExp r("^R(0?|1|2)[0-9]");
                QRegExp r1("^R3[0-1]$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(0).contains(r) && !l.at(0).contains(r1)) return false;
                if(!l.at(1).contains(r) && !l.at(1).contains(r1)) return false;
                if(!l.at(2).contains(r) && !l.at(2).contains(r1) && !l.at(2).contains(reg1)) return false;
            }
        }else if(!listDesMots.at(0).compare("NEG")){
        if(listDesMots.size()!=2) return false;
        QStringList l=listDesMots.at(1).split(",");
        if(l.size()!=1) return false;
        QRegExp r("^R(0?|1|2)[0-9]$");
        QRegExp r1("^R3[0-1]$");
        QRegExp reg("^@[0-9A-F]{4}$");
        if(!l.at(0).contains(r) && !l.at(0).contains(r1)&& !l.at(0).contains(reg)) return false;
        }else if(!listDesMots.at(0).compare("DEC")){
            if(listDesMots.size()!=2) return false;
            QStringList l=listDesMots.at(1).split(",");
            if(l.size()!=1) return false;
            QRegExp r("^R(0?|1|2)[0-9]$");
            QRegExp r1("^R3[0-1]$");
            QRegExp reg("^@[0-9A-F]{4}$");
            if(!l.at(0).contains(r) && !l.at(0).contains(r1)&& !l.at(0).contains(reg)) return false;

        }else if(!listDesMots.at(0).compare("INC")){
            if(listDesMots.size()!=2) return false;
            QStringList l=listDesMots.at(1).split(",");
            if(l.size()!=1) return false;
            QRegExp r("^R(0?|1|2)[0-9]$");
            QRegExp r1("^R3[0-1]$");
            QRegExp reg("^@[0-9A-F]{4}$");
            if(!l.at(0).contains(r) && !l.at(0).contains(r1)&& !l.at(0).contains(reg)) return false;

        }
        else if(!listDesMots.at(0).compare("\n")){
qDebug()<<"jjjj";
        }
        else if(!listDesMots.at(0).compare("DIV")){
                if(listDesMots.size()!=2) return false;
                QStringList l=listDesMots.at(1).split(",");
                if(l.size()!=2 && l.size()!=3) return false;
                if(l.size()==2){
                QRegExp r("^R(0?|1|2)[0-9]$");
                QRegExp r1("^R3[0-1]$");
                if(!l.at(0).contains(r) && !l.at(0).contains(r1)) return false;
                QRegExp reg("^@[0-9A-F]{4}$");
                QRegExp reg1("^#[0-9]*$");
                if(!l.at(1).contains(reg) && !l.at(1).contains(reg1) && !l.at(1).contains(r) && !l.at(1).contains(r1)) return false;}
                else if(l.size()==3){
                    QRegExp r("^R(0?|1|2)[0-9]");
                    QRegExp r1("^R3[0-1]$");
                    QRegExp reg1("^#[0-9]*$");
                    if(!l.at(0).contains(r) && !l.at(0).contains(r1)) return false;
                    if(!l.at(1).contains(r) && !l.at(1).contains(r1)) return false;
                    if(!l.at(2).contains(r) && !l.at(2).contains(r1) && !l.at(2).contains(reg1)) return false;
                }
            }else return false;
    }
    return true;
}

QStringList MainWindow::getListeDesInstruction(QString text){//return la liste des instructions
    QStringList l,ll;
    l.clear();
    ll.clear();
   // l = l.toUpper();

    l=text.split("\n");

    for(int i=0;i<l.size();i++){

        ll.append(l.at(i).split(" ").at(0));

 //qDebug()<<"l.at(i) ===== "<<l.at(i).toUpper();
    }
//    qDebug()<< "ll (list inst) = "<<ll;

    return ll;
}

void MainWindow::on_pushButton_2_clicked()//LOAD
{
    QString fichier = QFileDialog::getOpenFileName(this, "Choisissez un fichier", "../MOSTFA_SIMULATEUR_1.03/TestTxt", "Text files (*.txt)");
    QFile mfile(fichier);
    mfile.open(QFile :: ReadOnly);
    QTextStream in (&mfile);
    QString texte = "";
    QString temp;
    do
    {
        temp= in.readLine()+"\n";

        texte += temp;

    }while(!in.atEnd());
    //texte.remove(texte.size()-1, 1);
    //texte.truncate(texte.size()-1);
    texte.resize(texte.size()-1);
    //texte.split(';').first();
    //texte.replace(";", "");
    ////qDebug()<< "texte = "<<texte;

    ui->textEdit->setText(texte);
    ui->textEdit->setFocus();
    ui->textEdit->moveCursor( QTextCursor::End, QTextCursor::MoveAnchor );
    ui->textEdit->moveCursor( QTextCursor::StartOfLine, QTextCursor::MoveAnchor );
    ui->textEdit->moveCursor( QTextCursor::End, QTextCursor::KeepAnchor );
    //textEdit->text().remove(textEdit->text().size()-1);

    mfile.close();
    ui->pushButton_3->setEnabled(true);
}

void MainWindow::on_pushButton_4_clicked()//CLEAR
{//execute en click sur le bouton clear
    ui->textEdit->setText("");
    cmpGenerale=0;
    ui->pushButton->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_3->setEnabled(true);
    while (ui->tableWidget->rowCount() > 0)
    {//vider la table d'instruction
        ui->tableWidget->removeRow(0);
    }
   // //qDebug()<<"aaaa = "<<ui->tableWidget_3
//    for(int i=0;i<32;i++)
    for(int i=0;i<ui->tableWidget_3->rowCount();i++)
    {//vider la table d'instruction
        ui->tableWidget_3->item(i,1)->setText("0");
    }
  /*  for(int i=0;i<6;i++)
    {//vider la table d'instruction
        ui->tableWidget_2->item(i,1)->setText("0");
    }*/

}

void MainWindow::on_pushButton_3_clicked()//compiler
{
        QString text=ui->textEdit->toPlainText();
        text=text.toUpper();
       // text.replace("\n{2,}","\n");
        qDebug()<< "text = "<<text;
        if(verifier(text)){
            ui->pushButton->setEnabled(true);
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_5->setEnabled(true);
            ui->lineEdit->setText("@0000");
            codeSource=text;
            QStringList listeDesInstruction=getListeDesInstruction(text);
            int cmp=0;
            for(int i=0;i<listeDesInstruction.size();i++){//remplir le tableau
                int row = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(row); //insérer une ligne vide à la fin du QTableWidget
                ui->tableWidget->setItem(row, 1
                                         ,new QTableWidgetItem(QString::number(i)));
                ui->tableWidget->setItem(row, 0
                                         ,new QTableWidgetItem(QString::number(i)));
                ui->tableWidget->item(row,1)->setText(listeDesInstruction.at(i));
                //qDebug()<<"row"<<row;
                QString hexa;
                hexa.setNum(cmp,16);
                if(i==0)  ui->tableWidget->item(row,0)->setText("@0000");
                else if(i>0 && i<16) ui->tableWidget->item(row,0)->setText("@000"+hexa);
                else if(i>15 && i<256) ui->tableWidget->item(row,0)->setText("@00"+hexa);
                else if(i>255 && i<4096) ui->tableWidget->item(row,0)->setText("@0"+hexa);
                else if(i>4095 && i<65536) ui->tableWidget->item(row,0)->setText("@"+hexa);
                cmp++;
            }
            ui->textEdit->setFocus();
            QTextCursor cursor(ui->textEdit->textCursor());
            cursor.movePosition(QTextCursor::Start);
            cur=cursor;
            ui->textEdit->setTextCursor(cursor);
        }else{
            QMessageBox::information(this,"Message d'information"
                                     ,"Erreur"
                                     ,QMessageBox::Information);
        }

}

void MainWindow::on_pushButton_clicked()//execute
{
    QStringList lingeDinstruction=codeSource.split("\n");
    //qDebug () <<"lingeDinstruction.at(cmpGenerale)" << lingeDinstruction.at(cmpGenerale);
    if(!executeInstruction(lingeDinstruction.at(cmpGenerale)))
        ui->lineEdit_2->setText("N");
    else ui->lineEdit_2->setText("P");
    ui->textEdit->setFocus();
    if(!test){
        if(!cur.movePosition(QTextCursor::EndOfLine)){
            QMessageBox::information(this,"Message d'information","La fin de code",
                                     QMessageBox::Information);
            ui->pushButton->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
            return ;
        }
        if(!cur.movePosition(QTextCursor::Right)){
            QMessageBox::information(this,"Message d'information","La fin de code",
                                     QMessageBox::Information);
            ui->pushButton->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
            return ;
        }
    }
    ui->textEdit->setTextCursor(cur);
    cmpGenerale++;
    test=false;
}

void MainWindow::on_pushButton_5_clicked()//executeALL
{
    QStringList lingeDinstruction=codeSource.split("\n");
    for(int i=0;i<lingeDinstruction.size();i++){

    if(!executeInstruction(lingeDinstruction.at(cmpGenerale)))
        ui->lineEdit_2->setText("N");
    else ui->lineEdit_2->setText("P");
    ui->textEdit->setFocus();
    if(!test){
        if(!cur.movePosition(QTextCursor::EndOfLine)){
            QMessageBox::information(this,"Message d'information","La fin de code!!!",
                                     QMessageBox::Information);
            ui->pushButton->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
            return ;
        }
        if(!cur.movePosition(QTextCursor::Right)){
            QMessageBox::information(this,"Message d'information","Tout Terminer",
                                     QMessageBox::Information);
            ui->pushButton->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
            return ;
        }
    }
    ui->textEdit->setTextCursor(cur);
    cmpGenerale++;
    test=false;
}

}
