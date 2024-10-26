# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.

file(GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# file( GLOB APP_SOURCES ${CMAKE_SOURCE_DIR}/*.c )
# AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} APP_SOURCES)
find_package(Threads REQUIRED)
find_package(CAF REQUIRED)

set(CURRENT_DIR_NAME "linux_caf")
set(LANGUAGE "CXX")
set(LIBRARIES ${CMAKE_THREAD_LIBS_INIT} CAF::io)

include(${CMAKE_SOURCE_DIR}/cmake/CMakeFunctions.cmake)

foreach_all_files(${LANGUAGE} ${CURRENT_DIR_NAME} ${APP_SOURCES} ${LIBRARIES})

# target_link_libraries(${caf_name} ${CAF_LIBRARIES})
# target_link_libraries(${caf_name} PRIVATE CAF::internal CAF::core CAF::io)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CAF_INCLUDE_DIRS}
)
