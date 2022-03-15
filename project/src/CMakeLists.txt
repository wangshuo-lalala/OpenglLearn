SUBDIRLIST(SUB_DIR_LIST ${CMAKE_CURRENT_SOURCE_DIR})
foreach(src_dir ${SUB_DIR_LIST})
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${src_dir}/CMakeLists.txt")
        add_subdirectory(${src_dir})
    endif()
endforeach(src_dir ${SUB_DIR_LIST})

