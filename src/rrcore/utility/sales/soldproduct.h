#ifndef SOLDPRODUCT_H
#define SOLDPRODUCT_H

#include "saletransaction.h"
#include "utility/stock/stockproductcategory.h"
#include "utility/stock/stockproduct.h"
#include <QVariantList>

namespace Utility {
struct SoldProduct
{
    SaleTransaction transaction;
    StockProduct product;
    qreal quantity;
    qreal unitPrice;
    qreal cost;
    qreal discount;
    Note note;
    QDateTime created;
    QDateTime lastEdited;
    User user;
    RecordGroup::Flags flags;
    int row {-1};

    explicit SoldProduct() = default;
    explicit SoldProduct(const QVariantMap &map);
    explicit SoldProduct(qint64 saleTransactionId);

    QVariantMap toVariantMap() const;

    friend QDebug operator<<(QDebug debug, const SoldProduct &soldProduct)
    {
        debug.nospace() << "SoldProduct("
                        << ", saleTransaction=" << soldProduct.transaction
                        << ", product=" << soldProduct.product
                        << ", unitPrice=" << soldProduct.unitPrice
                        << ", quantity=" << soldProduct.quantity
                        << ", cost=" << soldProduct.cost
                        << ", discount=" << soldProduct.discount
                        << ", note=" << soldProduct.note
                        << ", flags=" << soldProduct.flags
                        << ", row=" << soldProduct.row
                        << ")";

        return debug.nospace();
    }
};

class SoldProductList : public QList<SoldProduct>
{
public:
    explicit SoldProductList() = default;
    SoldProductList(std::initializer_list<SoldProduct> products) :
        QList<SoldProduct>(products) { }
    explicit SoldProductList(const QVariantList &list) :
        QList<SoldProduct>() {
        for (const auto &variant : list)
            append(SoldProduct{ variant.toMap() });
    }

    QVariantList toVariantList() const {
        QVariantList list;
        for (const auto &product : *this)
            list.append(product.toVariantMap());
        return list;
    }
};
}
Q_DECLARE_TYPEINFO(Utility::SoldProduct, Q_PRIMITIVE_TYPE);

#endif // SOLDPRODUCT_H
