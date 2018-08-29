#ifndef DISK_LOG_H
#define DISK_LOG_H

#include <string>
#include <map>

#include "block_storage.h"
#include "disk_pmem.h"

using namespace disk_pmem;
template <typename T>
class DiskLog {
private:

    Block<LogBlock<T>> block;
    BlockStorage<LogBlock<T>> storage;
    int offset;
    std::string path;

public:

    DiskLog(std::string path_) : offset(0), path(path_), storage(path_){
        storage.ClearFile();
    }
    int getOffSet() {
        return offset;
    }
    Block<LogBlock<T>> read(int offset_) {
        storage.ReadBlock(offset_,block);
        return block;
    }
    void write(const LogBlock<T> &logB) {
        block.SetData(logB);
        if (storage.WriteBlock(offset++, block) != blkstorage::kNoError) {
            std::cout << "There was an error during WriteBlock()." << std::endl;
        }
    }
};

#endif // DISK_LOG_H







