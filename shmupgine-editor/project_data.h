#ifndef PROJECT_DATA_H
#define PROJECT_DATA_H

#define BTN_WIDTH 32

#include <QString>
#include "singleton.h"

#ifdef __unix__
    #define DEFAULT_PATH        "~/"
    #define DEFAULT_MAKE        "make"
    #define DEFAULT_CXX         "g++"
    #define DEFAULT_CXXFLAGS    "-Wall -Werror -std=c++11"
#elif defined __WIN32
    #define DEFAULT_PATH        "~/"
    #define DEFAULT_MAKE        "make"
    #define DEFAULT_CXX         "g++"
    #define DEFAULT_CXXFLAGS    "-Wall -Werror -std=c++11"
#endif

enum {
    NAME            = 0,
    WORKING_DIR     = 1,
    COMPILER_PATH   = 2,
    COMPILER_FLAGS  = 3,
    ENGINE_PATH     = 4,
    MAKE_PATH       = 5
};

class project_data : public Singleton<project_data> {
    friend class Singleton<project_data>;
    friend class w_editor;
    friend class w_new_project;

public:
    QString prj_config[6];
    QString prj_config_file;
    bool    f_config_changed;
    int     entity_max_id;

private:
    project_data();
    ~project_data();
};

#endif // PROJECT_DATA_H
