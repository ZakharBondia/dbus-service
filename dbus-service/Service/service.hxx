
#if 0
/*DBUS access for caller*/ \
    class NAME##DBus : public QDBusAbstractInterface \
    { \
        Q_OBJECT \
    public: \
        explicit NAME##DBus(QObject *parent = nullptr) \
            : QDBusAbstractInterface(BUS_SERVICE, \
                                     BUS_PATH, \
                                     BUS_INTERFACE, \
                                     QDBusConnection::systemBus(), \
                                     parent) \
        {} \
\
    public Q_SLOTS: \
        API(STRING_ARG, STRING_ARG, DBUS_CALL_IMPL) \
    Q_SIGNALS: \
        SIGNALS(STRING_ARG, NO_IMPL) \
    }; \

#endif
