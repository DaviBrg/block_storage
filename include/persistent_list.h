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


template <typename Key, typename Value>
struct ListNode {
        pmem::obj::persistent_ptr<ListNode<Key,Value>> next;
        pmem::obj::persistent_ptr<ListNode<Key,Value>> prev;
        pmem::obj::p<Key> id;
        pmem::obj::p<Value> obj;
};

template <typename Key, typename Value>
class PersistentList {

public:

    void Commit(pmem::obj::pool_base &pool,
                const std::vector<Value> &intention_list,
                std::unordered_map<Key,
                pmem::obj::persistent_ptr<ListNode<Key,Value>>> &lookup_table) {

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
                    std::unordered_map<Key,Value> &data_base,
                    std::unordered_map<Key,
                    pmem::obj::persistent_ptr<ListNode<Key,Value>>> &lookup_table) {
        auto current = head_;
        while (current != nullptr) {
            data_base.insert({current->obj.get_ro().id, current->obj.get_ro()});
            lookup_table.insert({current->obj.get_ro().id, current});
            current = current->next;
        }
    }


private:
    pmem::obj::persistent_ptr<ListNode<Key,Value>>
    AddNewEntry(const Value &entry) {
        auto entry_node = pmem::obj::make_persistent<ListNode<Key,Value>>();
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

    pmem::obj::persistent_ptr<ListNode<Key,Value>> head_;
    pmem::obj::persistent_ptr<ListNode<Key,Value>> tail_;
};

#endif // PERSISTENTLIST_H
