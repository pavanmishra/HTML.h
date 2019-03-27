project(html_lib_tests)

add_executable(tests main.cpp)
target_link_libraries(tests PRIVATE html_lib)
target_compile_features(tests PRIVATE cxx_std_17)
