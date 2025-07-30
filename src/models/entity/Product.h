#ifndef PRODUCT_H
#define PRODUCT_H

#include "models/entity/Entity.h"

class Product : Entity{
private:
    id_t productId;
    QString name;
    QString category;
    qreal price;
    qint32 stock;

public:
    Product() = default;

    // setter : constructor
    Product(id_t id, QString name, QString category, qreal price, qint32 stock)
        : productId(id), name(name), category(category), price(price), stock(stock) {}

    // getter
    id_t getId() const  override;
    QString getName() const ;
    QString getCategory() const ;
    qreal getPrice() const ;
    qint32 getStock() const ;

    // setter
    void setId(id_t id) override;
    RaErrorCode setName(QString inputName);
    RaErrorCode setPrice(qreal inputPrice);
    RaErrorCode setCategory(QString inputCategory);

    // etc
    RaErrorCode increaseStock(quint32 num);
    RaErrorCode decreaseStock(quint32 num);

    // json
    QJsonObject toJson() const override;
    RaErrorCode fromJson(const QJsonObject& json) override;

};

#endif // PRODUCT_H
