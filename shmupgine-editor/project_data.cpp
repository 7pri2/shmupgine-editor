#include "project_data.h"

project_data::project_data() {
    entity_max_id = 0;
    prj_config[MAKE_PATH]       = DEFAULT_MAKE;
    prj_config[COMPILER_FLAGS]  = DEFAULT_CXXFLAGS;
    prj_config[COMPILER_PATH]   = DEFAULT_CXX;
    makefile = "";
}

project_data::~project_data() {

}

QString project_data::generate_makefile() {
    makefile = "";
    makefile += QString("CXX=") + prj_config[COMPILER_PATH] +QString("\n");
    makefile += QString("");
}
