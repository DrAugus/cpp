# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
file(GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
# file( GLOB APP_SOURCES ${CMAKE_SOURCE_DIR}/*.c )
# AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} APP_SOURCES)

find_package (Threads REQUIRED)
set(fmt_DIR ${PROJECT_SOURCE_DIR}/3rd/fmt/build)
find_package(fmt)

foreach (primer_file ${APP_SOURCES})
    # I used a simple string replace, to cut off .cpp.
    string(REPLACE ".cpp" "" primer_name ${primer_file})
    add_executable(${primer_name} ${primer_file})
    set_target_properties(${primer_name} PROPERTIES LINKER_LANGUAGE CXX)
    target_link_libraries(${primer_name} ${CMAKE_THREAD_LIBS_INIT})
    target_link_libraries(${primer_name} fmt::fmt)
    install(TARGETS ${primer_name} DESTINATION "bin/backtracking")
endforeach (primer_file ${APP_SOURCES})

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)