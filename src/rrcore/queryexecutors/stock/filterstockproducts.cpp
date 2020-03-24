#include "filterstockproducts.h"
#include "utility/commonutils.h"
#include "database/databaseexception.h"
#include <QUrl>

using namespace StockQuery;

FilterStockProducts::FilterStockProducts(const Utility::FilterCriteria &filterCriteria,
                                         const Utility::SortCriteria &sortCriteria,
                                         int productCategoryId,
                                         QObject *receiver) :
    StockExecutor(COMMAND, {
                    { "product_category_id", productCategoryId },
                    { "filter_text", filterCriteria.text },
                    { "filter_column", filterCriteria.column },
                    { "sort_order", sortCriteria.orderAsString() },
                    { "sort_column", sortCriteria.column }
                  }, receiver)
{

}

QueryResult FilterStockProducts::execute()
{
    QueryResult result{ request() };
    result.setSuccessful(true);
    const QVariantMap &params{ request().params() };

    try {
        const QList<QSqlRecord> &records(callProcedure("FilterStockProducts", {
                                                           ProcedureArgument {
                                                               ProcedureArgument::Type::In,
                                                               "filter_column",
                                                               params.value("filter_column")
                                                           },
                                                           ProcedureArgument {
                                                               ProcedureArgument::Type::In,
                                                               "filter_text",
                                                               params.value("filter_text")
                                                           },
                                                           ProcedureArgument {
                                                               ProcedureArgument::Type::In,
                                                               "sort_column",
                                                               params.value("sort_column")
                                                           },
                                                           ProcedureArgument {
                                                               ProcedureArgument::Type::In,
                                                               "sort_order",
                                                               params.value("sort_order")
                                                           },
                                                           ProcedureArgument {
                                                               ProcedureArgument::Type::In,
                                                               "product_category_id",
                                                               params.value("product_category_id")
                                                           }
                                                       }));

        QVariantList products;
        for (const auto &record : records) {
            QVariantMap product{ recordToMap(record) };
            product.insert("image_url", QueryExecutor::byteArrayToImageUrl(record.value("image").toByteArray()));
            product.remove("image");
            products.append(product);
        }

        result.setOutcome(QVariantMap {
                              { "products", products },
                              { "record_count", products.count() }
                          });
        return result;
    } catch (const DatabaseException &) {
        throw;
    }
}
