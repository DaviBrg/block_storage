#ifndef DISK_LOG_H
#define DISK_LOG_H

#include "block_storage.h"

#include <string>
#include <map>


const unsigned int kTxSize = 3;

struct LogUpdate {
    unsigned int tx_id;
    unsigned int obj_id;
    double img_after;
}__attribute__((packed));

struct LogCommit {
    unsigned int tx_id;
}__attribute__((packed));

struct LogEntry {
    LogUpdate updates[kTxSize];
    LogCommit commit;
}__attribute__((packed));

struct LogBlock {
    LogEntry entries[78];
    int v[10];
}__attribute__((packed));

class DiskLog {
private:

    Block<LogBlock> block;
    BlockStorage<LogBlock> storage;
    int offset;
    std::string path;

public:

     DiskLog(std::string path_);
     int getOffSet();
     Block<LogBlock> read(int offset_);
     void write(const LogBlock &logB);
};

#endif // DISK_LOG_H







