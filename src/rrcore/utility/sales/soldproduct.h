#ifndef SOLDPRODUCT_H
#define SOLDPRODUCT_H

#include <QVariantList>
#include "saletransaction.h"
#include "utility/common/recordgroup.h"
#include "utility/stock/product.h"
#include "utility/stock/productcategory.h"
#include "utility/user/user.h"

namespace Utility {
namespace Sales {
struct SoldProduct
{
    SaleTransaction transaction;
    Stock::Product product;
    Stock::ProductQuantity quantity;
    SaleMonies monies;
    Note note;
    RecordTimestamp timestamp;
    User::User user;
    RecordGroup::Flags flags;
    int row{-1};

    explicit SoldProduct() = default;
    explicit SoldProduct(const QVariantMap& map);
    explicit SoldProduct(int saleTransactionId);

    QVariantMap toVariantMap() const;

    friend QDebug operator<<(QDebug debug, const SoldProduct& soldProduct)
    {
        debug.nospace() << "SoldProduct("
                        << ", saleTransaction=" << soldProduct.transaction
                        << ", product=" << soldProduct.product
                        << ", unitPrice=" << soldProduct.monies.unitPrice
                        << ", quantity=" << soldProduct.quantity
                        << ", cost=" << soldProduct.monies.cost
                        << ", discount=" << soldProduct.monies.discount
                        << ", note=" << soldProduct.note
                        << ", flags=" << soldProduct.flags
                        << ", row=" << soldProduct.row << ")";

        return debug.nospace();
    }
};

class SoldProductList : public QList<SoldProduct>
{
public:
    explicit SoldProductList() = default;
    SoldProductList(std::initializer_list<SoldProduct> products)
        : QList<SoldProduct>(products)
    {}
    explicit SoldProductList(const QVariantList& list) : QList<SoldProduct>()
    {
        for (const auto& variant : list)
            append(SoldProduct{variant.toMap()});
    }

    QVariantList toVariantList() const
    {
        QVariantList list;
        for (const auto& product : *this)
            list.append(product.toVariantMap());
        return list;
    }
};
}  // namespace Sales
}  // namespace Utility
Q_DECLARE_TYPEINFO(Utility::Sales::SoldProduct, Q_PRIMITIVE_TYPE);

#endif  // SOLDPRODUCT_H
