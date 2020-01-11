/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#ifndef USERSERVICEDBUS_HXX
#define USERSERVICEDBUS_HXX

#include <QDBusAbstractAdaptor>
#include <QDBusConnection>

#include "user_service_proxy.hxx"

#include <type_traits>

#define S_INTERFACE "a.User.api"
#define S_SERVICE "a.User"
#define S_PATH "/a/user"

class UserServiceDbusAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", S_INTERFACE)

    UserServiceProxy *dst_;

public:
    explicit UserServiceDbusAdaptor(UserServiceProxy *parent = nullptr)
        : QDBusAbstractAdaptor(parent)
        , dst_{parent}
    {
        setAutoRelaySignals(true);

        auto connection = QDBusConnection::systemBus();
        if (!connection.registerObject(S_PATH, parent)) {
            qWarning("Cannot register object.");
        }
        connection.registerService(S_SERVICE);
    }

public Q_SLOTS:
    virtual QString AddUser(QString name) { return dst_->AddUser(name); }

Q_SIGNALS:
    void userAdded(QString id, QString name);

private:
    bool _userAdded = [this] {
        connect(dst_,
                &std::remove_reference_t<decltype(*dst_)>::userAdded,
                this,
                &std::remove_reference_t<decltype(*this)>::userAdded);
        return true;
    }();
};

inline void RegisterService(IUserService *service)
{
    new UserServiceDbusAdaptor(new UserServiceProxy(service));
}
#endif // USERSERVICEDBUS_HXX
