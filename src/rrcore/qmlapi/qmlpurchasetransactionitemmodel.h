#ifndef QMLPURCHASETRANSACTIONITEMMODEL_H
#define QMLPURCHASETRANSACTIONITEMMODEL_H

#include "models/abstracttransactionitemmodel.h"
#include "utility/purchase/purchasedproduct.h"

class QMLPurchaseTransactionItemModel : public AbstractTransactionItemModel
{
    Q_OBJECT
public:
    enum SuccessCode {
        UnknownSuccess,
        ViewPurchaseTransactionItemsSuccess
    }; Q_ENUM(SuccessCode)

    enum ErrorCode {
        UnknownError
    }; Q_ENUM(ErrorCode)

    enum Roles {
        TransactionItemIdRole = Qt::UserRole,
        CategoryIdRole,
        CategoryRole,
        ProductIdRole,
        UnitPriceRole,
        ProductRole,
        QuantityRole,
        UnitIdRole,
        UnitRole,
        CostRole,
        DiscountRole,
        CurrencyRole,
        NoteIdRole,
        NoteRole,
        SuspendedRole,
        ArchivedRole,
        CreatedRole,
        LastEditedRole,
        UserIdRole,
        UserRole
    };

    enum Columns {
        CategoryColumn,
        ProductColumn,
        QuantityColumn,
        UnitPriceColumn,
        CostColumn,
        ColumnCount
    };

    explicit QMLPurchaseTransactionItemModel(QObject *parent = nullptr);
    explicit QMLPurchaseTransactionItemModel(DatabaseThread &thread, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override final;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override final;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override final;
    QHash<int, QByteArray> roleNames() const override final;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role) const override;

    Q_INVOKABLE void removeSoldProduct(int row);
protected:
    void tryQuery() override final;
    void processResult(const QueryResult result) override final;
    QString columnName(int column) const override;
private:
    Utility::PurchasedProductList m_products;
};

#endif // QMLPURCHASETRANSACTIONITEMMODEL_H
