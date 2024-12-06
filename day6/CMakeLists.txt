add_executable(day6-1 day6-1.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(day6-1 PRIVATE "-fsanitize=address,undefined")
  target_link_options(day6-1 PRIVATE "-fsanitize=address,undefined")
endif()
