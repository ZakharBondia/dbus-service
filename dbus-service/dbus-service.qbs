import qbs

QtApplication {
    cpp.cxxLanguageVersion: "c++14"
    consoleApplication: true
x        "main.cpp",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
x
