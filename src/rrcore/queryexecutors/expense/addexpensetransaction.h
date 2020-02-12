#ifndef ADDEXPENSETRANSACTION_H
#define ADDEXPENSETRANSACTION_H

#include "expenseexecutor.h"

class Client;
namespace Utility {
    enum class PaymentMethod;
}

namespace ExpenseQuery {
class AddExpenseTransaction : public ExpenseExecutor
{
    Q_OBJECT
public:
    static inline const QString COMMAND = QStringLiteral("add_expense_transaction");

    explicit AddExpenseTransaction(const Client &client,
                                   const QString &purpose,
                                   qreal amount,
                                   const Utility::PaymentMethod &paymentMethod,
                                   QObject *receiver);
    QueryResult execute() override;
};
}

#endif // ADDEXPENSETRANSACTION_H
