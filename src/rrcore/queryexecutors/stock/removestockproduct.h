#ifndef REMOVESTOCKPRODUCT_H
#define REMOVESTOCKPRODUCT_H

#include "stockexecutor.h"
#include "utility/stockutils.h"

namespace StockQuery {
class RemoveStockProduct : public StockExecutor
{
    Q_OBJECT
public:
    static inline const QString COMMAND = QStringLiteral("remove_stock_product");
    static inline const QString UNDO_COMMAND = QStringLiteral("undo_remove_stock_product");

    explicit RemoveStockProduct(int productId,
                                QObject *receiver);
    explicit RemoveStockProduct(int productRow,
                                const StockProduct &product,
                                QObject *receiver);
    QueryResult execute() override;
private:
    QueryResult removeStockProduct();
    QueryResult undoRemoveStockProduct();
};
}

#endif // REMOVESTOCKPRODUCT_H