# ------------------------------------------------------------------
# 公共框架：framework/ 下的所有 .cpp 打包成 framework 库
# 新增 .h / .cpp（含子目录）后直接 build 即可，无需改动本文件
# ------------------------------------------------------------------
file(GLOB_RECURSE FRAMEWORK_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE FRAMEWORK_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

if(FRAMEWORK_SOURCES)
    add_library(framework STATIC ${FRAMEWORK_SOURCES} ${FRAMEWORK_HEADERS})
    set(FRAMEWORK_SCOPE PUBLIC)
else()
    add_library(framework INTERFACE)
    target_sources(framework PRIVATE ${FRAMEWORK_HEADERS})   # 关键：让它生成可见的 VS 项目
    set(FRAMEWORK_SCOPE INTERFACE)
endif()

target_include_directories(framework ${FRAMEWORK_SCOPE} ${CMAKE_CURRENT_SOURCE_DIR})

# 让 VS 里按目录层级显示，而不是平铺在 "Source Files"
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${FRAMEWORK_SOURCES} ${FRAMEWORK_HEADERS})

