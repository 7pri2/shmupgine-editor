#include "project_data.h"

project_data::project_data() {
    entity_max_id = 0;
    prj_config[MAKE_PATH]       = DEFAULT_MAKE;
    prj_config[COMPILER_FLAGS]  = DEFAULT_CXXFLAGS;
    prj_config[COMPILER_PATH]   = DEFAULT_CXX;
    prj_config_file = "project.json";
    audio_config_file = "audio.json";
    graphics_config_file = "graphics.json";
}

project_data::~project_data() {

}
