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
    include/sql_parser.h
    include/persistent_list.h
    include/txentry.h
    include/data_base_pmem.h
    include/pmem_log.h
    include/disk_pmem.h
    include/data_base_pmem_disk.h
    include/performance_logger.h
)

set(SOURCES
    src/main.cpp
    src/disk_log.cpp
    src/blkstorage.cpp
    src/data_base_disk.cpp
    src/sql_parser.cpp
    src/data_base_pmem.cpp
    src/pmem_log.cpp
    src/performance_logger.cpp
)

add_executable(block_storage ${SOURCES} ${HEADERS})

target_link_libraries(block_storage -lpmemobj -lpmemlog)

target_include_directories(block_storage
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
