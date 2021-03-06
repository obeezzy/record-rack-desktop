#ifndef AMOUNTOVERPAIDEXCEPTION_H
#define AMOUNTOVERPAIDEXCEPTION_H

#include "database/databaseexception.h"

class AmountOverpaidException : public DatabaseException
{
public:
    explicit AmountOverpaidException(double amount);
    QString toString() const override;
};

#endif  // AMOUNTOVERPAIDEXCEPTION_H
