#ifndef DATA_BASE_PMEM_DISK_H
#define DATA_BASE_PMEM_DISK_H

#include <unordered_map>
#include <vector>
#include <unistd.h>

#include "txentry.h"
#include "persistent_list.h"

template <typename Key, typename Value>
class DataBasePmemDisk {
public:

    DataBasePmemDisk(size_t pool_size, const std::string &path, const std::string &layout) :
    pool_size_(pool_size), path_(path), layout_(layout){
        if (access(path_.c_str(), F_OK) != 0) {
            pool = pmem::obj::pool<PersistentList<Key,Value>>::create(
                        path_.c_str(), layout_.c_str(), pool_size_,
                        S_IWUSR | S_IRUSR);
            } else {
            pool = pmem::obj::pool<PersistentList<Key, Value>>::open(path_.c_str(),
                                                                     layout_.c_str());
            list_ = pool.get_root();
            Recover();
        }

        list_ = pool.get_root();
    }

    ~DataBasePmemDisk() {pool.close();}

    size_t ExecuteTransaction(std::vector<TxEntry<Key,Value>> &tx) {

        std::vector<Value> intention_list;

        for (auto &entry : tx) {
            if (entry.type() == TxWrite) {
                (entry.value())->id = entry.key();
                intention_list.push_back(*(entry.value()));
                data_base_[entry.key()] = *(entry.value());
            }
        }

        list_->Commit(pool, intention_list, lookup_table_);

    }

    void Recover() { list_->RecoverNVM(pool, data_base_, lookup_table_);}

    void Print() {list_->Print();}

    const std::unordered_map<Key,Value>& data_base() {return data_base_;}

private:
    size_t pool_size_;
    std::string path_;
    std::string layout_;

    std::unordered_map<Key,Value> data_base_;
    std::unordered_map<Key,
                    pmem::obj::persistent_ptr<ListNode<Key,Value>>> lookup_table_;
    pmem::obj::pool<PersistentList<Key,Value>> pool;
    pmem::obj::persistent_ptr<PersistentList<Key,Value>> list_;
};
#endif // DATA_BASE_PMEM_DISK_H
