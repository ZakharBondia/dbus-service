/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#ifndef CONVERTERS_HXX
#define CONVERTERS_HXX

#include <QString>

template<class T>
inline T FromJson(QString json);

template<>
inline int FromJson<int>(QString json)
{
    return json.toInt();
}
template<>
inline bool FromJson<bool>(QString json)
{
    return json == "true";
}

template<>
inline QString FromJson<QString>(QString json)
{
    return json;
}
//////////////////
template<class T>
inline QString ToJson(const T &v);

template<>
inline QString ToJson(const QString &v)
{
    return v;
}
template<>
inline QString ToJson(const int &v)
{
    return QString::number(v);
}

template<>
inline QString ToJson(const bool &v)
{
    return v ? "true" : "false";
}
//////////////////

struct FromJsonConvertor
{
    FromJsonConvertor() {}
    FromJsonConvertor(QString v)
        : v_{std::move(v)}
    {}

    template<class T>
    operator T() const
    {
        return FromJson<T>(v_);
    }

private:
    QString v_;
};
//////////////////
struct ToJsonConvertor
{
    ToJsonConvertor(){}
    template<class T>
    ToJsonConvertor(T v)
        : v_{ToJson(v)}
    {}

    operator QString() const { return v_; }

private:
    QString v_;
};

#include <QtCore>
Q_DECLARE_METATYPE(FromJsonConvertor)
Q_DECLARE_METATYPE(ToJsonConvertor)
#endif // CONVERTERS_HXX
