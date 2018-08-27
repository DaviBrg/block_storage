#ifndef DISK_PMEM_H
#define DISK_PMEM_H

#include <stddef.h>



namespace disk_pmem {

constexpr size_t kObjSize = 128;
constexpr size_t kBlockSize = 4096;
constexpr unsigned int kTxSize = 3;

struct LogUpdate {
    unsigned int tx_id;
    unsigned int obj_id;
    char img_after[kObjSize];
}__attribute__((packed));

struct LogCommit {
    unsigned int tx_id;
}__attribute__((packed));

struct LogEntry {
    LogUpdate updates[kTxSize];
    LogCommit commit;
}__attribute__((packed));

constexpr size_t kNumLogEntries = kBlockSize / sizeof(LogEntry);
constexpr size_t kLogNetryRemaining = kBlockSize % sizeof(LogEntry);

struct LogBlock {
    LogEntry entries[kNumLogEntries];
    char v[kLogNetryRemaining];
}__attribute__((packed));

}

#endif // DISK_PMEM_H
