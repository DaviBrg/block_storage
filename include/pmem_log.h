#ifndef PMEM_LOG_H
#define PMEM_LOG_H

#include "disk_pmem.h"

#include <libpmemlog.h>
#include <map>
#include <string>
#include <vector>

template <typename T>
class PmemLog {
private:
    const char* path;
    PMEMlogpool *plp;

public:
    explicit PmemLog(const char* path_, size_t kPoolSize) : path(path_) {
        plp = pmemlog_create(path, kPoolSize, 0666);

        if (plp == NULL) {
            plp = pmemlog_open(path);
        }
        if (plp == NULL) {
            perror(path);
            exit(1);
        }
        pmemlog_rewind(plp);
    }

    ~PmemLog() {
        pmemlog_close(plp);
    }

    void write(const disk_pmem::LogEntry<T>& logE) {
        if (pmemlog_append(plp, &logE, sizeof(logE)) < 0) {
            perror("pmemlog_append");
            exit(1);
        }
    }

    void read(void* arg, int (*function)(const void *buf, size_t len, void *arg)) {
        pmemlog_walk(plp, 0, function, arg);
    }
};

#endif // PMEM_LOG_H
