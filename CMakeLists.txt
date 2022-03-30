project(Leetcode_cn)

FILE(GLOB children RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/leetcode_*)
SET(dirlist "")
FOREACH(child ${children})
    IF(IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${child})
        LIST(APPEND dirlist ${child})
    ENDIF()
ENDFOREACH()

FOREACH(subdir ${dirlist})
    message("ADDING: ${subdir}")
    ADD_SUBDIRECTORY(${subdir})
ENDFOREACH()
