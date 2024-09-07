#ifndef STUSQLITE_H
#define STUSQLITE_H

#include <QObject>

class StuSQLite : public QObject
{
    Q_OBJECT
public:
    explicit StuSQLite(QObject *parent = nullptr);

signals:
};

#endif // STUSQLITE_H
