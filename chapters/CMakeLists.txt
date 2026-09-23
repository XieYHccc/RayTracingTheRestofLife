# ------------------------------------------------------------------
# 自动扫描 chapters/ 下的每个子目录，各生成一个可执行文件
# 新增 05/ 目录后直接 build 即可，无需改动本文件
# ------------------------------------------------------------------
file(GLOB CHAPTER_DIRS CONFIGURE_DEPENDS
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/*"
)

foreach(dir ${CHAPTER_DIRS})
    if(NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${dir})
        continue()
    endif()

    file(GLOB CHAPTER_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.cpp"
    )
    if(NOT CHAPTER_SOURCES)
        continue()
    endif()

    add_executable(${dir} ${CHAPTER_SOURCES})
    target_link_libraries(${dir} PRIVATE framework)
    target_include_directories(${dir} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${dir})

    message(STATUS "Added chapter: ${dir}")
endforeach()
