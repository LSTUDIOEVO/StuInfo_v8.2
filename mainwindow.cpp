#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
/*
设置数据库名 QSqlDatabase数据库.setDatabaseName("我是数据库.db");
创建表 QSqlQuery指针->exec("CREATE TABLE 表(a,b)");
向表中插入数据 QSqlQuery指针->exec("INSERT INTO 表(a,b) VALUES('x','y')");
查询表中数据(刷新) QSqlQueryModel指针->setQuery("SELECT * FROM 表");
修改表中数据 QSqlQuery指针->exec("UPDATE 表 SET a = 'xx' WHERE a = 'x'"或"UPDATE 表 SET a = '"+变量+"' WHERE a = 'x'")
搜索表中数据 QSqlQueryModel指针->setQuery("SELECT * FROM 表 WHERE a LIKE '%xx%'"或"SELECT * FROM 表 WHERE a LIKE '%"+变量+"%'");//模糊搜索语句
删除表中数据 QSqlQuery指针->exec("DELETE FROM 表 WHERE a = 'x'");
*/
/*
在两个双引号("")之间写的
"+变量+" 在执行时是 变量
'"+变量+"' 在执行时是 '变量'
可以解释stuqm1->setQuery("SELECT * FROM stuinfo WHERE "+TWselected+" LIKE '%"+arg1+"%'");这行代码
*/
//#define THISSSS(x) ui->LB_Intro->setStyleSheet("color:"+QString(x));ui->PB_Save->setStyleSheet("color:"+QString(x))//宏定义//Surprise
#define TV1SSS(x) ui->TV_1->setStyleSheet("color:"+QString(x))//宏定义//Surprise
QSqlDatabase MainWindow::studb1;//QSqlDatabase类成员初始化
//
QSqlQuery* MainWindow::stuq1;
QSqlQueryModel* MainWindow::stuqm1;
//静态QCoreApplication类成员初始化
//
QString MainWindow::Name = "Default";
QString MainWindow::SN = "Default";
QString MainWindow::YW = "Default";
QString MainWindow::SX = "Default";
QString MainWindow::YY = "Default";
QString MainWindow::TWselected = "姓名";//默认为"姓名"
//静态QString类成员初始化
int MainWindow::tableclicked = 0;//初始化判定是否选中数据的变量
QTimer* MainWindow::newtimer = new QTimer();//初始化时间指针
MainWindow* MainWindow::staticthis = nullptr;//初始化staticthis指针
QString MainWindow::eventtime = "00:00:00";//初始化事件时间文本

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);//this指针指向当前MainWindow类的实例(即main.cpp中的w)
    //
    staticthis = this;
    /*
    将this指针赋值给创造出来的staticthis指针
    它们都指向实例化的w
    这样就能在mainwindow.cpp的外部通过staticthis指针访问this->ui中的对象
    帅!指针新语法!
    */
    studb1 = QSqlDatabase::addDatabase("QSQLITE");//初始化对象
    studb1.setDatabaseName("studb1.db");//设置数据库名
    studb1.open();//打开数据库
    stuq1 = new QSqlQuery();//调用QSqlQuery构造函数,自动连接studb1数据库
    stuq1->exec("CREATE TABLE stuinfo(姓名,SN,语文,数学,英语,总分)");//创建stuinfo表
    stuqm1 = new QSqlQueryModel();//调用QSqlQueryModel构造函数,自动连接studb1数据库
    Alterstuqm1();//执行查询语句
    ui->TV_1->setModel(stuqm1);//调用setModel函数将Sqlite表中的数据传入TV_1
    //
    stuadd1 = new StuAdd();
    stualter1 = new StuAlter();
    studelete1 = new StuDelete();
    //初始化窗口指针
    newtimer->start(10);//每隔10ms(0.01s)发送一次timeout()的SIGNAL
    //
    connect(newtimer,SIGNAL(timeout()),this,SLOT(UpdateTime()));
    //每接收一次timeout()的SIGNAL(每10ms)就读取一次系统时间(HH:mm:ss)并显示,保证时间的准确性
    //
    ui->L2_EventTime->setText(QTime::currentTime().toString("HH:mm:ss"));
    //将最开始的事件时间设置为构造函数执行的系统时间
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CloseAll()
{
    stuadd1->close();
    studelete1->close();
    stualter1->close();
    this->close();//当中写了this->close();的方法不能标为常量方法//主窗口关闭后,Qt会直接让程序退出
}

