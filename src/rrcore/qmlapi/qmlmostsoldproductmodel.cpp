#include "qmlmostsoldproductmodel.h"
#include "database/databasethread.h"
#include <QDebug>

QMLMostSoldProductModel::QMLMostSoldProductModel(QObject *parent) :
    QMLMostSoldProductModel(DatabaseThread::instance(), parent)
{}

QMLMostSoldProductModel::QMLMostSoldProductModel(DatabaseThread &thread,
                                                 QObject *parent) :
    AbstractVisualListModel(thread, parent)
{}

int QMLMostSoldProductModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_records.count();
}

int QMLMostSoldProductModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 2;
}

QVariant QMLMostSoldProductModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0:
            return m_records.at(index.row()).toMap().value("product").toString();
        case 1:
            return m_records.at(index.row()).toMap().value("total_quantity").toDouble();
        }
    case CategoryIdRole:
        return m_records.at(index.row()).toMap().value("category_id").toInt();
    case CategoryRole:
        return m_records.at(index.row()).toMap().value("category").toInt();
    case ProductIdRole:
        return m_records.at(index.row()).toMap().value("product_id").toInt();
    case ProductRole:
        return m_records.at(index.row()).toMap().value("product").toString();
    case TotalRevenueRole:
        return m_records.at(index.row()).toMap().value("total_revenue").toDouble();
    case TotalQuantityRole:
        return m_records.at(index.row()).toMap().value("total_quantity").toDouble();
    case UnitIdRole:
        return m_records.at(index.row()).toMap().value("unit_id").toInt();
    case UnitRole:
        return m_records.at(index.row()).toMap().value("unit").toString();
    }

    return QVariant();
}

QHash<int, QByteArray> QMLMostSoldProductModel::roleNames() const
{
    QHash<int, QByteArray> roles(AbstractVisualListModel::roleNames());
    roles.insert(CategoryIdRole, "category_id");
    roles.insert(CategoryRole, "category");
    roles.insert(ProductIdRole, "product_id");
    roles.insert(ProductRole, "product");
    roles.insert(TotalRevenueRole, "total_revenue");
    roles.insert(TotalQuantityRole, "total_quantity");
    roles.insert(UnitIdRole, "product_unit_id");
    roles.insert(UnitRole, "unit");

    return roles;
}

void QMLMostSoldProductModel::tryQuery()
{

}

bool QMLMostSoldProductModel::canProcessResult(const QueryResult &result) const
{
    Q_UNUSED(result)
    return true;
}

void QMLMostSoldProductModel::processResult(const QueryResult &result)
{
    Q_UNUSED(result)
}