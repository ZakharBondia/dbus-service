/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#pragma once


#include <QDBusAbstractInterface>
#include <QDBusAbstractAdaptor>
#include <QDBusReply>
#include <QDebug>
#include <QObject>
#include <QDBusConnection>

#include <type_traits>

#include <converters.hxx>

#define IMPL_PURE(...) = 0;
#define NO_IMPL(...) ;
#define SAME_ARG(T) T
#define STRING_ARG(T) QString
#define TOJSONCONVERTOR_ARG(T) ToJsonConvertor
#define FROMJSONCONVERTOR_ARG(T) FromJsonConvertor
#define FWD_CAL_IMPL(VAR_PTR, FUNC, ...) \
    { \
        return VAR_PTR->FUNC(__VA_ARGS__); \
    }
#define FWD_SIGNALS_IMPL(SRC_PTR, DST_PTR, FUNC) \
    ; \
private: \
    bool hidden_connector_for_##FUNC##_ = [this] { \
        connect(SRC_PTR, \
                &std::remove_reference_t<decltype(*SRC_PTR)>::FUNC, \
                DST_PTR, \
                &std::remove_reference_t<decltype(*DST_PTR)>::FUNC); \
        return true; \
    }(); \
Q_SIGNALS:

#define DST_TO_THIS_FWD_SIGNALS_IMPL(FUNC, ...) FWD_SIGNALS_IMPL(dst_, this, FUNC)

#define DST_CAL_IMPL(FUNC, ...) FWD_CAL_IMPL(dst_, FUNC, __VA_ARGS__)


#define DEBUG_CALL_IMPL(...) {qDebug() << __func__; return {}; }


#define DBUS_CALL_IMPL(FUNC, ...) \
    { \
        auto helper = [&](auto... args) { \
            QDBusReply<QString> res = const_cast<QDBusAbstractInterface &>( \
                                          static_cast<const QDBusAbstractInterface &>(*this)) \
                                          .call(#FUNC, args...); \
        }; \
        helper(__VA_ARGS__); \
        return {}; \
    }

#define CREATE_SERVICE_INTERFACE(NAME, API, SIGNALS, BUS_SERVICE, BUS_PATH, BUS_INTERFACE) \
    /*Service interface*/ \
    class NAME : public QObject \
    { \
        Q_OBJECT \
    public: \
        using QObject::QObject; \
\
    public Q_SLOTS: \
        API(SAME_ARG, SAME_ARG, IMPL_PURE) \
    Q_SIGNALS: \
        SIGNALS(SAME_ARG, NO_IMPL) \
    }; \
\
    /*Forwards calls from itself to service interface and signals from interface back to itself*/ \
    class NAME##Proxy : public QObject \
    { \
        Q_OBJECT \
\
        NAME *dst_; \
\
    public: \
        NAME##Proxy(NAME *dst) \
            : QObject{dst} \
            , dst_{dst} \
        {} \
\
    public Q_SLOTS: \
        API(TOJSONCONVERTOR_ARG, FROMJSONCONVERTOR_ARG, DST_CAL_IMPL) \
\
    Q_SIGNALS: \
        SIGNALS(TOJSONCONVERTOR_ARG, DST_TO_THIS_FWD_SIGNALS_IMPL) \
    }; \
\
    /*Forwards calls from itself(coming over dubs) to proxy object and signals from proxy thisto itself(to send over dbus)*/ \
    class NAME##DbusAdaptor : public QDBusAbstractAdaptor \
    { \
        Q_OBJECT \
        Q_CLASSINFO("D-Bus Interface", BUS_INTERFACE) \
\
        NAME##Proxy *dst_; \
\
    public: \
        explicit NAME##DbusAdaptor(NAME##Proxy *parent) \
            : QDBusAbstractAdaptor(parent) \
            , dst_{parent} \
        { \
            setAutoRelaySignals(true); \
\
            auto connection = QDBusConnection::systemBus(); \
            if (!connection.registerObject(BUS_PATH, parent)) { \
                qWarning("Cannot register object."); \
                throw 2; \
            } \
            if (!connection.registerService(BUS_SERVICE)) { \
                qWarning("Cannot register service."); \
                throw 3; \
            } \
        } \
\
    public Q_SLOTS: \
        API(STRING_ARG, STRING_ARG, DST_CAL_IMPL) \
\
    Q_SIGNALS: \
        SIGNALS(STRING_ARG, DST_TO_THIS_FWD_SIGNALS_IMPL) \
    }; \
\
    class NAME##AccessDbus : public QDBusAbstractInterface \
    { \
        Q_OBJECT \
    public: \
        explicit NAME##AccessDbus(QObject *parent = nullptr) \
            : QDBusAbstractInterface(BUS_SERVICE, \
                                     BUS_PATH, \
                                     BUS_INTERFACE, \
                                     QDBusConnection::systemBus(), \
                                     parent) \
        {} \
\
    public Q_SLOTS: \
        API(STRING_ARG, STRING_ARG, DBUS_CALL_IMPL) \
\
    Q_SIGNALS: \
        SIGNALS(STRING_ARG, NO_IMPL) \
    }; \
    class NAME##AccessProxy : public QObject \
    { \
        Q_OBJECT \
\
        NAME##AccessDbus *dst_{new NAME##AccessDbus(this)}; \
        NAME *src_; \
\
    public: \
        NAME##AccessProxy(NAME *src) \
            : QObject(src) \
            , src_{src} \
        {} \
\
    public Q_SLOTS: \
        API(FROMJSONCONVERTOR_ARG, TOJSONCONVERTOR_ARG, DST_CAL_IMPL) \
\
    Q_SIGNALS: \
        SIGNALS(FromJsonConvertor, NO_IMPL)\
};\

//private:
//bool _userAdded = [this] {
//    connect(&dst_,
//            &std::remove_reference_t<decltype(*&dst_)>::userAdded,
//            this,
//            &std::remove_reference_t<decltype(*this)>::userAdded);
//    connect(this,
//            &std::remove_reference_t<decltype(*this)>::userAdded,
//            src_,
//            &std::remove_reference_t<decltype(*src_)>::userAdded);
//    return true;
//}();
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "service.hxx"

#define MY_SERVICE_API(RET, ARG, IMPL) \
virtual RET(QString) GetUser(ARG(int) id) const IMPL(GetUser, id)\
virtual RET(int) GetUser2()  IMPL(GetUser2)\

#define MY_SERVICE_SINGALS(ARG, IMPL) \
    void userAccessed(ARG(int) id, ARG(QString) name)  IMPL(userAccessed) \
    void userAccessed2()  IMPL(userAccessed2) \


CREATE_SERVICE_INTERFACE(IMyService, MY_SERVICE_API, MY_SERVICE_SINGALS, "a.myservice", "/myservice/api", "myservice.api")


class MyService: public IMyService
{
    Q_OBJECT
public:
    QString GetUser(int /*id*/) const override { return "user1"; }
    int GetUser2() /*override*/
    {
        emit userAccessed2();
        return 42;
    }
};


