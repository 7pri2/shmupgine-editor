#include "project_data.h"

project_data::project_data() {
    entity_max_id = 0;
    prj_config[MAKE_PATH]       = DEFAULT_MAKE;
    prj_config[COMPILER_FLAGS]  = DEFAULT_CXXFLAGS;
    prj_config[COMPILER_PATH]   = DEFAULT_CXX;
}

project_data::~project_data() {

}
