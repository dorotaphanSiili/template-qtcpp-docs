find_package(Qt5 REQUIRED COMPONENTS Core Qml WebSockets)

find_package(testbed2 QUIET COMPONENTS testbed2_api )
find_package(tb_enum QUIET COMPONENTS tb_enum_api )
find_package(tb_same1 QUIET COMPONENTS tb_same1_api )
find_package(tb_same2 QUIET COMPONENTS tb_same2_api )
find_package(tb_simple QUIET COMPONENTS tb_simple_api )
find_package(testbed1 QUIET COMPONENTS testbed1_api )

set (PLUGIN_TESTBED1_SOURCES
    plugin.cpp
)

add_library(plugin_testbed1 SHARED ${PLUGIN_TESTBED1_SOURCES})

set(OUTPUT_PATH ${IMPORTS_PATH}/testbed1)

set_target_properties(plugin_testbed1 PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH}
)

target_link_libraries(plugin_testbed1 PUBLIC testbed1::testbed1_api)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/qmldir ${OUTPUT_PATH}/qmldir COPYONLY)

target_compile_definitions(plugin_testbed1 PRIVATE TESTBED1_PLUGIN_LIBRARY)
