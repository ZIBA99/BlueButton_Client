#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <QObject>

class ProductManager : public QObject
{
    Q_OBJECT
public:
    explicit ProductManager(QObject *parent = nullptr);

signals:
};

#endif // PRODUCTMANAGER_H
