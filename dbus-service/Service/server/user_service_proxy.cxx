/*
 * Copyright (C) 2019 Duncan Technologies Pty Ltd. All rights reserved.
 */
#include "user_service_proxy.hxx"

UserServiceProxy::UserServiceProxy(IUserService *dst)
    : QObject{dst}
    , dst_{dst}
{

}
