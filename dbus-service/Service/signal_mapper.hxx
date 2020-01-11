/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#ifndef SIGNAL_MAPPER_HXX
#define SIGNAL_MAPPER_HXX

#include <QMap>
#include <QMetaMethod>
#include <QMetaObject>
#include <QVector>

inline void Map(QObject *src, QObject *dst)
{
    auto GetSignals = [](QObject *obj) -> QMap<QString, QMetaMethod> {
        QMap<QString, QMetaMethod> res;
        auto isSignal = [](auto &m) { return m.methodType() == 1; };
        auto not_ignore = [](auto &m) {
            for (auto &n : {"destroyed", "objectNameChanged"}) {
                if (m.name() == n) {
                    return false;
                }
            }
            return true;
        };
        auto meta = obj->metaObject();
        for (auto i = 0; i < meta->methodCount(); ++i) {
            auto method = meta->method(i);
            if (isSignal(method) && not_ignore(method)) {
                res[method.name()] = method;
            }
        }

        return res;
    };

    auto src_signals = GetSignals(src);
    auto dst_signals = GetSignals(dst);
    for (auto it = src_signals.begin(); it != src_signals.end(); ++it) {
        QObject::connect(src, it.value(), dst, dst_signals[it.key()]);
//        QObject::connect(src, it.value(), dst, [](){});
    }
}

#endif // SIGNAL_MAPPER_HXX
