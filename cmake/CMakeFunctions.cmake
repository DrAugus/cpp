# CMakeFunctions.cmake

# 定义一个函数来创建可执行文件并链接库
function(create_executable)
    cmake_parse_arguments(PARSE_ARGV 0 ARG
        ""
        "LANGUAGE;TARGET_NAME;SOURCE_FILES;LIBRARIES"
        ""
    )

    # message(STATUS "###### create_executable LANGUAGE ${ARG_LANGUAGE}")
    # message(STATUS "###### create_executable TARGET_NAME ${ARG_TARGET_NAME}")
    # message(STATUS "###### create_executable SOURCE_FILES ${ARG_SOURCE_FILES}")
    # message(STATUS "###### create_executable LIBRARIES ${ARG_LIBRARIES}")

    # 检查TARGET_NAME是否已定义且不为空
    if(NOT DEFINED ARG_TARGET_NAME OR ARG_TARGET_NAME STREQUAL "")
        message(FATAL_ERROR "ARG_TARGET_NAME is not defined or is empty")
    endif()

    # 检查SOURCE_FILES是否已定义且不为空
    if(NOT DEFINED ARG_SOURCE_FILES OR ARG_SOURCE_FILES STREQUAL "")
        message(FATAL_ERROR "ARG_SOURCE_FILES is not defined or is empty")
    endif()

    # 检查LANGUAGE是否已定义且为C或CXX
    if(NOT DEFINED ARG_LANGUAGE OR NOT(ARG_LANGUAGE STREQUAL "C" OR ARG_LANGUAGE STREQUAL "CXX"))
        message(FATAL_ERROR "ARG_LANGUAGE must be either 'C' or 'CXX'")
    endif()

    # 创建可执行文件
    add_executable(${ARG_TARGET_NAME} ${ARG_SOURCE_FILES})

    # 检查LIBRARIES是否已定义（可以为空，表示不链接任何库）
    if(DEFINED ARG_LIBRARIES)
        # 链接库（LIBRARIES 可以是一个或多个库名/目标）
        target_link_libraries(${ARG_TARGET_NAME} ${ARG_LIBRARIES})
    endif()

    # 设置链接器语言为CXX（如果需要的话，这通常是默认的，但如果混合使用C和C++，则可能需要明确指定）
    set_target_properties(${ARG_TARGET_NAME} PROPERTIES LINKER_LANGUAGE ${ARG_LANGUAGE})

    # 安装可执行文件到"bin"目录（这可以根据需要进行调整）
    install(TARGETS ${ARG_TARGET_NAME} DESTINATION "bin")

    # 可选：添加编译选项（这里作为示例，可以通过额外参数传递）
    # if(DEFINED COMPILE_OPTIONS)
    # target_compile_options(${TARGET_NAME} PRIVATE ${COMPILE_OPTIONS})
    # endif()

    # 可选：添加包含目录（同样，这里作为示例）
    # if(DEFINED INCLUDE_DIRS)
    # target_include_directories(${TARGET_NAME} PRIVATE ${INCLUDE_DIRS})
    # endif()

    # ... 可以添加更多可选功能，如依赖项、编译定义等
endfunction(create_executable)

function(foreach_all_files)
    # PARSE_ARGV 表示参数是从命令行传递的。
    # 0 表示从第一个参数开始解析。
    # arg: 解析后变量名的前缀，以避免命名冲突。
    # 例如，LANGUAGE 会变成 arg_LANGUAGE。
    # 第一行 会作为布尔值变量存在
    # 第二行 需要一个或多个值的参数列表
    cmake_parse_arguments(PARSE_ARGV 0 ARG
        ""
        "LANGUAGE;CURRENT_DIR_NAME;APP_SOURCES;LIBRARIES"
        ""
    )

    # message(STATUS "###### foreach_all_files LANGUAGE ${LANGUAGE}")
    # message(STATUS "###### foreach_all_files CURRENT_DIR_NAME ${CURRENT_DIR_NAME}")
    # message(STATUS "###### foreach_all_files APP_SOURCES ${APP_SOURCES}")
    # message(STATUS "###### foreach_all_files LIBRARIES ${LIBRARIES}")

    # 检查LANGUAGE是否已定义且为C或CXX
    if(NOT DEFINED LANGUAGE OR NOT(LANGUAGE STREQUAL "C" OR LANGUAGE STREQUAL "CXX"))
        message(FATAL_ERROR "LANGUAGE must be either 'C' or 'CXX'")
    endif()

    if(NOT DEFINED ARG_LIBRARIES OR ARG_LIBRARIES STREQUAL "")
        set(ARG_LIBRARIES "")
    endif()

    if(LANGUAGE STREQUAL "C")
        set(replace_str ".c")
    elseif(LANGUAGE STREQUAL "CXX")
        set(replace_str ".cpp")
    endif()

    foreach(practice_file ${APP_SOURCES})
        # I used a simple string replace, to cut off .cpp.
        string(REPLACE ${replace_str} "" base_name ${practice_file})
        set(practice_name "${CURRENT_DIR_NAME}_${base_name}")

        if(NOT DEFINED LIBRARIES OR LIBRARIES STREQUAL "")
            set(LIBRARIES "")
        endif()

        # message(STATUS "//// ${LANGUAGE} ${practice_name} ${practice_file} ${LIBRARIES}")
        create_executable(
            LANGUAGE ${LANGUAGE}
            TARGET_NAME ${practice_name}
            SOURCE_FILES ${practice_file}
            LIBRARIES ${LIBRARIES}
        )
    endforeach(practice_file ${APP_SOURCES})
endfunction(foreach_all_files)
