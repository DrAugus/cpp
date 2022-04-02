aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" training_src)
file(GLOB training_hdr *.h *.hpp)
source_group("Include" FILES ${training_hdr})

include_directories(
        ${CMAKE_SOURCE_DIR}/include
)

add_library(training OBJECT "${training_src}" "${training_hdr}")