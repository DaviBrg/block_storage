#ifndef DATA_BASE_PMEM_H
#define DATA_BASE_PMEM_H

#include <unordered_map>
#include <vector>

#include "pmem_log.h"
#include "txentry.h"

template <typename Key, typename Value>
class DataBasePmem {
public:
    DataBasePmem(const char* path_):
        path(path_),
        pmemLog(path),
        tx_id(0) {}

    size_t ExecuteTransaction(const std::vector<TxEntry<Key,Value>> &tx) {}

    void Recover() {}

    const std::unordered_map<Key,Value>& data_base() {return data_base_;}

private:
    std::unordered_map<Key,Value> data_base_;
    const char* path;
    PmemLog pmemLog;
    int tx_id;
};
#endif // DATA_BASE_PMEM_H
