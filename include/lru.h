#ifndef LRU_H
#define LRU_H

#include <unordered_map>
#include <list>
#include <stdlib.h>


template<typename T>
class Lru
{
public:

    Lru(): lru_list_({}), lru_map_({}) {}


    bool Contains(const T &entry) const {
        return (lru_map_.find(entry) != std::end(lru_map_));
    }

    void Push(const T &entry) {

        if (Contains(entry)) {
            lru_list_.erase(lru_map_[entry]);
        }

        Insert(entry);
    }

    typename std::list<T>::iterator begin() {return lru_list_.begin();}
    typename std::list<T>::iterator end() {return lru_list_.end();}

private:

    void Insert(T entry) {
        lru_list_.push_back(entry);
        lru_map_[entry] = std::prev(std::end(lru_list_));
    }

    std::list<T> lru_list_;
    std::unordered_map<T,typename std::list<T>::iterator> lru_map_;
};

#endif // LRU_H
