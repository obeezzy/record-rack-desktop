#ifndef PURCHASEREPORTTRANSACTION_H
#define PURCHASEREPORTTRANSACTION_H

#include <QVariantList>
#include "utility/stock/product.h"
#include "utility/stock/productcategory.h"

namespace Utility {
namespace Purchase {
struct PurchaseReportTransaction
{
    Stock::ProductCategory category;
    Stock::Product product;
    Stock::ProductQuantity quantityBought;
    Money totalExpenditure;

    explicit PurchaseReportTransaction() = default;
    explicit PurchaseReportTransaction(const QVariantMap& map);

    QVariantMap toVariantMap() const;
};

class PurchaseReportTransactionList : public QList<PurchaseReportTransaction>
{
public:
    explicit PurchaseReportTransactionList() = default;
    PurchaseReportTransactionList(
        std::initializer_list<PurchaseReportTransaction> transactions)
        : QList<PurchaseReportTransaction>(transactions)
    {}
    explicit PurchaseReportTransactionList(const QVariantList& list)
        : QList<PurchaseReportTransaction>()
    {
        for (const auto& variant : list)
            append(PurchaseReportTransaction{variant.toMap()});
    }

    QVariantList toVariantList() const
    {
        QVariantList list;
        for (const auto& transaction : *this)
            list.append(transaction.toVariantMap());
        return list;
    }
};
}  // namespace Purchase
}  // namespace Utility
Q_DECLARE_TYPEINFO(Utility::Purchase::PurchaseReportTransaction,
                   Q_PRIMITIVE_TYPE);

#endif  // PURCHASEREPORTTRANSACTION_H
