#include "debtpayment.h"

int DebtPayment::temporaryId = 1;

DebtPayment::DebtPayment(qreal totalAmount,
                         qreal amountPaid,
                         const QDateTime &dueDateTime,
                         const Note &note) :
    id(temporaryId++),
    totalAmount(totalAmount),
    amountPaid(amountPaid),
    balance(totalAmount - amountPaid),
    currency(Settings::DEFAULT_CURRENCY),
    dueDateTime(dueDateTime),
    note(note),
    archived(false),
    created(QDateTime::currentDateTime()),
    lastEdited(QDateTime::currentDateTime()),
    state(State::Fresh)
{ }

DebtPayment::DebtPayment(int id,
                         qreal totalAmount,
                         qreal amountPaid,
                         qreal balance,
                         const QString &currency,
                         const QDateTime &dueDateTime,
                         const Note &note,
                         bool archived,
                         const QDateTime &created,
                         const QDateTime &lastEdited,
                         State state) :
    id(id),
    totalAmount(totalAmount),
    amountPaid(amountPaid),
    balance(balance),
    currency(currency),
    dueDateTime(dueDateTime),
    note(note),
    archived(archived),
    created(created),
    lastEdited(lastEdited),
    state(state)
{ }

DebtPayment::DebtPayment(const QVariantMap &map) :
    id(map.value("debt_payment_id").toInt()),
    totalAmount(map.value("total_amount").toDouble()),
    amountPaid(map.value("amount_paid").toDouble()),
    balance(map.value("balance").toDouble()),
    currency(map.value("currency").toString()),
    dueDateTime(map.value("due_date").toDateTime()),
    note(Note {
         map.value("note_id").toInt(),
         map.value("note").toString()
         }),
    archived(map.value("archived").toBool()),
    created(map.value("created").toDateTime()),
    lastEdited(map.value("last_edited").toDateTime()),
    state(State::Clean)
{ }

QVariantMap DebtPayment::toVariantMap() const {
    return {
        { "debt_transaction_id", debtTransactionId },
        { "debt_payment_id", id },
        { "total_amount", totalAmount },
        { "amount_paid", amountPaid },
        { "balance", balance },
        { "currency", currency },
        { "due_date", dueDateTime },
        { "note_id", note.id },
        { "note", note.note },
        { "archived", archived },
        { "created", created },
        { "last_edited", lastEdited }
    };
}

