project(html_library) 

add_library(html_lib STATIC html.hpp html.cpp)
target_include_directories(html_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(html_lib PRIVATE cxx_std_17)
