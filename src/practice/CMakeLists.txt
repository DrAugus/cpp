# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
file(GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
# file( GLOB APP_SOURCES ${CMAKE_SOURCE_DIR}/*.c )
# AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} APP_SOURCES)

foreach (practice_file ${APP_SOURCES})
    # I used a simple string replace, to cut off .cpp.
    string(REPLACE ".cpp" "" practice_name ${practice_file})
    add_executable(${practice_name} ${practice_file})

    set_target_properties(${practice_name} PROPERTIES LINKER_LANGUAGE CXX)
    if (OpenMP_CXX_FOUND)
        target_link_libraries(${practice_name} OpenMP::OpenMP_CXX)
    endif ()
    find_package (Threads REQUIRED)

    # curl
    find_package(CURL REQUIRED)
    target_link_libraries(${practice_name} ${CURL_LIBRARIES})

    target_link_libraries(${practice_name} ${CMAKE_THREAD_LIBS_INIT})
    install(TARGETS ${practice_name} DESTINATION "bin/backtracking")

endforeach (practice_file ${APP_SOURCES})


include_directories(
        ${CMAKE_SOURCE_DIR}/include
)