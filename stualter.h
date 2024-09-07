#ifndef STUALTER_H
#define STUALTER_H

#include <QWidget>

namespace Ui {
class StuAlter;
}

class StuAlter : public QWidget
{
    Q_OBJECT

public:
    explicit StuAlter(QWidget *parent = nullptr);
    ~StuAlter();
    void SetTextForMe() const;//将MainWindow中的6个静态变量同步到本类的6个Line Edit上

public slots:

private slots:
    void on_PB1_Yes_clicked();
    void on_PB2_No_clicked();

    void on_LE3_YW_textChanged(const QString &arg1);

    void on_LE4_SX_textChanged(const QString &arg1);

    void on_LE5_YY_textChanged(const QString &arg1);

private:
    Ui::StuAlter *ui;
    //
    static float YW;
    static float SX;
    static float YY;
    static float ZF;
    //用于同步Line Edit中的文本的几个数据,为了便于计算"总分"项
    static QString event;//事件文本
    void ArgReset() const;//用来重置变量与Line Edit中的内容的方法
    void CalculateAndShowZF() const;//用于计算并显示总分的方法
    void UpdateTable() const;//用于更新查询SQLite表的方法

};

#endif // STUALTER_H
