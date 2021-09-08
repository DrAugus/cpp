cmake_minimum_required(VERSION 3.9)
project(TRAINING)

set(CMAKE_CXX_STANDARD 14)

# include
include_directories(
        ${CMAKE_SOURCE_DIR}/include
)

# libs path
link_directories(${CMAKE_SOURCE_DIR}/lib)
# set libs variable
set(LIBS
        gmockd
        gtestd) # libgtest.a

# sources path
aux_source_directory(. SRC)

add_executable(${PROJECT_NAME} ${SRC})

# link
target_link_libraries(${PROJECT_NAME} ${LIBS})