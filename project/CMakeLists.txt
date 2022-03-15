CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

project(hello_opengl)

#设置调试库的后缀
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_RELWITHDEBINFO_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_MINSIZEREL_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")

#设置库和可执行文件的输出文件
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 设置导出所有符号库不用加dllexport
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# load modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(utils)
include(find3rdParty)


#set the 3rdparty directory
SET(3RD_PARTY_DIR "" CACHE PATH "thrid party")

include_directories(${3RD_PARTY_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/interface)
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories("${CMAKE_BINARY_DIR}/lib/Debug")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_subdirectory(src)