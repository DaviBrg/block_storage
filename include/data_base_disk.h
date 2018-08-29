#ifndef DATA_BASE_DISK_H
#define DATA_BASE_DISK_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "disk_log.h"
#include "disk_pmem.h"
#include "txentry.h"


template <typename Key, typename Value>
class DataBaseDisk {
public:
    typedef Key key_type;
    typedef Value value_type;

    DataBaseDisk(const std::string &path) :
        diskLog(path),
        tx_id(0) {}

    size_t ExecuteTransaction(std::vector<TxEntry<Key,Value>> &tx) {
        int counter = 0;

        for (auto& action:tx) {
            LogUpdate<Value> logU;
            Value* ptr = action.value();

            logU.obj_id = action.key();
            logU.img_after = *ptr;
            if(action.type() == TxWrite) {
                data_base_[action.key()] = *ptr;
            }
            else {
                *ptr = data_base_[action.key()];
            }
            logU.tx_id = tx_id;
            (logB.entries[indexBlock]).updates[counter++] = logU;
        }
        for(int i = counter; i < disk_pmem::kTxSize; i++ )
        {
            (logB.entries[indexBlock]).updates[i].obj_id = -1;
            (logB.entries[indexBlock]).updates[i].tx_id = -1;
        }
        LogCommit logC;

        logC.tx_id = tx_id;
        (logB.entries[indexBlock++]).commit = logC;
        tx_id++;
        if(indexBlock == disk_pmem::NumLogEntries<Value>()) {
            indexBlock = 0;
            diskLog.write(logB);
            return disk_pmem::NumLogEntries<Value>();
        }
        return 0;
    }

    void Recover() {}

    const std::unordered_map<Key,Value>& data_base() {return data_base_;}

private:
    std::unordered_map<Key,Value> data_base_;
    DiskLog<Value> diskLog;
    int indexBlock;
    LogBlock<Value> logB;
    int tx_id;
};

#endif // DATA_BASE_DISK_H
