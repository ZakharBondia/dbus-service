import qbs

QtApplication {
    cpp.cxxLanguageVersion: "c++14"

    cpp.defines: [
        // The following define makes your compiler emit warnings if you use
        // any Qt feature that has been marked deprecated (the exact warnings
        // depend on your compiler). Please consult the documentation of the
        // deprecated API in order to know how to port your code away from it.
        "QT_DEPRECATED_WARNINGS",

        // You can also make your code fail to compile if it uses deprecated APIs.
        // In order to do so, uncomment the following line.
        // You can also select to disable deprecated APIs only up to a certain version of Qt.
        //"QT_DISABLE_DEPRECATED_BEFORE=0x060000" // disables all the APIs deprecated before Qt 6.0.0
    ]

    Depends {
        name: "Qt.dbus"
    }

    cpp.includePaths: ["."]
    consoleApplication: true
    files: [
        "client/user_service_access.cxx",
        "client/user_service_access.hxx",
        "client/user_service_access_dbus.cxx",
        "client/user_service_access_dbus.hxx",
        "client/user_service_access_proxy.cxx",
        "client/user_service_access_proxy.hxx",
        "converters.cxx",
        "converters.hxx",
        "main.cxx",
        "myservice.cxx",
        "myservice.hxx",
        "server/user_service.cxx",
        "server/user_service.hxx",
        "server/user_service_dbus.cxx",
        "server/user_service_dbus.hxx",
        "server/user_service_interface.cxx",
        "server/user_service_interface.hxx",
        "server/user_service_proxy.cxx",
        "server/user_service_proxy.hxx",
        "service.hxx",
        "signal_mapper.hxx",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
