/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#include "server/user_service.hxx"
#include "server/user_service_dbus.hxx"
#include "server/user_service_proxy.hxx"
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDebug>

#include "client/user_service_access.hxx"

//////////////////
#include "myservice.hxx"

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    MyService my_service;
    IMyService *ptr = &my_service;
    new IMyServiceDbusAdaptor(new IMyServiceProxy(ptr));

    QObject::connect(ptr, &IMyService::userAccessed2, []() {
        qDebug() << "userAccessed2";
    });

//    QObject root;
//    NAMEDbusAdaptor name(&root);
#if 0
    UserService service;
    //REGISTRATION
    RegisterService(&service);

    std::unique_ptr<IUserService> access = AccessService<IUserService>();
    qDebug() << access->AddUser("zak");

    QObject::connect(access.get(), &IUserService::userAdded, [](auto id, auto name) {
        qDebug() << "new user" << name << "with id" << id;
    });

    service.AddUser("zak22");

#endif
    return a.exec();
}

