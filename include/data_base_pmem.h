#ifndef DATA_BASE_PMEM_H
#define DATA_BASE_PMEM_H

#include <unordered_map>
#include <vector>

#include "pmem_log.h"
#include "txentry.h"

template <typename Key, typename Value>
class DataBasePmem {
public:
    typedef Key key_type;
    typedef Value value_type;

    DataBasePmem(const char* path_, size_t kPoolSize):
        path(path_),
        pmemLog(path, kPoolSize),
        tx_id(0) {}

    size_t ExecuteTransaction(std::vector<TxEntry<Key,Value>> &tx) {
            int counter = 0;
            disk_pmem::LogEntry<Value> logE;

            for (auto& action:tx) {
                disk_pmem::LogUpdate<Value> logU;
                Value* ptr = action.value();

                logU.obj_id = action.key();
                logU.img_after = *ptr;
                if(action.type() == TxWrite) {
                    data_base_[action.key()] = *ptr;
                }
                else {
//                    *ptr = data_base_[action.key()];
                }
                logU.tx_id = tx_id;
                logE.updates[counter++] = logU;
            }
            for(int i = counter; i < disk_pmem::kTxSize; i++ ) {
                logE.updates[i].tx_id = -1;
            }
            disk_pmem::LogCommit logC;

            logC.tx_id = tx_id;
            logE.commit = logC;
            tx_id++;
            pmemLog.write(logE);
            return 1;
    }

    void Recover() {}

    const std::unordered_map<Key,Value>& data_base() {return data_base_;}

private:
    std::unordered_map<Key,Value> data_base_;
    const char* path;
    PmemLog<Value> pmemLog;
    unsigned long int tx_id;
};
#endif // DATA_BASE_PMEM_H
