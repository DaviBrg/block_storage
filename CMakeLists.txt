cmake_minimum_required(VERSION 3.5)

set (CMAKE_CXX_STANDARD 11)

project(block_storage)

set(HEADERS
    include/workload_generator.h
    include/disk_log.h
    include/blkstorage.h
    include/data_base_disk.h
    include/lru.h
    include/block_storage.h
    include/data_base.h
    include/sql_parser.h
    include/persistent_list.h
)

set(SOURCES
    src/main.cpp
    src/workload_generator.cpp
    src/disk_log.cpp
    src/blkstorage.cpp
    src/data_base_disk.cpp
    src/sql_parser.cpp
)

add_executable(block_storage ${SOURCES} ${HEADERS})

target_link_libraries(block_storage -lpmemobj)

target_include_directories(block_storage
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
