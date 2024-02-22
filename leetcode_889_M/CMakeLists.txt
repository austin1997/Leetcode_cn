
get_filename_component(FOLDER_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

project(${FOLDER_NAME})

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

include_directories(../utility)

add_executable(${PROJECT_NAME} main.cpp)
