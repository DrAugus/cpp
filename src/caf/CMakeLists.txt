# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
file(GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
# file( GLOB APP_SOURCES ${CMAKE_SOURCE_DIR}/*.c )
# AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} APP_SOURCES)

foreach (caf_file ${APP_SOURCES})
    # I used a simple string replace, to cut off .cpp.
    string(REPLACE ".cpp" "" caf_name ${caf_file})
    add_executable(${caf_name} ${caf_file})

    set_target_properties(${caf_name} PROPERTIES LINKER_LANGUAGE CXX)
    if (OpenMP_CXX_FOUND)
        target_link_libraries(${caf_name} OpenMP::OpenMP_CXX)
    endif ()

    find_package (Threads REQUIRED)
    target_link_libraries(${caf_name} ${CMAKE_THREAD_LIBS_INIT})
    install(TARGETS ${caf_name} DESTINATION "bin/backtracking")

endforeach (caf_file ${APP_SOURCES})


include_directories(
        ${CMAKE_SOURCE_DIR}/include
)
