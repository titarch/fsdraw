set(utils_src_files
        vectormath.hh
        )
add_library(utils ${utils_src_files})
set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)