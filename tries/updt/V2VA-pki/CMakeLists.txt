cmake_minimum_required(VERSION 3.6)
project(V2VA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(OpenCV REQUIRED) #OpenCV
set(SOURCE_FILES main.cpp v2va.cpp v2va.h Udplink.cpp Udplink.h Alv.cpp Alv.h crc32.cpp crc32.h)


#LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib) #OpenALPR
add_executable(V2VA ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(V2VA -lpthread libopenalpr.so) #OpenALPR
TARGET_LINK_LIBRARIES(V2VA libcryptopp.so) #crypto++

include_directories($(OpenCV_INCLUDE_DIRS)) #OpenCV
target_link_libraries(V2VA -lpthread ${OpenCV_LIBS}) #OpenCV