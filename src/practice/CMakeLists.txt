# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
file(GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# file( GLOB APP_SOURCES ${CMAKE_SOURCE_DIR}/*.c )
# AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} APP_SOURCES)
find_package(Threads REQUIRED)
set(LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

if(UNIX)
    find_package(CURL REQUIRED)
    set(LIBRARIES ${CMAKE_THREAD_LIBS_INIT} ${CURL_LIBRARIES})
endif()

set(CURRENT_DIR_NAME "practice")
set(LANGUAGE "CXX")

include(${CMAKE_SOURCE_DIR}/cmake/CMakeFunctions.cmake)

foreach_all_files(${LANGUAGE} ${CURRENT_DIR_NAME} ${APP_SOURCES} ${LIBRARIES})

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CURL_INCLUDE_DIRS}
)
