#ifndef WORKLOAD_GENERATOR_H
#define WORKLOAD_GENERATOR_H

#include "txentry.h"

#include <vector>
#include <random>
#include <cmath>

template <typename DBType, typename DBKey, typename DBValue>
class WorkloadGenerator
{
public:
    WorkloadGenerator(double skew_factor,int skew_window,
                      int tx_size, DBType *db):
        skew_window_(skew_window),
        tx_size_(tx_size),
        r_(),
        mt_(r_),
        exp_(skew_factor),
        db_(db) {}

    virtual ~WorkloadGenerator() {}

    void GenerateTx() {

    std::vector<TxEntry<DBKey,DBValue>> tx;
    do {
        int obj_id = 0;
        do {
            obj_id = floor(-exp_(mt_)) + newest_;
        } while (obj_id < 0);
        tx.push_back(obj_id);
    } while (tx.size() < std::min(tx_size_, newest_));
    advance_counter_++;
    if (advance_counter_ == skew_window_) {
        advance_counter_ = 0;
        newest_++;
    }
    db_->ExecuteTransaction(tx);
}

private:
    TxEntry<DBKey,DBValue> GenerateEntry(int obj_id) {
        return TxRead(TxInsert, static_cast<DBKey>(obj_id));
    }
    int skew_window_ = 1;
    int tx_size_ = 1;
    std::random_device r_;
    std::mt19937 mt_;
    std::exponential_distribution<double> exp_;
    int advance_counter_ = 0;
    int newest_ = 1;
    DBType *db_ = nullptr;
};

#endif // WORKLOAD_GENERATOR_H
