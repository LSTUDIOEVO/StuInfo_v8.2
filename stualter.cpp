#include "stualter.h"
#include "ui_stualter.h"
#include "mainwindow.h"
#include <QDebug>

StuAlter::StuAlter(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StuAlter)
{
    ui->setupUi(this);
}

StuAlter::~StuAlter()
{
    delete ui;
}
//
float StuAlter::YW = 0;
float StuAlter::SX = 0;
float StuAlter::YY = 0;
float StuAlter::ZF = 0;
QString StuAlter::event = "Default";
//初始化静态变量
void StuAlter::ArgReset() const
{
    ui->LE1_Name->setText("");
    ui->LE2_SN->setText("");
    ui->LE3_YW->setText("");
    ui->LE4_SX->setText("");
    ui->LE5_YY->setText("");
    ui->L7_ShowZF->setText("自动计算");
    YW = 0;
    SX = 0;
    YY = 0;
    ZF = 0;
    event = "Default";
}//用来重置变量与Line Edit中的内容的方法

void StuAlter::CalculateAndShowZF() const
{
    ZF = YW + SX + YY;
    ui->L7_ShowZF->setText(QString::number(ZF,'f',1));
}

void StuAlter::SetTextForMe() const
{
    //
    ui->LE1_Name->setText(MainWindow::Name);
    //qDebug() << MainWindow::Name;
    ui->LE2_SN->setText(MainWindow::SN);
    ui->LE3_YW->setText(MainWindow::YW);
    ui->LE4_SX->setText(MainWindow::SX);
    ui->LE5_YY->setText(MainWindow::YY);
    //setText方法,设置Line Edit的显示文本
}

void StuAlter::UpdateTable() const
{
    MainWindow::stuq1->exec("UPDATE stuinfo SET 姓名 = '"+ui->LE1_Name->text()+"' WHERE SN = '"+MainWindow::SN+"'");
    MainWindow::stuq1->exec("UPDATE stuinfo SET SN = '"+ui->LE2_SN->text()+"' WHERE SN = '"+MainWindow::SN+"'");
    MainWindow::stuq1->exec("UPDATE stuinfo SET 语文 = '"+ui->LE3_YW->text()+"' WHERE SN = '"+ui->LE2_SN->text()+"'");
    //qDebug() << ui->LE3_YW->text();
    MainWindow::stuq1->exec("UPDATE stuinfo SET 数学 = '"+ui->LE4_SX->text()+"' WHERE SN = '"+ui->LE2_SN->text()+"'");
    MainWindow::stuq1->exec("UPDATE stuinfo SET 英语 = '"+ui->LE5_YY->text()+"' WHERE SN = '"+ui->LE2_SN->text()+"'");
    MainWindow::stuq1->exec("UPDATE stuinfo SET 总分 = '"+QString::number(ZF,'f',1)+"' WHERE SN = '"+ui->LE2_SN->text()+"'");
}//"姓名"和"SN"通过修改前的"SN"的值定位;"YW","SX"和"YY"通过修改后的"SN"的值定位//因为只有SN的值是唯一的

void StuAlter::on_PB1_Yes_clicked()
{
    if(ui->LE1_Name->text() == ""||ui->LE2_SN->text() == ""
        ||ui->LE3_YW->text() == ""||ui->LE4_SX->text() == ""
        ||ui->LE5_YY->text() == "")
    {
        //任意一个为空就不修改原项,并重置Line Edit和所有分数变量
        event = "修改学生 "+MainWindow::Name+" 失败!";
    }else{
        UpdateTable();
        event = "修改学生 "+MainWindow::Name+" 成功!";
        //qDebug() << MainWindow::Name;
        MainWindow::Alterstuqm1();
        MainWindow::Recovertableclicked();
    }
    MainWindow::AlterEvent(event);
    ArgReset();
    this->close();
}

void StuAlter::on_PB2_No_clicked()
{
    event = "已取消修改学生 "+MainWindow::Name+"!";
    MainWindow::AlterEvent(event);
    ArgReset();
    this->close();
}

void StuAlter::on_LE3_YW_textChanged(const QString &arg1)
{
    YW = arg1.toFloat();//调用QString类的toFloat()方法,将QString类型转为float类型
    CalculateAndShowZF();
}

void StuAlter::on_LE4_SX_textChanged(const QString &arg1)
{
    SX = arg1.toFloat();
    CalculateAndShowZF();
}

void StuAlter::on_LE5_YY_textChanged(const QString &arg1)
{
    YY = arg1.toFloat();
    qDebug() << YW << SX << YY;
    CalculateAndShowZF();
}
