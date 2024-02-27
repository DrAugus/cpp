# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
file(GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
# file( GLOB APP_SOURCES ${CMAKE_SOURCE_DIR}/*.c )
# AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} APP_SOURCES)

find_package (Threads REQUIRED)

foreach (testsourcefile ${APP_SOURCES})
    # I used a simple string replace, to cut off .cpp.
    string(REPLACE ".cpp" "" testname ${testsourcefile})
    add_executable(${testname} ${testsourcefile})
    set_target_properties(${testname} PROPERTIES LINKER_LANGUAGE CXX)
    target_link_libraries(${testname} ${CMAKE_THREAD_LIBS_INIT})
    install(TARGETS ${testname} DESTINATION "bin/backtracking")
endforeach (testsourcefile ${APP_SOURCES})

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)