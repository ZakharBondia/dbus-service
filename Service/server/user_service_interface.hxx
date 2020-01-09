/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#ifndef IUSERSERVICE_HXX
#define IUSERSERVICE_HXX

#include <QObject>


class IUserService : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;

public Q_SLOTS:
    virtual int AddUser(QString name) = 0;

Q_SIGNALS:
    void userAdded(int id, QString name);
};

#endif // IUSERSERVICE_HXX
