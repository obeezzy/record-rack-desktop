#include "qmldashboardhomemodel.h"
#include "database/databasethread.h"
#include "queryexecutors/dashboard.h"
#include <QTimer>
#include <QDebug>

QMLDashboardHomeModel::QMLDashboardHomeModel(QObject *parent)
    : QMLDashboardHomeModel(DatabaseThread::instance(), parent)
{}

QMLDashboardHomeModel::QMLDashboardHomeModel(DatabaseThread &thread, QObject *parent)
    : AbstractHomeModel(thread, parent)
{}

void QMLDashboardHomeModel::tryQuery()
{
    setBusy(true);
    emit execute(new DashboardQuery::ViewDashboard(this));
}

bool QMLDashboardHomeModel::canProcessResult(const QueryResult &result) const
{
    Q_UNUSED(result)
    return true;
}

void QMLDashboardHomeModel::processResult(const QueryResult &result)
{
    Q_UNUSED(result)
}
