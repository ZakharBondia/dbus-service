/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#ifndef USERSERVICEACCESSPROXY_HXX
#define USERSERVICEACCESSPROXY_HXX

#include <QObject>
#include "converters.hxx"
#include "user_service_access_dbus.hxx"

class UserServiceAccessProxy : public QObject
{
    Q_OBJECT

    UserServiceAccessDbus *dst_;
public:
    UserServiceAccessProxy(UserServiceAccessDbus *dst);

public Q_SLOTS:
    virtual FromJsonConvertor AddUser(ToJsonConvertor name) {
        return dst_->AddUser(name);
    }

Q_SIGNALS:
    void userAdded(FromJsonConvertor id, FromJsonConvertor name);


private:
    bool _userAdded = [this] {
        connect(dst_,
                &std::remove_reference_t<decltype(*dst_)>::userAdded,
                this,
                &std::remove_reference_t<decltype(*this)>::userAdded);
        return true;
    }();
};

#endif // USERSERVICEACCESSPROXY_HXX
