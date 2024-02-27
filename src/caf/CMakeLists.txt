# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
file(GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
# file( GLOB APP_SOURCES ${CMAKE_SOURCE_DIR}/*.c )
# AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} APP_SOURCES)

find_package (Threads REQUIRED)
find_package(CAF REQUIRED)

foreach (caf_file ${APP_SOURCES})
    # I used a simple string replace, to cut off .cpp.
    string(REPLACE ".cpp" "" caf_name ${caf_file})
    add_executable(${caf_name} ${caf_file})
    set_target_properties(${caf_name} PROPERTIES LINKER_LANGUAGE CXX)
    target_link_libraries(${caf_name} ${CMAKE_THREAD_LIBS_INIT})
    # target_link_libraries(${caf_name} ${CAF_LIBRARIES})
    # target_link_libraries(${caf_name} PRIVATE CAF::internal CAF::core CAF::io)
    target_link_libraries(${caf_name} CAF::io)
    install(TARGETS ${caf_name} DESTINATION "bin/backtracking")

endforeach (caf_file ${APP_SOURCES})


include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CAF_INCLUDE_DIRS}
)
