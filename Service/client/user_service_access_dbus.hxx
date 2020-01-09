/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#ifndef USERSERVICEACCESSDBUS_HXX
#define USERSERVICEACCESSDBUS_HXX

#include <QDBusAbstractInterface>
#include <QDBusReply>
#include <QObject>
#include <QDebug>

class UserServiceAccessDbus : public QDBusAbstractInterface
{
    Q_OBJECT
public:
    explicit UserServiceAccessDbus(QObject *parent = nullptr);

public Q_SLOTS:
    virtual QString AddUser(QString name)  {
        //dbus call
        QDBusReply<QString> res = call("AddUser", name);
        if (!res.isValid())
        {
            qWarning() << res.error().message();
        }
        return res.value();
    }

Q_SIGNALS:
    void userAdded(QString id, QString name);

};

#endif // USERSERVICEACCESSDBUS_HXX
