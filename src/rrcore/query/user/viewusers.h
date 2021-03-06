#ifndef VIEWUSERS_H
#define VIEWUSERS_H

#include "userexecutor.h"
#include "utility/common/recordgroup.h"

namespace Query {
namespace User {
class ViewUsers : public UserExecutor
{
    Q_OBJECT
public:
    static inline const QString COMMAND = QStringLiteral("view_users");

    explicit ViewUsers(const Utility::RecordGroup::Flags& flags,
                       QObject* receiver);
    QueryResult execute() override;
};
}  // namespace User
}  // namespace Query

#endif  // VIEWUSERS_H
