cmake_minimum_required(VERSION 3.9)
project(eco_feature)

set(CMAKE_CXX_STANDARD 17)
find_package(Boost 1.65.1 COMPONENTS system filesystem)
find_package( OpenCV REQUIRED )

file(GLOB SOURCE_FILES src/*.cpp include/*.hpp)

include_directories( include/ )
add_executable(eco_feature ${SOURCE_FILES})
target_link_libraries( eco_feature ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${OpenCV_LIBS} )