project(html_library) 

add_library(html_lib STATIC html.hpp html.cpp)
#set_target_properties(html_lib PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(html_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
