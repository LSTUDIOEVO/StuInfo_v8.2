#ifndef STUADD_H
#define STUADD_H

#include <QWidget>

namespace Ui {
class StuAdd;
}

class StuAdd : public QWidget
{
    Q_OBJECT

public:
    explicit StuAdd(QWidget *parent = nullptr);
    ~StuAdd();

public slots:

private slots:
    void on_PB1_Yes_clicked();
    void on_PB2_No_clicked();
    //
    void on_LE3_YW_textChanged(const QString &arg1);
    void on_LE4_SX_textChanged(const QString &arg1);
    void on_LE5_YY_textChanged(const QString &arg1);
    //检测文本变动的方法
private:
    Ui::StuAdd *ui;
    //
    static float YW;
    static float SX;
    static float YY;
    static float ZF;
    //用于同步Line Edit中的文本的几个数据,为了便于计算"总分"项
    static QString event;//事件文本
    void ArgReset() const;//用来重置变量与Line Edit中的内容的方法
    void CalculateAndShowZF() const;//用于计算并显示总分的方法

};

#endif // STUADD_H
