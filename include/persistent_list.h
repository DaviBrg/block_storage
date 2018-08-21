#ifndef PERSISTENTLIST_H
#define PERSISTENTLIST_H

#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/p.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/transaction.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>


template <typename T>
struct ListNode {
        pmem::obj::persistent_ptr<ListNode<T>> next;
        pmem::obj::persistent_ptr<ListNode<T>> prev;
        pmem::obj::p<uint64_t> id;
        pmem::obj::p<T> obj;
};

template <typename T>
class PersistentList {

public:

    void Commit(pmem::obj::pool_base &pool,
                const std::vector<T> &intention_list,
                std::unordered_map<uint64_t,
                pmem::obj::persistent_ptr<ListNode<T>>> &lookup_table) {

        pmem::obj::transaction::exec_tx(pool, [&](){

            for (auto &entry : intention_list) {
                auto it = lookup_table.find(entry.id);
                if (it == std::end(lookup_table)) {
                    auto ptr = AddNewEntry(entry);
                    lookup_table[entry.id] = ptr;
                }
                else {
                    it->second->obj = entry;
                }
            }
        });
    }

    void Print() {
        auto current = head_;
        while (current != nullptr) {
            std::cout << current->id << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void RecoverNVM(pmem::obj::pool_base &pool,
                    std::unordered_map<uint64_t,T> &data_base,
                    std::unordered_map<uint64_t,
                    pmem::obj::persistent_ptr<ListNode<T>>> &lookup_table) {
        auto current = head_;
        while (current != nullptr) {
            data_base.insert({current->obj.get_ro().id, current->obj.get_ro()});
            lookup_table.insert({current->obj.get_ro().id, current});
            current = current->next;
        }
    }


private:
    pmem::obj::persistent_ptr<ListNode<T>>
    AddNewEntry(const T &entry) {
        auto entry_node = pmem::obj::make_persistent<ListNode<T>>();
        entry_node->id = entry.id;
        entry_node->obj = entry;
        if (head_ == nullptr) {
            head_ = tail_ = entry_node;
        }
        else {
            entry_node->next = head_;
            head_->prev = entry_node;
            head_ = entry_node;
        }

        return entry_node;
    }

    pmem::obj::persistent_ptr<ListNode<T>> head_;
    pmem::obj::persistent_ptr<ListNode<T>> tail_;
};

#endif // PERSISTENTLIST_H
