/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#include "user_service_access_dbus.hxx"

#include "server/user_service_dbus.hxx"

UserServiceAccessDbus::UserServiceAccessDbus(QObject *parent)
    : QDBusAbstractInterface(S_SERVICE, S_PATH, S_INTERFACE, QDBusConnection::systemBus(), parent)
{

}
