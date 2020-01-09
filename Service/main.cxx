/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDebug>
#include "server/user_service.hxx"
#include "server/user_service_dbus.hxx"
#include "server/user_service_proxy.hxx"

#include "client/user_service_access.hxx"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    UserService service;
    //REGISTRATION
    new UserServiceDbusAdaptor(new UserServiceProxy(&service));

    UserServiceAccess access;
    qDebug() << access.AddUser("zak");

    QObject::connect(&access, &UserServiceAccess::userAdded, [](auto id, auto name){
        qDebug() << "new user" << name << "with id" << id;
    });

    service.AddUser("zak22");
    return a.exec();
}
