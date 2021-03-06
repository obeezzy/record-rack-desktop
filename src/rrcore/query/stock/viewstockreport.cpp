#include "viewstockreport.h"
#include "database/databaseexception.h"
#include "utility/common/datetimespan.h"

using namespace Query::Stock;

ViewStockReport::ViewStockReport(const Utility::DateTimeSpan& dateTimeSpan,
                                 QObject* receiver)
    : StockExecutor(COMMAND,
                    {{"from", dateTimeSpan.from}, {"to", dateTimeSpan.to}},
                    receiver)
{}

QueryResult ViewStockReport::execute()
{
    QueryResult result{request()};
    result.setSuccessful(true);
    const QVariantMap& params = request().params();

    try {
        const auto& records(callProcedure(
            "ViewStockReport", {ProcedureArgument{ProcedureArgument::Type::In,
                                                  "from", params.value("from")},
                                ProcedureArgument{ProcedureArgument::Type::In,
                                                  "to", params.value("to")}}));

        QVariantList products;
        for (const auto& record : records)
            products.append(recordToMap(record));

        result.setOutcome(QVariantMap{
            {"products", products},
            {"record_count", products.count()},
        });
        return result;
    } catch (const DatabaseException&) {
        throw;
    }
}
