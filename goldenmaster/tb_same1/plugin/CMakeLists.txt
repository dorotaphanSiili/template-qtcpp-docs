find_package(Qt5 REQUIRED COMPONENTS Core Qml WebSockets)

find_package(testbed2 QUIET COMPONENTS testbed2_api )
find_package(tb_enum QUIET COMPONENTS tb_enum_api )
find_package(tb_same1 QUIET COMPONENTS tb_same1_api )
find_package(tb_same2 QUIET COMPONENTS tb_same2_api )
find_package(tb_simple QUIET COMPONENTS tb_simple_api )
find_package(testbed1 QUIET COMPONENTS testbed1_api )

set (PLUGIN_TB_SAME1_SOURCES
    plugin.cpp
)

add_library(plugin_tb_same1 SHARED ${PLUGIN_TB_SAME1_SOURCES})

set(OUTPUT_PATH ${IMPORTS_PATH}/tb/same1)

set_target_properties(plugin_tb_same1 PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH}
)

target_link_libraries(plugin_tb_same1 PUBLIC tb_same1::tb_same1_api)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/qmldir ${OUTPUT_PATH}/qmldir COPYONLY)

target_compile_definitions(plugin_tb_same1 PRIVATE TB_SAME1_PLUGIN_LIBRARY)
