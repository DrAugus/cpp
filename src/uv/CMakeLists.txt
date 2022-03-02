# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
file(GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
include_directories(${CMAKE_SOURCE_DIR}/include)

foreach (testsourcefile ${APP_SOURCES})
    # I used a simple string replace, to cut off .cpp.
    string(REPLACE ".cpp" "" testname ${testsourcefile})

    link_directories(lib)
    link_libraries(uv)

    add_executable(${testname} ${testsourcefile})

    target_link_libraries(${testname} uv)

    set_target_properties(${testname} PROPERTIES LINKER_LANGUAGE CXX)
    if (OpenMP_CXX_FOUND)
        target_link_libraries(${testname} OpenMP::OpenMP_CXX)
    endif ()

    install(TARGETS ${testname} DESTINATION "bin/uv")

endforeach (testsourcefile ${APP_SOURCES})

