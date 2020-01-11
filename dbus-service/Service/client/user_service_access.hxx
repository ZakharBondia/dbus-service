/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#ifndef USERSERVICEACCESS_HXX
#define USERSERVICEACCESS_HXX

#include <QObject>


#include "server/user_service_interface.hxx"
#include "user_service_access_proxy.hxx"

class UserServiceAccess : public IUserService
{
    Q_OBJECT

    UserServiceAccessProxy dst_{this};
public:
    explicit UserServiceAccess(QObject *parent = nullptr)
        : IUserService(parent)
    {
    }

public Q_SLOTS:
    virtual int AddUser(QString name) override {
        //proxy call
        return dst_.AddUser(name);
    }


//    virtual QString GetUser(int id) const override
//    {
//        return "??";
//    }
};

#include <memory>
template<class T>
std::unique_ptr<T> AccessService();

template<>
inline std::unique_ptr<IUserService> AccessService()
{
    return std::unique_ptr<IUserService>{new UserServiceAccess};
}


#endif // USERSERVICEACCESS_HXX
