project(start)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB APP_SRCS *.cpp *.h)

add_executable(start ${APP_SRCS})
target_link_libraries(
    start
    debug ${GLFW_LIBRARY_DEBUG} optimized ${GLFW_LIBRARY}
    debug ${GLAD_LIBRARY_DEBUG} optimized ${GLAD_LIBRARY}
    debug jsgd optimized jsg
)
if (WIN32)
    Set_Target_Properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()