#ifndef PERSISTENTLIST_H
#define PERSISTENTLIST_H

#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/p.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/transaction.hpp>
#include <iostream>

//explicit PersistentList(const char* path, const char* layout) {

//}

//~PersistentList() {
//    try {
//        pool_.close();
//    }
//    catch(const std::logic_error& excep) {
//        std::cout << excep.what() << std::endl;
//        std::abort;
//    }
//}


template <typename T>
struct ListNode {
        pmem::obj::persistent_ptr<ListNode<T>> next;
        pmem::obj::persistent_ptr<ListNode<T>> previous;
        pmem::obj::p<uint64_t> key;
        pmem::obj::p<T> obj;
};




template <typename T>
class PersistentList {

public:

    ListNode<T>* Push(pmem::obj::pool_base &pool, uint64_t key, const  T &value) {
        pmem::obj::transaction::exec_tx(pool, [&] {
            auto current = pmem::obj::make_persistent<ListNode<T>>();
            current->key = key;
            current->value = value;
            if (head_ == nullptr) {
                head_ = current;
            }
            else {
                current->next = head_;
                head_->previous = current;
                head_ = current;
            }
        });
        return head_.get();
    }


    bool IsEmpty() {
        return (head_ == nullptr);
    }


private:
    pmem::obj::persistent_ptr<ListNode<T>> head_;
};

#endif // PERSISTENTLIST_H
