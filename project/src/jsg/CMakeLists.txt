set(LIB_NAME jsg)
set(HEADER_PATH ${CMAKE_SOURCE_DIR}/include/jsg)
file(GLOB PRO_HEADERS ${HEADER_PATH}/*.h ${HEADER_PATH}/*.hpp)
file(GLOB PRO_INTERFACES ${CMAKE_SOURCE_DIR}/interface/*.h ${CMAKE_SOURCE_DIR}/interface/*.hpp)
file(GLOB PRO_SRCS *.cpp *.c)

source_group("interface" FILES ${PRO_INTERFACES})

add_library(
    ${LIB_NAME} 
    SHARED
    ${PRO_INTERFACES}
    ${PRO_HEADERS}
    ${PRO_SRCS}
)

target_link_libraries(
    ${LIB_NAME}
    debug ${GLFW_LIBRARY_DEBUG} optimized ${GLFW_LIBRARY}
    debug ${GLAD_LIBRARY_DEBUG} optimized ${GLAD_LIBRARY}
)

INSTALL(TARGETS ${LIB_NAME} ARCHIVE DESTINATION lib)
INSTALL(TARGETS ${LIB_NAME} RUNTIME DESTINATION bin)
#et_property(TARGET ${LIB_NAME} PROPERTY USE_FOLDERS ON)
#set_property(TARGET ${LIB_NAME} PROPERTY FOLDER "Core")