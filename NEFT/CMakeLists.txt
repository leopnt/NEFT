file(GLOB Sources "src/*.cpp")
add_library(NEFT STATIC ${Sources})
target_include_directories(NEFT PUBLIC "include")