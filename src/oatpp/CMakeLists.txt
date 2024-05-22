# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
file(GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
# file( GLOB APP_SOURCES ${CMAKE_SOURCE_DIR}/*.c )
# AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} APP_SOURCES)

# find_package (Threads REQUIRED)
# set(fmt_DIR ${PROJECT_SOURCE_DIR}/3rd/fmt/build)
# find_package(fmt)
find_package(oatpp REQUIRED)

foreach (oatpp_file ${APP_SOURCES})
    # I used a simple string replace, to cut off .cpp.
    string(REPLACE ".cpp" "" oatpp_name ${oatpp_file})
    add_executable(${oatpp_name} ${oatpp_file})
    set_target_properties(${oatpp_name} PROPERTIES LINKER_LANGUAGE CXX)
    # target_link_libraries(${oatpp_name} ${CMAKE_THREAD_LIBS_INIT})
    # target_link_libraries(${oatpp_name} fmt::fmt)
    target_link_libraries(${oatpp_name} oatpp::oatpp)
    install(TARGETS ${oatpp_name} DESTINATION "bin/backtracking")
endforeach (oatpp_file ${APP_SOURCES})

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    oatpp_handle.h
)
