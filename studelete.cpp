#include "studelete.h"
#include "ui_studelete.h"
#include "mainwindow.h"
#include <QDebug>

StuDelete::StuDelete(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StuDelete)
{
    ui->setupUi(this);
}

StuDelete::~StuDelete()
{
    delete ui;
}

QString StuDelete::event = "Default";//初始化事件文本

void StuDelete::SetTextForMe() const
{
    //setText方法,设置Line Edit的显示文本
    ui->LE1_Name->setText(MainWindow::Name);
}

void StuDelete::on_PB1_Yes_clicked()
{
    //qDebug() << MainWindow::SN;
    MainWindow::stuq1->exec("DELETE FROM stuinfo WHERE SN = '"+MainWindow::SN+"'");
    MainWindow::Alterstuqm1();
    MainWindow::Recovertableclicked();
    event = "成功删除学生 "+MainWindow::Name+"!";
    MainWindow::AlterEvent(event);
    this->close();
    ui->LE1_Name->setText("");
}

void StuDelete::on_PB2_No_clicked()
{
    event = "已取消删除学生 "+MainWindow::Name+"!";
    MainWindow::AlterEvent(event);
    this->close();
    ui->LE1_Name->setText("");
}
