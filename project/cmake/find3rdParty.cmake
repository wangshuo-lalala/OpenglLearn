message(STATUS "find3rdparty module load succeed!")

################################################################################################
# this Macro find a generic dependency, handling debug suffix
# all the paramenter are required, in case of lists, use "" in calling
################################################################################################

################################################################################################
#FIND_DEPENDENCY宏的参数说明
#DEPNAME 				依赖库名（如TIFF、CURL）
#INCLUDEFILE 			INCLUDE中包含的头文件（如tiff.h、curl.h）
#LIBRARY_NAMES_BASE		静态库名（如"libcurl;curllib;libcurl_imp"）
#SEARCHPATHLIST			查找路径
#DEBUGSUFFIX			DEBUG库的后缀
#EXSUFFIX				其他后缀
################################################################################################
MACRO(FIND_DEPENDENCY DEPNAME INCLUDEFILE LIBRARY_NAMES_BASE SEARCHPATHLIST DEBUGSUFFIX EXSUFFIX)

    MESSAGE(STATUS "searching ${DEPNAME} -->${INCLUDEFILE}<-->${LIBRARY_NAMES_BASE}<-->${SEARCHPATHLIST}<--")

    SET(MY_PATH_INCLUDE )
    SET(MY_PATH_LIB )
    
	#for循环，用于在SEARCHPATHLIST中查找INCLUDE路径和LIB路径，分别赋值给MY_PATH_INCLUDE和MY_PATH_LIB
    FOREACH( MYPATH ${SEARCHPATHLIST} )
        SET(MY_PATH_INCLUDE ${MY_PATH_INCLUDE} ${MYPATH}/include ${MYPATH}/include/${DEPNAME})
        SET(MY_PATH_LIB ${MY_PATH_LIB} ${MYPATH}/lib ${MYPATH}/lib/${DEPNAME})
    ENDFOREACH( MYPATH ${SEARCHPATHLIST} )
    
	
	#在MY_PATH_INCLUDE和NO_DEFAULT_PATH路径中查找INCLUDEFILE文件，并将路径赋值给${DEPNAME}_INCLUDE_DIR
    FIND_PATH("${DEPNAME}_INCLUDE_DIR" ${INCLUDEFILE}
      ${MY_PATH_INCLUDE}
      NO_DEFAULT_PATH
    )
    MARK_AS_ADVANCED("${DEPNAME}_INCLUDE_DIR")
    #MESSAGE( " ${DEPNAME}_INCLUDE_DIR --> ${${DEPNAME}_INCLUDE_DIR}<--")
    
	#查找Release库
    SET(LIBRARY_NAMES "")
    FOREACH(LIBNAME ${LIBRARY_NAMES_BASE})
        LIST(APPEND LIBRARY_NAMES "${LIBNAME}")
        LIST(APPEND LIBRARY_NAMES "${LIBNAME}${EXSUFFIX}")
    ENDFOREACH(LIBNAME)
    FIND_LIBRARY("${DEPNAME}_LIBRARY"
        NAMES ${LIBRARY_NAMES}
      PATHS ${MY_PATH_LIB}
      NO_DEFAULT_PATH
    )
	
	#查找Debug库
    SET(LIBRARY_NAMES_DEBUG "")
    FOREACH(LIBNAME ${LIBRARY_NAMES_BASE})
        LIST(APPEND LIBRARY_NAMES_DEBUG "${LIBNAME}${DEBUGSUFFIX}")
        LIST(APPEND LIBRARY_NAMES_DEBUG "${LIBNAME}${EXSUFFIX}${DEBUGSUFFIX}")
        LIST(APPEND LIBRARY_NAMES_DEBUG "${LIBNAME}${DEBUGSUFFIX}${EXSUFFIX}")
    ENDFOREACH(LIBNAME)
    FIND_LIBRARY("${DEPNAME}_LIBRARY_DEBUG" 
        NAMES ${LIBRARY_NAMES_DEBUG}
      PATHS ${MY_PATH_LIB}
      NO_DEFAULT_PATH
    )
    MARK_AS_ADVANCED("${DEPNAME}_LIBRARY")
    #MESSAGE( " ${DEPNAME}_LIBRARY --> ${${DEPNAME}_LIBRARY}<--")
	
	#设置标记库已找到（如CURL_FOUND）,如果DEBUG库未找到，则使用Release库
    SET( ${DEPNAME}_FOUND "NO" )
    IF(${DEPNAME}_INCLUDE_DIR AND ${DEPNAME}_LIBRARY)
      SET( ${DEPNAME}_FOUND "YES" )
      IF(NOT ${DEPNAME}_LIBRARY_DEBUG)
          MESSAGE("-- Warning Debug ${DEPNAME} not found, using: ${${DEPNAME}_LIBRARY}")
          SET(${DEPNAME}_LIBRARY_DEBUG "${${DEPNAME}_LIBRARY}")
      ENDIF(NOT ${DEPNAME}_LIBRARY_DEBUG)
    ENDIF(${DEPNAME}_INCLUDE_DIR AND ${DEPNAME}_LIBRARY)
ENDMACRO(FIND_DEPENDENCY DEPNAME INCLUDEFILE LIBRARY_NAMES_BASE SEARCHPATHLIST DEBUGSUFFIX)

################################################################################################
# this Macro is tailored to Mike and Torbens dependencies
################################################################################################

MACRO(SEARCH_3RDPARTY ACTUAL_3RD_PARTY_DIR)
	#查找GLFW库
    FIND_DEPENDENCY(GLFW GLFW/glfw3.h "glfw3" ${ACTUAL_3RD_PARTY_DIR} "D" "_i")
	#查找glad库
    FIND_DEPENDENCY(GLAD glad/glad.h "glad" ${ACTUAL_3RD_PARTY_DIR} "D" "")
	#查找LOG4CPP库
    #FIND_DEPENDENCY(FREEGlUT Configurator.hh "log4cpp" ${ACTUAL_3RD_PARTY_DIR} "D" "")
	#查找ZLIB库
    #FIND_DEPENDENCY(ZLIB zlib.h "z;zlib;zlib1" ${ACTUAL_3RD_PARTY_DIR} "D" "")
    #查找GDAL库
    #FIND_DEPENDENCY(GDAL gdal/gdal.h "gdal_i" ${ACTUAL_3RD_PARTY_DIR} "D" "")
ENDMACRO(SEARCH_3RDPARTY 3RD_PARTY_DIR)

IF(EXISTS ${3RD_PARTY_DIR})
    SEARCH_3RDPARTY(${3RD_PARTY_DIR})
ENDIF(EXISTS ${3RD_PARTY_DIR})
