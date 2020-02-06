#include "viewsaletransactionproducts.h"
#include "database/databaseexception.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

using namespace SaleQuery;

ViewSoldProducts::ViewSoldProducts(qint64 transactionId,
                                   QObject *receiver) :
    SaleExecutor(COMMAND, {
                    { "transaction_id", transactionId },
                    { "suspended", false },
                    { "archived", false }
                 }, receiver)
{

}

QueryResult ViewSoldProducts::execute()
{
    QueryResult result{ request() };
    result.setSuccessful(true);
    QSqlDatabase connection = QSqlDatabase::database(connectionName());
    const QVariantMap &params = request().params();
    QSqlQuery q(connection);

    try {
        QueryExecutor::enforceArguments({ "transaction_id" }, params);

        const QList<QSqlRecord> records(callProcedure("ViewSoldProducts", {
                                                          ProcedureArgument {
                                                              ProcedureArgument::Type::In,
                                                              "transaction_id",
                                                              params.value("transaction_id")
                                                          },
                                                          ProcedureArgument {
                                                              ProcedureArgument::Type::In,
                                                              "suspended",
                                                              params.value("suspended")
                                                          },
                                                          ProcedureArgument {
                                                              ProcedureArgument::Type::In,
                                                              "archived",
                                                              params.value("archived")
                                                          }
                                                      }));

        QVariantList products;
        for (const QSqlRecord &record : records) {
            products.append(recordToMap(record));
        }

        result.setOutcome(QVariantMap {
                              { "products", products },
                              { "record_count", products.count() }
                          });
        return result;
    } catch (DatabaseException &) {
        throw;
    }
}