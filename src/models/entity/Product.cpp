#include "Product.h"


// getter
id_t Product::getId() const {
    return productId;
}

QString Product::getName() const {
    return name;
}

QString Product::getCategory() const {
    return category;
}

qreal Product::getPrice() const {
    return price;
}

qint32 Product::getStock() const {
    return stock;
}

// setter
void Product::setId(id_t id){
    productId = id;
}

RaErrorCode Product::setName(QString inputName){
    name = inputName;
    return Ra_Success;
}

RaErrorCode Product::setPrice(qreal inputPrice){
    price = inputPrice;
    return Ra_Success;
}

RaErrorCode Product::setCategory(QString inputCategory){
    category = inputCategory;
    return Ra_Success;
}

// etc
RaErrorCode Product::increaseStock(quint32 num){
    stock+=num;
    return Ra_Success;
}

RaErrorCode Product::decreaseStock(quint32 num){
    if((stock-num)<0){
        return Ra_Domain_Unkown_Error;
    }
    stock-=num;
    return Ra_Success;
}



QJsonObject Product::toJson() const {
    QJsonObject jsonObject;
    jsonObject.insert("productId",productId);
    jsonObject.insert("name",name);
    jsonObject.insert("category",category);
    jsonObject.insert("price",price);
    jsonObject.insert("stock",stock);

    return jsonObject;
}

RaErrorCode Product::fromJson(const QJsonObject& inputJson){
    productId = inputJson.value("productId").toInteger();
    name = inputJson.value("name").toString();
    category = inputJson.value("category").toString();
    price = inputJson.value("price").toDouble();
    stock = inputJson.value("stock").toInt();

    return Ra_Success;
}
