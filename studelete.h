//Qt设计师界面类
#ifndef STUDELETE_H
#define STUDELETE_H

#include <QWidget>

namespace Ui {
class StuDelete;
}

class StuDelete : public QWidget
{
    Q_OBJECT

public:
    explicit StuDelete(QWidget *parent = nullptr);
    ~StuDelete();
    void SetTextForMe() const;//将选中的对象的"姓名"同步到本类的Line Edit上

public slots:

private slots:
    void on_PB1_Yes_clicked();
    void on_PB2_No_clicked();

private:
    Ui::StuDelete *ui;
    static QString event;//事件文本

};

#endif // STUDELETE_H
