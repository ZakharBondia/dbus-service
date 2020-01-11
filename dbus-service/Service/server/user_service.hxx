/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#ifndef USERSERVICE_HXX
#define USERSERVICE_HXX

#include "user_service_interface.hxx"


class UserService : public IUserService
{
    Q_OBJECT
public:
    UserService() = default;

public Q_SLOTS:
    virtual int AddUser(QString name) override {
        emit userAdded(next_id, name);
        return next_id++;
    }

private:
    int next_id = 0;
};

#endif // USERSERVICE_HXX
