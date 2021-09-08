cmake_minimum_required(VERSION 3.9)
project(TRAINING)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        #        ${CMAKE_CURRENT_SOURCE_DIR}
        #        ${CMAKE_CURRENT_BINARY_DIR}
        #        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include
)

# sources path
aux_source_directory(. SRC)

# libs path
link_directories(${CMAKE_SOURCE_DIR}/lib)

# set libs variable
set(LIBS
        gmockd
        gtestd) # libgtest.a

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} ${LIBS})