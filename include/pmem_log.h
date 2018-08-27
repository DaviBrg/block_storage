#ifndef PMEM_LOG_H
#define PMEM_LOG_H

#include "disk_pmem.h"

#include <libpmemlog.h>
#include <map>
#include <string>
#include <vector>

class PmemLog {
private:
    const char* path;
    PMEMlogpool *plp;

public:
    explicit PmemLog(const char* path_);
    ~PmemLog();
    void write(const disk_pmem::LogEntry& logE);
    void read(void* arg, int (*function)(const void *buf, size_t len, void *arg));
};

#endif // PMEM_LOG_H
