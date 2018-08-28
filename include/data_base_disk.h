#ifndef DATA_BASE_DISK_H
#define DATA_BASE_DISK_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "disk_log.h"
#include "txentry.h"


template <typename Key, typename Value>
class DataBaseDisk {
public:
    typedef Key key_type;
    typedef Value value_type;

    DataBaseDisk(const std::string &path) :
        diskLog(path),
        tx_id(0) {}

    size_t ExecuteTransaction(const std::vector<TxEntry<Key,Value>> &tx) {}

    void Recover() {}

    const std::unordered_map<Key,Value>& data_base() {return data_base_;}

private:
    std::unordered_map<Key,Value> data_base_;
    DiskLog diskLog;
    int indexBlock;
    LogBlock logB;
    int tx_id;
};

#endif // DATA_BASE_DISK_H
