#ifndef IMAGETOOLARGEEXCEPTION_H
#define IMAGETOOLARGEEXCEPTION_H

#include "database/databaseexception.h"

class ImageTooLargeException : public DatabaseException
{
public:
    explicit ImageTooLargeException(int size, int maxSize);
    QString toString() const override;
};

#endif  // IMAGETOOLARGEEXCEPTION_H
