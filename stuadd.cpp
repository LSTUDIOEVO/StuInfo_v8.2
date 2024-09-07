#include "stuadd.h"
#include "ui_stuadd.h"
#include "mainwindow.h"
#include <QDebug>

StuAdd::StuAdd(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StuAdd)
{
    ui->setupUi(this);
}

StuAdd::~StuAdd()
{
    delete ui;
}
//
float StuAdd::YW = 0;
float StuAdd::SX = 0;
float StuAdd::YY = 0;
float StuAdd::ZF = 0;
QString StuAdd::event = "Default";
//初始化静态变量
void StuAdd::ArgReset() const
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

void StuAdd::CalculateAndShowZF() const
{
    ZF = YW + SX + YY;
    ui->L7_ShowZF->setText(QString::number(ZF,'f',1));
}

void StuAdd::on_PB1_Yes_clicked()
{
    if(ui->LE1_Name->text() == ""||ui->LE2_SN->text() == ""
        ||ui->LE3_YW->text() == ""||ui->LE4_SX->text() == ""
        ||ui->LE5_YY->text() == "")
    {
        //任意一个为空就不创建新项,并重置Line Edit和所有分数变量
        event = "增加学生失败!";
    }else{
        //
        MainWindow::stuq1->exec("INSERT INTO stuinfo(姓名,SN,语文,数学,英语,总分) "
                                "VALUES('"+ui->LE1_Name->text()+"','"+ui->LE2_SN->text()+"',"
                                "'"+ui->LE3_YW->text()+"','"+ui->LE4_SX->text()+"',"
                                "'"+ui->LE5_YY->text()+"','"+QString::number(ZF,'f',1)+"')");
        //插入数据//此处的ui指针指向stuadd//text()方法->取出Line Edit中的数据
        event = "增加学生 "+ui->LE1_Name->text()+" 成功!";
        qDebug() << event;
        MainWindow::Alterstuqm1();
        //
        MainWindow::Recovertableclicked();
        //点击"PB1_Yes"之后会查询表中内容,导致失去选中状态,此时要同步tableclicked变量
    }
    MainWindow::AlterEvent(event);
    ArgReset();
    this->close();
}

void StuAdd::on_PB2_No_clicked()
{
    event = "已取消增加学生!";
    MainWindow::AlterEvent(event);
    ArgReset();
    this->close();
}
//按下"修改键"后执行的SetTextForMe方法已经更改了Line Edit中的内容,所以以下这三个方法会执行,不用额外同步YW,SX,YY和ZF
void StuAdd::on_LE3_YW_textChanged(const QString &arg1)
{
    YW = arg1.toFloat();//调用QString类的toFloat()方法,将QString类型转为float类型
    qDebug() << YW;
    CalculateAndShowZF();
}

void StuAdd::on_LE4_SX_textChanged(const QString &arg1)
{
    SX = arg1.toFloat();
    CalculateAndShowZF();
}

void StuAdd::on_LE5_YY_textChanged(const QString &arg1)
{
    YY = arg1.toFloat();
    CalculateAndShowZF();
}