void MainWindow::Alterstuqm1()
{
    stuqm1->setQuery("SELECT * FROM stuinfo");
}

void MainWindow::Recovertableclicked()
{
    tableclicked = 0;
}

void MainWindow::AlterEvent(const QString &event1)
{
    MainWindow::staticthis->ui->L3_Event->setText(event1);//显示事件为传进来的参数event1
    eventtime = staticthis->ui->L5_CurrentTime->text();//定义事件时间为执行AlterEvent函数的时间(即产生事件的时间)
    qDebug() << eventtime;
    MainWindow::staticthis->ui->L2_EventTime->setText(eventtime);//显示事件时间
    eventtime = "00:00:00";//重置事件时间文本
    qDebug() << eventtime;
}//通过等效于this指针但是是静态指针的staticthis指针同步最新事件到ui的L2_Event对象上

void MainWindow::on_PB_Save_clicked()
{
    CloseAll();//只执行this->close();会导致其他窗口不关闭
}

unsigned short count1 = 0;//记录PB_LSE按下的次数//Surprise

void MainWindow::on_PB_LSE_clicked()//Surprise
{
    count1++;
    switch(count1 % 7)
    {
        case 1:TV1SSS("#ff6633");break;
        case 2:TV1SSS("#ff3366");break;
        case 3:TV1SSS("#33ff66");break;
        case 4:TV1SSS("#6633ff");break;
        case 5:TV1SSS("#ffff00");break;
        case 6:TV1SSS("#0000ff");break;
        //default:TV1SSS("#1e1e1e");//Windows深色模式默认背景颜色
        default:TV1SSS("#ffffff");
    }
}

void MainWindow::SyncArg(const QModelIndex &index) const
{
    Name = index.siblingAtColumn(0).data().toString();
    //qDebug() << Name;
    SN = index.siblingAtColumn(1).data().toString();
    YW = index.siblingAtColumn(2).data().toString();
    SX = index.siblingAtColumn(3).data().toString();
    YY = index.siblingAtColumn(4).data().toString();
    //index.siblingAtColumn(n).data().toString()代表TV_1的被选中对象的第(n+1)列的数据转为QString类型的结果
}

void MainWindow::on_TV_1_clicked(const QModelIndex &index)
{
    tableclicked = 1;//将tableclicked的值修改为1,表示"已选中"
    SyncArg(index);//将TV_1的被选中对象的数据同步到几个静态变量中
}

void MainWindow::on_PB1_Add_clicked()
{
    stuadd1->show();
}

void MainWindow::on_PB2_Alter_clicked()
{
    if(tableclicked) stualter1->show();//如果已选中就显示
    stualter1->SetTextForMe();
}

void MainWindow::on_PB3_Delete_clicked()
{
    if(tableclicked) studelete1->show();//如果已选中就显示
    studelete1->SetTextForMe();
}

void MainWindow::on_LE1_Search_textChanged(const QString &arg1)//arg1就是实时版的ui->LE1_Search->text()//若有更改则自动搜索
{
    //
    stuqm1->setQuery("SELECT * FROM stuinfo WHERE "+TWselected+" LIKE '%"+arg1+"%'");
    //模糊搜索语句//从类型为TWselected的所有项中查询包含"arg1"的项
}

void MainWindow::on_LW_1_itemClicked(QListWidgetItem *item)
{
    TWselected = item->text();//将TWselected变量同步为被选中项的文本内容
    ui->LE1_Search->setText("");//改变搜索项时自动清空搜索栏
    //qDebug() << TWselected;
}

void MainWindow::UpdateTime() const
{
    ui->L5_CurrentTime->setText(QTime::currentTime().toString("HH:mm:ss"));
}//更新文本为当前读取的时间//"(24小时制的)时:分:秒"
