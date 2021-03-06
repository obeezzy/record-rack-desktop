#ifndef MODELRESULT_H
#define MODELRESULT_H

#include <QDebug>
#include <QObject>

class ModelResult
{
    Q_GADGET
    Q_PROPERTY(int code READ code CONSTANT)
    Q_PROPERTY(QVariant extra READ extra WRITE setExtra)
public:
    ModelResult() = default;
    ModelResult(const ModelResult& other);
    explicit ModelResult(int code);
    ModelResult& operator=(const ModelResult& other);
    ~ModelResult() = default;

    int code() const;

    QVariant extra() const;
    void setExtra(const QVariant& extra);

    bool operator==(const ModelResult& other) { return m_code == other.code(); }

    friend QDebug operator<<(QDebug debug, const ModelResult& result)
    {
        debug.nospace() << "ModelResult(code=" << result.code()
                        << ", extra=" << result.extra() << ")";
        debug.space();
        return debug;
    }

private:
    int m_code{0};
    QVariant m_extra;
};
Q_DECLARE_METATYPE(ModelResult)

#endif  // MODELRESULT_H
