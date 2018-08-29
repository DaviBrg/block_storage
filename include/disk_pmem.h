#ifndef DISK_PMEM_H
#define DISK_PMEM_H

#include <stddef.h>

namespace disk_pmem {

constexpr size_t kBlockSize = 4096;
constexpr unsigned int kTxSize = 3;

template <typename T>
struct LogUpdate {
    size_t tx_id;
    size_t obj_id;
    T img_after;
}__attribute__((packed));

struct LogCommit {
    unsigned int tx_id;
}__attribute__((packed));

template <typename T>
struct LogEntry {
    LogUpdate<T> updates[kTxSize];
    LogCommit commit;
}__attribute__((packed));

template <typename T>
constexpr size_t NumLogEntries() {
    static_assert(kBlockSize > sizeof(LogEntry<T>),"Invalid log entry size");
    return (kBlockSize / sizeof(LogEntry<T>));
}

template <typename T>
constexpr size_t LogEntryRemaining() {
    static_assert(kBlockSize > sizeof(LogEntry<T>),"Invalid log entry size");
    return (kBlockSize % sizeof(LogEntry<T>));
}

template <typename T>
struct LogBlock {
    LogEntry<T> entries[NumLogEntries<T>()];
    char v[LogEntryRemaining<T>()];
}__attribute__((packed));

}

#endif // DISK_PMEM_H
