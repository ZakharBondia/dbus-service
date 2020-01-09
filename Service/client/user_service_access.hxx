/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#ifndef USERSERVICEACCESS_HXX
#define USERSERVICEACCESS_HXX

#include <QObject>


#include "server/user_service_interface.hxx"
#include "user_service_access_proxy.hxx"

//TODO map same name signals automatically

//NOTE base interface under question since we need to know if
class UserServiceAccess : public IUserService
{
    Q_OBJECT

    UserServiceAccessDbus dbus;
    UserServiceAccessProxy *dst_;
public:
    explicit UserServiceAccess(QObject *parent = nullptr)
        : IUserService(parent)
        , dst_{new UserServiceAccessProxy(&dbus)}
    {
    }

public Q_SLOTS:
    virtual int AddUser(QString name) override {
        //proxy call
        return dst_->AddUser(name);
    }

private:
    bool _userAdded = [this]{
        connect(dst_, &std::remove_reference_t<decltype (*dst_)>::userAdded, this, &std::remove_reference_t<decltype (*this)>::userAdded);
        return true;
    }();
};

#endif // USERSERVICEACCESS_HXX
