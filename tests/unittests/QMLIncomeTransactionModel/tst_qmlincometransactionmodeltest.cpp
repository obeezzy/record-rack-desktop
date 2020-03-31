#include "mockdatabasethread.h"
#include "qmlapi/qmlincometransactionmodel.h"
#include <QtTest>
#include <QCoreApplication>

class QMLIncomeTransactionModelTest : public QObject
{
    Q_OBJECT
public:
    QMLIncomeTransactionModelTest() = default;
private slots:
    void init();
    void cleanup();

    void testViewIncomeTransactions();
    void testError();
private:
    QMLIncomeTransactionModel *m_incomeTransactionModel;
    MockDatabaseThread *m_thread;
    QueryResult m_result;
};

void QMLIncomeTransactionModelTest::init()
{
    m_thread = new MockDatabaseThread(&m_result, this);
    m_incomeTransactionModel = new QMLIncomeTransactionModel(*m_thread, this);
}

void QMLIncomeTransactionModelTest::cleanup()
{
    m_incomeTransactionModel->deleteLater();
    m_thread->deleteLater();
}

void QMLIncomeTransactionModelTest::testViewIncomeTransactions()
{
    const QVariantList transactions {
        QVariantMap {
            { "client_id", 1 },
            { "preferred_name", QStringLiteral("Ama Mosieri") },
            { "purpose", QStringLiteral("Dodger tickets") },
            { "amount", 420.00 },
            { "payment_method", "cash" }
        },
        QVariantMap {
            { "client_id", 2 },
            { "preferred_name", QStringLiteral("Bob Martin") },
            { "purpose", QStringLiteral("Clean code and TDD!") },
            { "amount", 420.00 },
            { "payment_method", "cash" }
        }
    };

    auto databaseWillReturn = [this](const QVariantList &transactions) {
        m_result.setSuccessful(true);
        m_result.setOutcome(QVariantMap { { "transactions", transactions } });
    };
    QSignalSpy successSpy(m_incomeTransactionModel, &QMLIncomeTransactionModel::success);
    QSignalSpy errorSpy(m_incomeTransactionModel, &QMLIncomeTransactionModel::error);
    QSignalSpy busyChangedSpy(m_incomeTransactionModel, &QMLIncomeTransactionModel::busyChanged);

    QCOMPARE(m_incomeTransactionModel->rowCount(), 0);

    databaseWillReturn(transactions);

    m_incomeTransactionModel->componentComplete();
    QCOMPARE(successSpy.count(), 1);
    QCOMPARE(errorSpy.count(), 0);
    QCOMPARE(busyChangedSpy.count(), 2);

    QCOMPARE(m_incomeTransactionModel->rowCount(), 2);
    QCOMPARE(m_incomeTransactionModel->data(m_incomeTransactionModel->index(0, QMLIncomeTransactionModel::TransactionIdColumn),
                                             QMLIncomeTransactionModel::TransactionIdRole).toInt(),
             transactions[0].toMap()["income_transaction_id"].toInt());
    QCOMPARE(m_incomeTransactionModel->data(m_incomeTransactionModel->index(0, 0),
                                             QMLIncomeTransactionModel::ClientIdRole).toInt(),
             transactions[0].toMap()["client_id"].toInt());
    QCOMPARE(m_incomeTransactionModel->data(m_incomeTransactionModel->index(0, QMLIncomeTransactionModel::ClientNameColumn),
                                             QMLIncomeTransactionModel::ClientNameRole).toInt(),
             transactions[0].toMap()["preferred_name"].toInt());
    QCOMPARE(m_incomeTransactionModel->data(m_incomeTransactionModel->index(0, QMLIncomeTransactionModel::AmountColumn),
                                             QMLIncomeTransactionModel::AmountRole).toInt(),
             transactions[0].toMap()["amount"].toInt());
}

void QMLIncomeTransactionModelTest::testError()
{
    auto databaseWillReturnError = [this]() {
        m_result.setSuccessful(false);
    };
    QSignalSpy successSpy(m_incomeTransactionModel, &QMLIncomeTransactionModel::success);
    QSignalSpy errorSpy(m_incomeTransactionModel, &QMLIncomeTransactionModel::error);
    QSignalSpy busyChangedSpy(m_incomeTransactionModel, &QMLIncomeTransactionModel::busyChanged);

    QCOMPARE(m_incomeTransactionModel->rowCount(), 0);

    databaseWillReturnError();

    m_incomeTransactionModel->componentComplete();
    QCOMPARE(m_incomeTransactionModel->rowCount(), 0);
    QCOMPARE(successSpy.count(), 0);
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(busyChangedSpy.count(), 2);
}

QTEST_MAIN(QMLIncomeTransactionModelTest)

#include "tst_qmlincometransactionmodeltest.moc"