#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSqlDatabase>//用于管理和配置数据库连接
#include <QSqlQuery>//用于与数据库进行交互
#include <QSqlQueryModel>//主要用于向QTableView等视图类提供数据
#include <QListWidgetItem>//搜索项列表
#include <QTimer>//计时
#include <QTime>//获取当前时间
#include "stualter.h"
#include "stuadd.h"
#include "studelete.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //将以下成员变为静态成员是为了在其他引用mainwindow.h的程序中也可以使用它们
    //static QSqlDatabase studb1 = QSqlDatabase::addDatabase("QSQLITE");;//创建数据库并初始化对象
    static QSqlDatabase studb1;//只创建数据库
    static QSqlQuery* stuq1;//指针
    static QSqlQueryModel* stuqm1;//指针//向TV_1传输Sqlite表中的内容
    static void Alterstuqm1();//查询表中数据(刷新)
    static void Recovertableclicked();//原表被修改后,TV_1会解除被选中状态.此函数用于同步状态变量tableclicked
    static void AlterEvent(const QString &event1);//同步最新事件到ui的方法
    static MainWindow* staticthis;//静态的this指针,方便其他文件访问
    //
    static QString Name;
    static QString SN;
    static QString YW;
    static QString SX;
    static QString YY;
    //定义静态成员变量,用于同步在TV_1中选中的数据//将它们变为静态以便传入stualter1&studelete1(新窗口)中//不需要定义ZF
    static QString TWselected;//定义静态成员变量,用于同步在TW_1中选中的数据
    static int tableclicked;//判定是否选中数据的变量
    static QTimer* newtimer;//时间指针
    static QString eventtime;//事件时间文本

signals:

public slots:

private slots:
    void on_PB_Save_clicked();//保存并退出
    void on_PB_LSE_clicked();//Surprise
    void on_TV_1_clicked(const QModelIndex &index);//选中TV_1中的对象并同步信息
    void on_PB1_Add_clicked();//增加学生
    void on_PB2_Alter_clicked();//修改学生综合信息
    void on_PB3_Delete_clicked();//删除学生
    void on_LE1_Search_textChanged(const QString &arg1);//自动搜索
    void on_LW_1_itemClicked(QListWidgetItem *item);//搜索项列表
    void UpdateTime() const;

private:
    Ui::MainWindow *ui;
    //
    StuAlter* stualter1;
    StuAdd* stuadd1;
    StuDelete* studelete1;
    //窗口指针
    void SyncArg(const QModelIndex &index1) const;//同步变量的方法
    void CloseAll();//关闭所有窗口的方法

};
#endif // MAINWINDOW_H
