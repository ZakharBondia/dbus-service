/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#ifndef USERSERVICEPROXY_HXX
#define USERSERVICEPROXY_HXX

#include "user_service_interface.hxx"
#include "converters.hxx"


class UserServiceProxy: public QObject
{
    Q_OBJECT

    IUserService *dst_;
public:
    UserServiceProxy(IUserService *dst);

public Q_SLOTS:
    virtual ToJsonConvertor AddUser(FromJsonConvertor name) {
        return dst_->AddUser(name);
    }

Q_SIGNALS:
    void userAdded(ToJsonConvertor id, ToJsonConvertor name);

private:
    bool _userAdded = [this]{
        connect(dst_, &std::remove_reference_t<decltype (*dst_)>::userAdded, this, &std::remove_reference_t<decltype (*this)>::userAdded);
        return true;
    }();
};

#endif // USERSERVICEPROXY_HXX
