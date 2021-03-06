#ifndef STOCKMONIES_H
#define STOCKMONIES_H

#include "utility/common/money.h"

namespace Utility {
namespace Stock {
struct StockMonies
{
    Money costPrice;
    Money retailPrice;
    Money unitPrice;

    explicit StockMonies();
    explicit StockMonies(const QVariantMap& map);
};
}  // namespace Stock
}  // namespace Utility

#endif  // STOCKMONIES_H
