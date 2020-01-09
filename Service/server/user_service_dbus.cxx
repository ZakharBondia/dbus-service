/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#include "user_service_dbus.hxx"

#include <QDBusConnection>

UserServiceDbusAdaptor::UserServiceDbusAdaptor(UserServiceProxy *parent) : QDBusAbstractAdaptor(parent), dst_{parent}
{
    setAutoRelaySignals(true);

    auto connection = QDBusConnection::systemBus();
    if (!connection.registerObject(S_PATH, parent))
    {
        qWarning("Cannot register object.");
    }
    connection.registerService(S_SERVICE);
}
