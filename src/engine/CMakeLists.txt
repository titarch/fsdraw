set(engine_src_files
        )

add_library(engine ${engine_src_files})

target_link_libraries(engine PRIVATE)