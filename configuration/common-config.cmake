add_definitions(-D_USE_MATH_DEFINES)

#Use solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(TESTS_SOLUTION_FOLDER_NAME Tests)

set(HEADERS_FOLDER "Header Files")
set(SRC_FOLDER "Source Files")
set(HEADERS_REGEXP ".*\\.h")
set(SRC_REGEXP ".*\\.cpp")

FUNCTION(add_source_groups)
    FOREACH(dir ${ARGN})
        SOURCE_GROUP(${HEADERS_FOLDER}\\${dir} REGULAR_EXPRESSION "${dir}/${HEADERS_REGEXP}")
        SOURCE_GROUP(${SRC_FOLDER}\\${dir} REGULAR_EXPRESSION "${dir}/${SRC_REGEXP}")
    ENDFOREACH()
ENDFUNCTION()

#This is a temporary solution. Should find better approach
FUNCTION(target_link_special_libraries_for_linux ARG_TARGET_NAME)
    if(UNIX AND NOT APPLE)
        target_link_libraries(${ARG_TARGET_NAME} rt)
    endif()
ENDFUNCTION()

IF(BUILD_K52_LIBRARY_TYPE STREQUAL Dynamic)
    SET(K52_LIBS_TYPE SHARED)
    SET(K52_LIBS_TYPE_DYNAMIC TRUE)
ELSE()
    #Default if Static
    SET(K52_LIBS_TYPE STATIC)
    SET(K52_LIBS_TYPE_DYNAMIC FALSE)
ENDIF()

message("${K52_MESSAGE_PREFIX} k52 libs will be build as ${K52_LIBS_TYPE} ${K52_MESSAGE_POSTFIX}")