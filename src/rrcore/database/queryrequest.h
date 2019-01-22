#ifndef QUERYREQUEST_H
#define QUERYREQUEST_H

#include <QObject>
#include <QVariantMap>
#include <QDebug>

class QueryRequest : public QObject
{
    Q_OBJECT
public:
    enum Type {
        Unknown,
        Client,
        User,
        Dashboard,
        Stock,
        Sales,
        Purchase,
        Income,
        Expense,
        Debtor
    }; Q_ENUM(Type)
    explicit QueryRequest(QObject *receiver = nullptr); // NOTE: The parent parameter is mandatory!
    QueryRequest(const QueryRequest &other);
    QueryRequest &operator= (const QueryRequest &other);

    inline bool operator ==(const QueryRequest &other) const {
        return m_command == other.command() && m_type == other.type() && parent() == other.parent();
    }

    QObject *receiver() const;
    void setReceiver(QObject *receiver);

    void setCommand(const QString &command, const QVariantMap &params, const Type type);
    QString command() const;
    QVariantMap params() const;
    Type type() const;

    friend QDebug operator<<(QDebug debug, const QueryRequest &request)
    {
        debug.nospace() << "QueryRequest(command=" << request.command()
                        << ", params=" << request.params()
                        << ", type=" << request.type() << ") ";

        return debug;
    }
private:
    QObject *m_receiver;
    QString m_command;
    QVariantMap m_params;
    Type m_type;
};

#endif // QUERYREQUEST_H
