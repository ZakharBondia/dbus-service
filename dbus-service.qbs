import qbs

QtApplication {
    cpp.cxxLanguageVersion: "c++14"
    consoleApplication: true
    files: [
        "main.cpp",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
