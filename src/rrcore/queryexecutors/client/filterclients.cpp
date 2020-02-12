#include "filterclients.h"
#include "database/databaseexception.h"
#include "utility/commonutils.h"

using namespace ClientQuery;

FilterClients::FilterClients(const FilterCriteria &filterCriteria,
                             const RecordGroup::Flags &flags,
                             QObject *receiver) :
    ClientExecutor(COMMAND, {
                    { "filter_text", filterCriteria.text },
                    { "filter_column", filterCriteria.column },
                    { "archived", flags.testFlag(RecordGroup::Archived) }
                   }, receiver)
{

}

QueryResult FilterClients::execute()
{
    QueryResult result{ request() };
    result.setSuccessful(true);
    const QVariantMap &params = request().params();

    try {
        const auto &records(callProcedure("FilterClients", {
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
                                                  "archived",
                                                  params.value("archived")
                                              }
                                          }));


        QVariantList clients;
        for (const auto &record : records)
            clients.append(recordToMap(record));

        result.setOutcome(QVariantMap {
                              { "clients", clients },
                              { "record_count", clients.count() }
                          });
        return result;
    } catch (DatabaseException &) {
        throw;
    }
}
