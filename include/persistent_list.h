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
        pmem::obj::persistent_ptr<ListNode> next;
        pmem::obj::persistent_ptr<ListNode> previous;
        pmem::obj::p<uint64_t> key;
        pmem::obj::p<T> obj;
};




template <typename T>
class PersistentList {

public:

    ListNode<T>* Push(pmem::obj::pool_base &pool, uint64_t key, const  T &value) {
        pmem::obj::transaction::exec_tx(pool, [&] {
            auto node = pmem::obj::make_persistent<ListNode<T>>();
        });

    }


    bool IsEmpty() {
        return (head_ == nullptr);
    }


private:
    pmem::obj::persistent_ptr<ListNode<T>> head_;
};

#endif // PERSISTENTLIST_H
