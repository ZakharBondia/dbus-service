/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#ifndef USERSERVICEACCESSDBUS_HXX
#define USERSERVICEACCESSDBUS_HXX

#include <QDBusAbstractInterface>
#include <QDBusReply>
#include <QObject>
#include <QDebug>


#include "server/user_service_dbus.hxx"

class UserServiceAccessDbus : public QDBusAbstractInterface
{
    Q_OBJECT
public:
    explicit UserServiceAccessDbus(QObject *parent = nullptr)
        : QDBusAbstractInterface(S_SERVICE, S_PATH, S_INTERFACE, QDBusConnection::systemBus(), parent)
    {

    }

public Q_SLOTS:
    virtual QString AddUser(QString name) const {
        //dbus call
        QDBusReply<QString> res = const_cast<QDBusAbstractInterface&>(static_cast<const QDBusAbstractInterface&>(*this)).call("AddUser", name);
        if (!res.isValid())
        {
            qCritical() << res.error().message();
        }
        return res.value();
    }

Q_SIGNALS:
    void userAdded(QString id, QString name);

};

#endif // USERSERVICEACCESSDBUS_HXX
