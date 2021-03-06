#include <QCoreApplication>
#include <QtTest>
#include "mockdatabasethread.h"
#include "qmlapi/expense/qmlexpensetransactionmodel.h"

class QMLExpenseTransactionModelTest : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();

    void testViewExpenseTransactions();
    void testError();

private:
    QMLExpenseTransactionModel* m_expenseTransactionModel;
    MockDatabaseThread* m_thread;
};

void QMLExpenseTransactionModelTest::init()
{
    m_thread = new MockDatabaseThread(this);
    m_expenseTransactionModel = new QMLExpenseTransactionModel(*m_thread, this);
}

void QMLExpenseTransactionModelTest::cleanup()
{
    m_expenseTransactionModel->deleteLater();
    m_thread->deleteLater();
}

void QMLExpenseTransactionModelTest::testViewExpenseTransactions()
{
    const QVariantList transactions{
        QVariantMap{{"client_id", 1},
                    {"preferred_name", QStringLiteral("Ama Mosieri")},
                    {"purpose", QStringLiteral("Dodger tickets")},
                    {"amount", 420.0},
                    {"payment_method", "cash"}},
        QVariantMap{{"clhttps://jimmyc.wistia.com/medias/3nguha2yf1ient_id", 2},
                    {"preferred_name", QStringLiteral("Bob Martin")},
                    {"purpose", QStringLiteral("Clean code and TDD!")},
                    {"amount", 420.0},
                    {"payment_method", "cash"}}};

    auto databaseWillReturn = [this](const QVariantList& transactions) {
        m_thread->result().setSuccessful(true);
        m_thread->result().setOutcome(
            QVariantMap{{"transactions", transactions}});
    };
    QSignalSpy successSpy(m_expenseTransactionModel,
                          &QMLExpenseTransactionModel::success);
    QSignalSpy errorSpy(m_expenseTransactionModel,
                        &QMLExpenseTransactionModel::error);
    QSignalSpy busyChangedSpy(m_expenseTransactionModel,
                              &QMLExpenseTransactionModel::busyChanged);

    QCOMPARE(m_expenseTransactionModel->rowCount(), 0);

    databaseWillReturn(transactions);

    m_expenseTransactionModel->componentComplete();
    QCOMPARE(successSpy.count(), 1);
    QCOMPARE(errorSpy.count(), 0);
    QCOMPARE(busyChangedSpy.count(), 2);

    QCOMPARE(m_expenseTransactionModel->rowCount(), 2);
    QCOMPARE(m_expenseTransactionModel
                 ->data(m_expenseTransactionModel->index(
                            0, QMLExpenseTransactionModel::TransactionIdColumn),
                        QMLExpenseTransactionModel::TransactionIdRole)
                 .toInt(),
             transactions[0].toMap()["expense_transaction_id"].toInt());
    QCOMPARE(m_expenseTransactionModel
                 ->data(m_expenseTransactionModel->index(0, 0),
                        QMLExpenseTransactionModel::ClientIdRole)
                 .toInt(),
             transactions[0].toMap()["client_id"].toInt());
    QCOMPARE(m_expenseTransactionModel
                 ->data(m_expenseTransactionModel->index(
                            0, QMLExpenseTransactionModel::ClientNameColumn),
                        QMLExpenseTransactionModel::ClientNameRole)
                 .toInt(),
             transactions[0].toMap()["preferred_name"].toInt());
    QCOMPARE(m_expenseTransactionModel
                 ->data(m_expenseTransactionModel->index(
                            0, QMLExpenseTransactionModel::AmountColumn),
                        QMLExpenseTransactionModel::AmountRole)
                 .toInt(),
             transactions[0].toMap()["amount"].toInt());
}

void QMLExpenseTransactionModelTest::testError()
{
    auto databaseWillReturnError = [this]() {
        m_thread->result().setSuccessful(false);
    };
    QSignalSpy successSpy(m_expenseTransactionModel,
                          &QMLExpenseTransactionModel::success);
    QSignalSpy errorSpy(m_expenseTransactionModel,
                        &QMLExpenseTransactionModel::error);
    QSignalSpy busyChangedSpy(m_expenseTransactionModel,
                              &QMLExpenseTransactionModel::busyChanged);

    QCOMPARE(m_expenseTransactionModel->rowCount(), 0);

    databaseWillReturnError();

    m_expenseTransactionModel->componentComplete();
    QCOMPARE(m_expenseTransactionModel->rowCount(), 0);
    QCOMPARE(successSpy.count(), 0);
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(busyChangedSpy.count(), 2);
}

QTEST_GUILESS_MAIN(QMLExpenseTransactionModelTest)

#include "tst_qmlexpensetransactionmodeltest.moc"
